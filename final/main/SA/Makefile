CC:=g++
FLAG:=-std=c++20 -Wextra -Werror -Wall -O3
ARGPARSERSRC:=../../argparser/

all: main.o 
	$(CC) -o main.elf main.o

dep: main.cpp
	$(CC) $(FLAG) -I$(ARGPARSERSRC) -c main.cpp

clean:
	-rm *.o
