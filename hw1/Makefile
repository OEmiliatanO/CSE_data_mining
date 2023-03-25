CC:=g++

all: main.o Data.o Brute.o Dataloader.o KNN.o
	$(CC) -o main.elf main.o Data.o
dep: main.cpp Data.cpp Brute.cpp Dataloader.cpp KNN.cpp
	$(CC) -Wextra -Werror -Wall -O3 -c main.cpp
	$(CC) -Wextra -Werror -Wall -O3 -c Data.cpp
	$(CC) -Wextra -Werror -Wall -O3 -c Brute.cpp
	$(CC) -Wextra -Werror -Wall -O3 -c Dataloader.cpp
	$(CC) -Wextra -Werror -Wall -O3 -c KNN.cpp
clean:
	-rm *.o
