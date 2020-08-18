CC=g++

all: build

build: main.cpp Recursive_descent-calculator.cpp Recursive_descent-calculator.h
	$(CC) -c main.cpp Recursive_descent-calculator.cpp
	$(CC) -o calculator main.o Recursive_descent-calculator.o

run: main.cpp Recursive_descent-calculator.cpp Recursive_descent-calculator.h
	$(CC) -c main.cpp Recursive_descent-calculator.cpp
	$(CC) -o calculator main.o Recursive_descent-calculator.o
	./calculator

test: main.cpp Recursive_descent-calculator.cpp Recursive_descent-calculator.h
	$(CC) -c main.cpp Recursive_descent-calculator.cpp
	$(CC) -o calculator main.o Recursive_descent-calculator.o
	./run_test.bash

main.o: main.cpp Recursive_descent-calculator.h
	$(CC) -c main.cpp

square.o: Recursive_descent-calculator.cpp Recursive_descent-calculator.h
	$(CC) -c Recursive_descent-calculator.cpp

clean:
	rm -rf *.o calculator
