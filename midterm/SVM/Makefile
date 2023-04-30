CC:=g++
FLAG:=-std=c++20 -Wextra -Werror -Wall -O3
LINKPATH:=../lib

all: main.o svm.o
	$(CC) -o main.elf main.o svm.o

dep: main.cpp svm.cpp
	$(CC) $(FLAG) -c main.cpp
	$(CC) $(FLAG) -c svm.cpp

clean:
	-rm *.o
