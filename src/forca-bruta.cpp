#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

#define INF 10000000

typedef vector<int> vi;
typedef vector<vector<int>> vvi;

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

pair<vi, vi> particionaForcaBruta(vvi &MA, int n, int &corteMinimo)
{
  pair<vi, vi> particoesOtimas;

  // Inicializa o vetor de partição, onde true representa vértices na partição A
  vi estaNaParticaoA(n);
  fill_n(estaNaParticaoA.begin(), n / 2, 1);

  corteMinimo = INF;
  // Gera todas as combinações possiveis para encontrar a melhor
  do
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

    int corte = calculaCorte(MA, n, particaoA, particaoB);

    if (corte < corteMinimo)
    {
      corteMinimo = corte;
      particoesOtimas = make_pair(particaoA, particaoB);
    }

  } while (
      prev_permutation(estaNaParticaoA.begin(), estaNaParticaoA.end()) &&
      estaNaParticaoA[0]); // A validação estaNaParticaoA[0] evita partições equivalentes

  return particoesOtimas;
}

void exibirParticoes(pair<vi, vi> &particoesOtimas, int n)
{
  cout << "Particao A: ";
  for (int i = 0; i < n / 2; i++)
  {
    cout << particoesOtimas.first[i] << " ";
  }

  cout << endl
       << "Particao B: ";
  for (int i = 0; i < n / 2; i++)
  {
    cout << particoesOtimas.second[i] << " ";
  }
  cout << endl;
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
  int corteMinimo;
  chrono::steady_clock::time_point begin = chrono::steady_clock::now();
  pair<vi, vi> particoesOtimas = particionaForcaBruta(MA, n, corteMinimo);
  chrono::steady_clock::time_point end = chrono::steady_clock::now();

  cout << "Valor do corte minimo: "
       << corteMinimo
       << endl;

  exibirParticoes(particoesOtimas, n);

  cout << "Tempo de execucao = " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " ms" << " | ";
  cout << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << " ns" << endl;

  return 0;
}