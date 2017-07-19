all: prog

prog: main.o
	g++ main.o -o prog

main.o: main.cpp
	g++ -c -ansi -pedantic -errors --std=c++11 main.cpp

clean:
	rm *.o prog
