CC = g++
RM = /bin/rm -f
all: rocks
rocks: rocks.o utilities.o
	$(CC) -o rocks rocks.o utilities.o
rocks.o: rocks.cpp
	$(CC) -c rocks.cpp
utilities.o: utilities.cpp
	$(CC) -c utilities.cpp
clean:
	$(RM) *.o rocks
