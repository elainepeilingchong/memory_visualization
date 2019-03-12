#compile:
#	gcc main.c dist/functions.o -o dist/main 
default: link

link: bin/main.o bin/functions.o
	gcc bin/main.o bin/functions.o -o bin/main 

bin/main.o: main.c
	gcc main.c -o bin/main.o

bin/functions.o: lib/functions.c
	gcc -c lib/functions.c -o bin/functions.o
clean:
	rm -rf ./bin && mkdir ./bin
