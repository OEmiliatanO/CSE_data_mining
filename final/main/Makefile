CC:=g++
FLAG:=-std=c++20 -Wextra -Werror -Wall -O3
KNNSRC:=../classifying/KNN/src/
SVMSRC:=../classifying/SVM/src/
DBSCANSRC:=../clustering/DBSCAN/src/
KMEANSSRC:=../clustering/kmeans/src/
DATASRC:=../include/
ARGPARSERSRC:=../argparser/

all: main.o 
	$(CC) -o main.elf main.o

dep: main.cpp
	$(CC) $(FLAG) -I$(KNNSRC) -I$(SVMSRC) -I$(DBSCANSRC) -I$(KMEANSSRC) -I$(DATASRC) -I$(ARGPARSERSRC) -c main.cpp

clean:
	-rm *.o
