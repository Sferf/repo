CXX=g++
sanitizers=-fsanitize=leak

main: main.cpp string.h program
	$(CXX) main.cpp -o main

program: tester.o tests.o
	$(CXX)    $(sanitizers) tester.o tests.o -o program

tester.o: tester.cpp
	$(CXX) -c $(sanitizers) tester.cpp -o tester.o

tests.o: tests.h tests.cpp
	$(CXX) -c $(sanitizers) tests.cpp -o tests.o

clean:
	rm tests.o
	rm tester.o
	rm program
	rm main
