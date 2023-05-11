CC:=g++
FLAG:=-std=c++20 -Wextra -Werror -Wall -O3
KMEANSSRC:=./src/
DATASRC:=../../include/

all: main.o 
	$(CC) -o main.elf main.o

dep: main.cpp
	$(CC) $(FLAG) -I$(KMEANSSRC) -I$(DATASRC) -c main.cpp

clean:
	-rm *.o
