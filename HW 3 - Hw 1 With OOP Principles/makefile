all: prog

prog: main.o CPU.o CPUProgram.o instructionFuctions.o
	g++ main.o CPU.o CPUProgram.o instructionFuctions.o -o prog

main.o: main.cpp
	g++ -c -ansi -pedantic -errors --std=c++11 main.cpp

CPU.o: CPU.cpp
	g++ -c -ansi -pedantic -errors --std=c++11 CPU.cpp
	
CPUProgram.o: CPUProgram.cpp
	g++ -c -ansi -pedantic -errors --std=c++11 CPUProgram.cpp
	
instructionFuctions.o: instructionFuctions.cpp
	g++ -c -ansi -pedantic -errors --std=c++11 instructionFuctions.cpp

clean:
	rm *.o prog
