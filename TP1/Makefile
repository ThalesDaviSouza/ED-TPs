CFLAGS = -I include

all: output

## Não me pergunte porque o executável se chama tp3 para o tp1
output: obj/main.o obj/sort.o
	g++ -o bin/tp3 obj/main.o obj/sort.o

obj/main.o: ./src/main.cpp ./include/sort.hpp | obj
	g++ $(CFLAGS) -c ./src/main.cpp -o obj/main.o

obj/sort.o: ./src/sort.cpp ./include/sort.hpp | obj
	g++ $(CFLAGS) -c ./src/sort.cpp -o obj/sort.o 
