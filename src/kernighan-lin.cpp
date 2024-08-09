#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

#define INF 10000000

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<pair<int, ii>> vGanhos;

/* Realiza o cálculo inicial da diferença D entre os custos
 externos e internos para os vértices do grafo */
vi calcularDInicial(vvi &MA, int n, vi &estaNaParticaoA)
{
  vi D(n, 0);

  for (int j = 0; j < n; j++)
  {
    for (int k = 0; k < n; k++)
    {
      if (MA[j][k] == 1)
      {
        if (estaNaParticaoA[j] == estaNaParticaoA[k])
          D[j]--; // Se estão na mesma partição = custo interno
        else
          D[j]++; // Se não estão na mesma partição = custo externo
      }
    }
  }
  return D;
}

/* Atualizar a diferença D dos vértices não trancados */
void atualizarD(vvi &MA, int n,
                vi &estaNaParticaoA, vi &D,
                vi &trancado, int &a, int &b)
{
  for (int j = 0; j < n; j++)
  {
    if (trancado[j])
      continue;

    if (estaNaParticaoA[j])
      D[j] = D[j] + (2 * MA[j][a]) - (2 * MA[j][b]);
    else
      D[j] = D[j] + (2 * MA[j][b]) - (2 * MA[j][a]);
  }
}

/* Encontra as melhores trocas de vértices de modo a reduzir o corte*/
vGanhos encontrarGanhos(vvi &MA, int n,
                        vi &estaNaParticaoA, vi &D)
{
  vGanhos ganhos;
  vi trancado(n, 0); // Marca os vértices que já foram trocados
  int a, b;

  for (int i = 0; i < n / 2; i++)
  {
    int maiorGanho = -INF;
    for (int j = 0; j < n; j++)
    {
      if (trancado[j] || !estaNaParticaoA[j])
        continue;

      for (int k = j + 1; k < n; k++)
      {
        if (trancado[k] || estaNaParticaoA[k])
          continue;

        int ganho = D[j] + D[k] - 2 * MA[j][k];

        if (ganho > maiorGanho)
        {
          a = j;
          b = k;
          maiorGanho = ganho;
        }
      }
    }

    // Armazena o par de vértices e seu respectivo ganho na estrutura de dados
    ganhos.push_back(make_pair(maiorGanho, make_pair(a, b)));
    trancado[a] = trancado[b] = 1;

    atualizarD(MA, n, estaNaParticaoA, D, trancado, a, b);
  }

  return ganhos;
}

vi KernighanLin(vvi &MA, int n)
{
  // Inicializa o vetor de partição, onde true representa vértices na partição A
  vi estaNaParticaoA(n);
  fill_n(estaNaParticaoA.begin(), n / 2, 1);

  int ganhoMaximo;

  do
  {
    vi D = calcularDInicial(MA, n, estaNaParticaoA);
    vGanhos ganhos = encontrarGanhos(MA, n, estaNaParticaoA, D);

    ganhoMaximo = -INF;
    int indiceMaiorGanho = -1;
    int somaGanhos = 0;

    // Encontra o indice K de forma a maximizar os ganhos
    for (int i = 0; i < n / 2; i++)
    {
      somaGanhos += ganhos[i].first;
      if (somaGanhos > ganhoMaximo)
      {
        indiceMaiorGanho = i;
        ganhoMaximo = somaGanhos;
      }
    }

    // Se existir ganho fazer as trocas
    if (ganhoMaximo > 0)
    {
      for (int i = 0; i <= indiceMaiorGanho; i++)
      {
        estaNaParticaoA[ganhos[i].second.first] = false;
        estaNaParticaoA[ganhos[i].second.second] = true;
      }
    }

  } while (ganhoMaximo > 0);

  return estaNaParticaoA;
}

// Calcula o corte entre duas partições A e B
int calculaCorte(vvi &MA, int n, vi &particaoA, vi &particaoB)
{
  int valorCorte = 0;

  for (int i = 0; i < n / 2; i++)
  {
    int verticeA = particaoA[i];

    for (int j = 0; j < n / 2; j++)
    {
      int verticeB = particaoB[j];

      if (MA[verticeA][verticeB])
        valorCorte++;
    }
  }

  return valorCorte;
}

// Imprime as partições resultantes e o corte entre elas
void imprimirResultado(vvi &MA, int n, vi estaNaParticaoA)
{
  vi particaoA, particaoB;
  particaoA.reserve(n / 2);
  particaoB.reserve(n / 2);

  for (int i = 0; i < n; i++)
  {
    if (estaNaParticaoA[i])
      particaoA.push_back(i);
    else
      particaoB.push_back(i);
  }

  cout << "Particao A: ";
  for (int i = 0; i < n / 2; i++)
  {
    cout << particaoA[i] << "  ";
  }

  cout << endl
       << "Particao B: ";
  for (int i = 0; i < n / 2; i++)
  {
    cout << particaoB[i] << "  ";
  }
  cout << endl;

  int valorCorte = calculaCorte(MA, n, particaoA, particaoB);
  cout << "Valor do corte minimo: "
       << valorCorte
       << endl;
}

int main()
{
  // Inicialização das estruturas de dados e leitura dos dados
  int n, m, u, v;
  cin >> n >> m;

  vvi MA(n, vi(n, 0));

  for (int i = 0; i < m; i++)
  {
    cin >> u >> v;
    MA[u][v] = MA[v][u] = 1;
  }

  // Execução do algoritmo
  chrono::steady_clock::time_point begin = chrono::steady_clock::now();
  vi estaNaParticaoA = KernighanLin(MA, n);
  chrono::steady_clock::time_point end = chrono::steady_clock::now();

  // Imprimir o resultado
  imprimirResultado(MA, n, estaNaParticaoA);
  cout << "Tempo de execucao = " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " ms" << " | ";
  cout << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << " ns" << endl;

  system("pause");
  return 0;
}