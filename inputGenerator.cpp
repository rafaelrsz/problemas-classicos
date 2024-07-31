#include <iostream>
#include <stdlib.h>

using namespace std;

// A function to generate random graph.
void GenerateRandGraphs(int NOE, int NOV)
{
  int i, j, edge[NOE][2], count;
  i = 0;
  // Build a connection between two random vertex.
  while (i < NOE)
  {
    edge[i][0] = rand() % NOV;
    edge[i][1] = rand() % NOV;

    if (edge[i][0] == edge[i][1])
      continue;
    else
    {
      for (j = 0; j < i; j++)
      {
        if ((edge[i][0] == edge[j][0] && edge[i][1] == edge[j][1]) || (edge[i][0] == edge[j][1] && edge[i][1] == edge[j][0]))
          i--;
      }
    }
    i++;
  }

  // Print the random graph.
  cout << "\nThe generated random random graph is: " << endl;
  cout << NOV << " " << NOE << endl;
  for (i = 0; i < NOE; i++)
  {
    cout << edge[i][0] << " " << edge[i][1] << endl;
  }
}

int main()
{
  int n, i, e, v;
  cout << "Digite o numero de vertices:" << endl;

  cin >> v;
  cout << "Digite o numero de arestas:" << endl;
  cin >> e;

  // A function to generate a random undirected graph with e edges and v vertexes.
  GenerateRandGraphs(e, v);
  system("pause");
}