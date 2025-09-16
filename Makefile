MAIN= main.c

all: main


ObjectManager.o: ObjectManager.c ObjectManager.h
	clang++ -Wall -c -DNDEBUG ObjectManager.c -o ObjectManager.o

main: $(MAIN) ObjectManager.o    
	clang++ -Wall $(MAIN)  ObjectManager.o -o main

clean:
	rm -f ObjectManager.o main