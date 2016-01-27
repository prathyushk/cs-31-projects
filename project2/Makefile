CC = g++
RM = /bin/rm -f
all: royalty
royalty: royalty.o
	$(CC) -o royalty royalty.o
royalty.o: royalty.cpp
	$(CC) -c royalty.cpp
clean:
	$(RM) *.o royalty
