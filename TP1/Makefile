CFLAGS = -I include

all: output

output: obj/main.o obj/heap.o
	g++ -o bin/pa3 obj/main.o obj/heap.o

obj/main.o: ./src/main.cpp ./include/heap.h | obj
	g++ $(CFLAGS) -c ./src/main.cpp -o obj/main.o

obj/heap.o: ./src/heap.cpp ./include/heap.h | obj
	g++ $(CFLAGS) -c ./src/heap.cpp -o obj/heap.o 
