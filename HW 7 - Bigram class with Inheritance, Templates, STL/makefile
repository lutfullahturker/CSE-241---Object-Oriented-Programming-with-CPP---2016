all: exe

exe: _mainTester.o
	g++ _mainTester.o -o exe

main.o: main.cpp
	g++ -c -ansi -pedantic -errors --std=c++11 main.cpp
	
_mainTester.o: _mainTester.cpp
	g++ -c -ansi -pedantic -errors --std=c++11 _mainTester.cpp


	
clean:
	rm *.o exe
