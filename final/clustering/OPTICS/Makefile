CC:=g++
FLAG:=-std=c++20 -Wextra -Werror -Wall -O3
DBSCANSRC:=./src/
DATASRC:=../../include/

all: main.o 
	$(CC) -o main.elf main.o

dep: main.cpp
	$(CC) $(FLAG) -I$(KNNSRC) -I$(SVMSRC) -I$(DBSCANSRC) -I$(KMEANSSRC) -I$(DATASRC) -I$(ARGPARSERSRC) -c main.cpp

clean:
	-rm *.o
