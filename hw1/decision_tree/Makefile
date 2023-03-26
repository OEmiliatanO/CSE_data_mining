CC:=g++

all: main.o Data.o Dataloader.o decision_tree.o
	$(CC) -o main.elf main.o Data.o Dataloader.o decision_tree.o
dep: main.cpp Data.cpp Dataloader.cpp decision_tree.cpp
	$(CC) -Wextra -Werror -Wall -O3 -c main.cpp
	$(CC) -Wextra -Werror -Wall -O3 -c Data.cpp
	$(CC) -Wextra -Werror -Wall -O3 -c Dataloader.cpp
	$(CC) -Wextra -Werror -Wall -O3 -c decision_tree.cpp
clean:
	-rm *.o
