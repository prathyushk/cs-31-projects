CC = g++
RM = /bin/rm -f
all: array
array: array.o
	$(CC) -o array array.o
array.o: array.cpp
	$(CC) -c array.cpp
clean:
	$(RM) *.o array
