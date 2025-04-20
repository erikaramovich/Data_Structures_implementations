all: stack

stack: stack.o
	g++ stack.o -o stack

stack.o: stack.cpp
	g++ -c stack.cpp -o stack.o

clean:
	rm -f stack.o stack

