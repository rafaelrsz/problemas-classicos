# parametro padrao: arquivo de entrada
input = "testes/in.txt"

# caso precise de parametros adicionais
alg = ""

# compilador
CC = g++

# regra default: obter os executáveis dos dois algoritmos
all: forca-bruta kernighan-lin

# prepara os executáveis dos dois algoritmos
forca-bruta: forca-bruta.o
	$(CC) forca-bruta.o -o forca-bruta

kernighan-lin: kernighan-lin.o
	$(CC) kernighan-lin.o -o kernighan-lin

# prepara os arquivos objetos dos dois algoritmos
forca-bruta.o: src/forca-bruta.cpp
	$(CC) -c -I src/ src/forca-bruta.cpp -o forca-bruta.o

kernighan-lin.o: src/kernighan-lin.cpp
	$(CC) -c -I src/ src/kernighan-lin.cpp -o kernighan-lin.o

# executa os dois algoritmos
run: run-forca-bruta run-kernighan-lin

# executa o algoritmo 1 separadamente
run-forca-bruta: forca-bruta
	cat $(input) | ./forca-bruta

# executa o algoritmo 2 separadamente
run-kernighan-lin: kernighan-lin
	cat $(input) | ./kernighan-lin

# # executa o algoritmo 1 separadamente
# run-forca-bruta: forca-bruta
# 	powershell -Command "cat $(input) | ./forca-bruta"

# # executa o algoritmo 2 separadamente
# run-kernighan-lin: kernighan-lin
# 	powershell -Command "cat $(input) | ./kernighan-lin"


# remove os arquivos objetos e os executáveis
clean:
	rm -f *.o forca-bruta kernighan-lin