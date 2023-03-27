CC:=g++
FLAG:=-std=c++20 -Wextra -Werror -Wall -O3
LINKPATH:=../lib

all: main.o $(LINKPATH)/Data.o $(LINKPATH)/Dataloader.o $(LINKPATH)/Datatransformer.o KNN.o Brute.o 
	$(CC) -o main.elf main.o $(LINKPATH)/Data.o $(LINKPATH)/Dataloader.o $(LINKPATH)/Datatransformer.o KNN.o Brute.o

dep: main.cpp KNN.cpp Brute.cpp
	$(CC) $(FLAG) -c main.cpp
	$(CC) $(FLAG) -c KNN.cpp
	$(CC) $(FLAG) -c Brute.cpp

clean:
	-rm *.o
