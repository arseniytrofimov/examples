COMPILER=g++
FLAGS=-fsanitize=undefined,address

all: main

try:
	-clear
	-rm main
	$(COMPILER) $(FLAGS) matrix.cpp matrix.hpp main.cpp -g -o main
	./main

main: matrix.o main.o
	$(COMPILER) $(FLAGS) matrix.o main.o -g -o main


main.o: main.cpp
	g++ -c main.cpp

matrix.o: matrix.cpp matrix.hpp
	g++ -c matrix.cpp matrix.hpp


test:
	-rm main
	$(COMPILER) $(FLAGS) matrix.cpp matrix.hpp test1.cpp -g
	-./a.out
	$(COMPILER) $(FLAGS) matrix.cpp matrix.hpp test2.cpp -g
	-./a.out
	$(COMPILER) $(FLAGS) matrix.cpp matrix.hpp test3.cpp -g
	-./a.out
	-rm a.out
	-rm -rf *.o
	-rm *.hpp.gch
	-rm -rf *.dSYM


clean:
	-rm
	-rm main
	-rm a.out
	-rm -rf *.o
	-rm *.hpp.gch
	-rm -rf *.dSYM
	-clear
