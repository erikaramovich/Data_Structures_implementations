all: main

main: main.o
	g++ main.o -o main 

main.o: main.cpp custom_vector.hpp
	g++ -c main.cpp -o main.o

clean:
	rm -f main.o main
