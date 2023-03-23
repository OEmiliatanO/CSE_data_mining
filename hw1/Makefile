CC:=g++

all: main.o
	$(CC) -o main.elf
dep: main.cpp
	$(CC) -Wextra -Werror -Wall -O3 -c main.cpp
clean:
	-rm *.o
