CC:=g++

all: main.o Data.o
	$(CC) -o main.elf main.o Data.o
dep: main.cpp Data.cpp
	$(CC) -Wextra -Werror -Wall -O3 -c main.cpp
	$(CC) -Wextra -Werror -Wall -O3 -c Data.cpp
clean:
	-rm *.o
