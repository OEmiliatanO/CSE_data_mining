CC:=g++
FLAG:=-std=c++23
NNCHAINSRC:=./src/
DATASRC:=../../include/

all: main.o 
	$(CC) -o main main.o

dep: main.cpp
	$(CC) $(FLAG) -I$(NNCHAINSRC) -I$(DATASRC) -c main.cpp

clean:
	-rm *.o
