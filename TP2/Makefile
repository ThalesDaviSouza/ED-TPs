CFLAGS = -I include

all: output

output: obj/main.o obj/pacote.o
	g++ -o bin/tp2 obj/main.o obj/pacote.o

obj/main.o: ./src/main.cpp ./include/pacote.hpp | obj
	g++ $(CFLAGS) -c ./src/main.cpp -o obj/main.o

obj/pacote.o: ./src/pacote.cpp ./include/pacote.hpp | obj
	g++ $(CFLAGS) -c ./src/pacote.cpp -o obj/pacote.o 


