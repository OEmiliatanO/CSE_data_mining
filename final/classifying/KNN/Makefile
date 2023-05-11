CC:=g++
FLAG:=-std=c++20 -Wextra -Werror -Wall -O3
KNNSRC:=./src/
DATASRC:=../../include/

all: main.o 
	$(CC) -o main.elf main.o

dep: main.cpp
	$(CC) $(FLAG) -I$(KNNSRC) -I$(DATASRC) -c main.cpp

clean:
	-rm *.o
