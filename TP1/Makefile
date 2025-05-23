CFLAGS = -I include

all: output

output: obj/main.o obj/sort.o obj/ordenador.o
	g++ -o bin/tp1.out obj/main.o obj/sort.o obj/ordenador.o

obj/main.o: ./src/main.cpp ./include/sort.hpp | obj
	g++ $(CFLAGS) -c ./src/main.cpp -o obj/main.o

obj/sort.o: ./src/sort.cpp ./include/sort.hpp | obj
	g++ $(CFLAGS) -c ./src/sort.cpp -o obj/sort.o 

obj/ordenador.o: ./src/ordenador.cpp ./include/ordenador.hpp | obj
	g++ $(CFLAGS) -c ./src/ordenador.cpp -o obj/ordenador.o 
