CC:=g++
FLAG:=-std=c++20 -Wextra -Werror -Wall -O3
LINKPATH:=../lib

all: main.o $(LINKPATH)/Data.o $(LINKPATH)/Dataloader.o $(LINKPATH)/Datatransformer.o decision_tree.o DT_criterion.o
	$(CC) -o main.elf main.o $(LINKPATH)/Data.o $(LINKPATH)/Dataloader.o $(LINKPATH)/Datatransformer.o decision_tree.o DT_criterion.o

dep: main.cpp decision_tree.cpp DT_criterion.cpp
	$(CC) $(FLAG) -c main.cpp
	$(CC) $(FLAG) -c decision_tree.cpp
	$(CC) $(FLAG) -c DT_criterion.cpp

clean:
	-rm *.o
