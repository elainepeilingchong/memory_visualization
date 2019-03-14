<<<<<<< HEAD
default: link

link:dist dist/main.o dist/functions.o
	gcc dist/main.o dist/functions.o -o dist/main 

dist/main.o: main.c
	gcc -c -Wall main.c -o dist/main.o
	
dist/functions.o: lib/functions.c
	gcc -c -Wall lib/functions.c -o dist/functions.o
	
=======
#compile:
#	gcc main.c dist/functions.o -o dist/main 
default: link

link: bin/main.o bin/functions.o
	gcc bin/main.o bin/functions.o -o bin/main 

bin/main.o: main.c
	gcc main.c -o bin/main.o

bin/functions.o: lib/functions.c
	gcc -c lib/functions.c -o bin/functions.o
>>>>>>> master
clean:
	rm -rf ./bin && mkdir ./bin
