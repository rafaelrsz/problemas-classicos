
## :bulb: Sobre

Esse projeto foi desenvolvido como trabalho prático da disciplina GCC253 - Complexidade e Projetos de Algoritmos ministrada pelo professor Vinícius Dias (UFLA).

O objetivo do trabalho é estudar e apresentar um seminário sobre algum problema clássico da computação. Nesse repositório será encontrado um estudo sobre o problema da Partição de Grafos.

>**Partição de Grafos (PG)**
>Dado um grafo não direcionado G com uma quantidade par de vértices, o objetivo é dividir o conjunto de vértices em dois grupos A,B de igual tamanho de tal forma que a quantidade de arestas entre os grupos deve ser minimizada. Portanto, a entrada é um grafo $G(V,E)$ e a saída são dois subconjuntos disjuntos de vértices $A, B \subseteq V$, tal que  $$A \cap B = \emptyset$$.


## :mag_right: Tópicos abordados


* Definição e explicação do problema. 
* Algoritmo exato para o problema: força bruta $O(2^n)$.
* Algoritmo aproximado ou heurística para o problema: Kernighan-Lin $O(n^3)$.
* Demonstração da execução de cada algoritmo.
* Análise experimental dos algoritmos.


## :computer: Execução

O projeto foi desenvolvido para ser compatível com o Linux. Portanto, é recomendável que ele seja executado neste sistema operacional para obter uma melhor aferição da perfomance e tempo de execução dos algoritmos.

Os dois algoritmos podem ser executados manualmente (qualquer sistema) ou utilizando o makefile (Linux). 

```bash
# Executar os dois algoritmos com entrada padrão
make run 

# Executar os dois algoritmos utilizando o arquivo in2.txt como entrada
make run input="testes/in2.txt" 

# Limpar os arquivos 
make clean 
```
## :book: Referências

### Livros

- [Kahng, Lienig, Markov, Jin Hu (2011) - From Graph Partitioning to Timing Closure](https://ia903208.us.archive.org/0/items/VLSI_Physical_Design_From_Graph_Partitioning_to_Timing_Closure/VLSI_Physical_Design_From_Graph_Partitioning_to_Timing_Closure.pdf)

### Artigos

- [Kernighan, Lin (1970) - An Efficient Heuristic Procedure for Partitioning Graphs](https://www.cs.utexas.edu/~pingali/CS395T/2009fa/papers/kl.pdf)

### Projetos
- [Mostafa Hassan - Graph Test Cases Generator](https://mostafa-abdullah.github.io/graph/random-case.html)

