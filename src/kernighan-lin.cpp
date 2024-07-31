#include <iostream>
#include <vector>

using namespace std;

#define INF 10000000

typedef vector<int> vi;

vi KernighanLin(int **MA, int n)
{
  // Definição das partições iniciais
  vi estaNaParticaoA = vi(n);
  for (int i = 0; i < n / 2; i++)
  {
    estaNaParticaoA[i] = true;
  }

  int G;

  do
  {
    int a, b;
    vi locked = vi(n);
    vi D = vi(n);
    vector<pair<int, pair<int, int>>> ganhos;

    // Calcula o D inicial
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

    for (int i = 0; i < n / 2; i++)
    {

      // Calcular todos os ganhos possíveis e escolher o maior
      int maiorGanho = -INF;
      for (int j = 0; j < n; j++)
      {

        if (locked[j] || !estaNaParticaoA[j])
          continue;

        for (int k = j + 1; k < n; k++)
        {
          if (locked[k] || estaNaParticaoA[k])
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

      ganhos.push_back(make_pair(maiorGanho, make_pair(a, b)));

      // Trancar a e b
      locked[a] = 1;
      locked[b] = 1;

      // Atualizar o D dos vértices não trancados
      if (i + 1 < n / 2)
      {
        for (int j = 0; j < n; j++)
        {
          if (locked[j])
            continue;

          if (estaNaParticaoA[j])
            D[j] = D[j] + (2 * MA[j][a]) - (2 * MA[j][b]);
          else
            D[j] = D[j] + (2 * MA[j][b]) - (2 * MA[j][a]);
        }
      }
    }

    // Fazer as trocas de partição
    int maiorK = -1;
    int somaGanhos = 0;
    G = -INF;

    // Encontra o k que de forma a maximizar os ganhos
    for (int i = 0; i < n / 2; i++)
    {
      somaGanhos += ganhos[i].first;
      if (somaGanhos > G)
      {
        maiorK = i;
        G = somaGanhos;
      }
    }

    // Se existe ganho fazer as trocas
    if (G > 0)
    {
      for (int i = 0; i <= maiorK; i++)
      {
        estaNaParticaoA[ganhos[i].second.first] = false;
        estaNaParticaoA[ganhos[i].second.second] = true;
      }
    }
  } while (G > 0);

  return estaNaParticaoA;
}

int imprimirResultado(int **MA, int n, vi estaNaParticaoA)
{
  vi particaoA(n / 2), particaoB(n / 2);

  int indexA = 0, indexB = 0;
  for (int i = 0; i < n; i++)
  {
    if (estaNaParticaoA[i])
    {
      particaoA[indexA] = i;
      indexA++;
    }
    else
    {
      particaoB[indexB] = i;
      indexB++;
    }
  }

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

  cout << "O valor do corte minimo eh "
       << valorCorte
       << endl;

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

  return valorCorte;
}

int main()
{
  int n, m, u, v;
  cin >> n >> m;

  int **MA = new int *[n];

  // Inicialização da matriz de adjacência
  for (int i = 0; i < n; i++)
  {
    MA[i] = new int[n];

    for (int j = 0; j < n; j++)
    {
      MA[i][j] = 0;
    }
  }

  // Leitura dos dados
  for (int i = 0; i < m; i++)
  {
    cin >> u >> v;
    MA[u][v] = MA[v][u] = 1;
  }

  // Cálculo da solução
  vi estaNaParticaoA = KernighanLin(MA, n);

  // Imprimir o resultado
  imprimirResultado(MA, n, estaNaParticaoA);

  // Desalocação de memória
  for (int i = 0; i < n; i++)
  {
    delete MA[i];
  }

  delete MA;

  system("pause");
  return 0;
}