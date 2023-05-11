CC:=g++
FLAG:=-std=c++20 -Wextra -Werror -Wall -O3
SVMSRC:=./src/
DATASRC:=../../include/

all: main.o 
	$(CC) -o main.elf main.o

dep: main.cpp
	$(CC) $(FLAG) -I$(SVMSRC) -I$(DATASRC) -c main.cpp

clean:
	-rm *.o
