CC="gcc"
all: parse.o 
	$(CC) -o main src/main.c  src/parse.o 
parse.o: 
	$(CC) -c src/parse.c -o src/parse.o

clean:
	rm -rf main src/*.o
