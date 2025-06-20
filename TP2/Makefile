CFLAGS = -I include

all: output

output: obj/pacote.o obj/armazem.o obj/rede.o obj/escalonador.o obj/main.o
	g++ -o bin/tp2.out obj/pacote.o obj/armazem.o obj/rede.o obj/escalonador.o obj/main.o

obj/main.o: src/main.cpp include/utils.hpp include/list.hpp include/heap.hpp include/pilha.hpp | obj
	g++ $(CFLAGS) -c src/main.cpp -o obj/main.o

obj/pacote.o: src/pacote.cpp include/pacote.hpp | obj
	g++ $(CFLAGS) -c src/pacote.cpp -o obj/pacote.o

obj/armazem.o: src/armazem.cpp include/armazem.hpp | obj
	g++ $(CFLAGS) -c src/armazem.cpp -o obj/armazem.o

obj/rede.o: src/rede.cpp include/rede.hpp include/list.hpp | obj
	g++ $(CFLAGS) -c src/rede.cpp -o obj/rede.o

obj/escalonador.o: src/escalonador.cpp include/heap.hpp include/escalonador.hpp | obj
	g++ $(CFLAGS) -c src/escalonador.cpp -o obj/escalonador.o
