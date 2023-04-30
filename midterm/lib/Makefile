CC:=g++
SOURCE:=../source
FLAG:=-std=c++20 -Wextra -Werror -Wall -O3

dep: $(SOURCE)/Data.cpp $(SOURCE)/Dataloader.cpp $(SOURCE)/Datatransformer.cpp
	$(CC) $(FLAG) -c $(SOURCE)/Data.cpp
	$(CC) $(FLAG) -c $(SOURCE)/Dataloader.cpp
	$(CC) $(FLAG) -c $(SOURCE)/Datatransformer.cpp
	
clean:
	-rm *.o
