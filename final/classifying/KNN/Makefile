CC:=g++
FLAG:=-std=c++20 -Wextra -Werror -Wall -O3
LINKPATH:=../lib

all: main.o 
	$(CC) -o main.elf main.o

dep: main.cpp
	$(CC) $(FLAG) -c main.cpp

clean:
	-rm *.o
