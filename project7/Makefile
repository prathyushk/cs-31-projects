CC = g++
RM = /bin/rm -f
all: robots
robots: robots.o
	$(CC) -o robots robots.o
robots.o: robots.cpp
	$(CC) -c robots.cpp
clean:
	$(RM) *.o robots
