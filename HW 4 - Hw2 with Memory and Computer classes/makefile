all: exe

exe: main.o CPU.o CPUProgram.o instructionFuctions.o Memory.o Computer.o
	g++ main.o CPU.o CPUProgram.o instructionFuctions.o Computer.o Memory.o -o exe

main.o: main.cpp
	g++ -c -ansi -pedantic -errors --std=c++11 main.cpp

CPU.o: CPU.cpp
	g++ -c -ansi -pedantic -errors --std=c++11 CPU.cpp
	
CPUProgram.o: CPUProgram.cpp
	g++ -c -ansi -pedantic -errors --std=c++11 CPUProgram.cpp
	
Computer.o: Computer.cpp
	g++ -c -ansi -pedantic -errors --std=c++11 Computer.cpp
	
Memory.o: Memory.cpp
	g++ -c -ansi -pedantic -errors --std=c++11 Memory.cpp
	
instructionFuctions.o: instructionFuctions.cpp
	g++ -c -ansi -pedantic -errors --std=c++11 instructionFuctions.cpp
	
_mainTester.o: _mainTester.cpp
	g++ -c -ansi -pedantic -errors --std=c++11 _mainTester.cpp
	

clean:
	rm *.o exe
