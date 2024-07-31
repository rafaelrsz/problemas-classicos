#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

#define INF 10000000

typedef vector<int> vi;
typedef vector<bool> vb;

int calculaCorte(int **MA, int n, vi particaoA, vi particaoB)
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

pair<vi, vi> particionaForcaBruta(int **MA, int n)
{
  pair<vi, vi> particoesOtimas;
  vb estaNaParticaoA;

  // Inicializa partições iniciais
  estaNaParticaoA.assign(n, false);
  fill_n(estaNaParticaoA.begin(), n / 2, true);

  int corteMinimo = INF;
  // Gera todas as combinações possiveis para encontrar a melhor
  do
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

    int corte = calculaCorte(MA, n, particaoA, particaoB);

    if (corte < corteMinimo)
    {
      corteMinimo = corte;
      particoesOtimas = make_pair(particaoA, particaoB);
    }
    // Verifica se estaNaParticaoA[0] para evitar partições equivalentes
  } while (prev_permutation(estaNaParticaoA.begin(), estaNaParticaoA.end()) && estaNaParticaoA[0]);

  return particoesOtimas;
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

  // Execução do algoritmo
  pair<vi, vi> particoesOtimas = particionaForcaBruta(MA, n);

  // Exibição do resultado *CALCULO DUPLICADO DO MELHOR CORTE - MELHORAR*
  cout << "O valor do corte minimo eh "
       << calculaCorte(MA, n, particoesOtimas.first, particoesOtimas.second)
       << endl;

  cout << "Particao A: ";
  for (int i = 0; i < n / 2; i++)
  {
    cout << particoesOtimas.first[i] << "  ";
  }

  cout << endl
       << "Particao B: ";
  for (int i = 0; i < n / 2; i++)
  {
    cout << particoesOtimas.second[i] << "  ";
  }
  cout << endl;

  // Desalocação de memória
  for (int i = 0; i < n; i++)
  {
    delete MA[i];
  }

  delete MA;

  system("pause");
  return 0;
}