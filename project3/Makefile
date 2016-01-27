CC = g++
RM = /bin/rm -f
all: mazeprog
mazeprog: maze.o grid.o
	$(CC) -o maze maze.o grid.o
maze.o: maze.cpp
	$(CC) -c maze.cpp
grid.o: grid.cpp
	$(CC) -c grid.cpp
clean: $(RM) *.o maze
