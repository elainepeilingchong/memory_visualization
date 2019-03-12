compile:
	gcc main.c dist/my-functions.o -o dist/main 
link:dist dist/main.o, dist/functions.o
	gcc dist/main.o dist/functions.o -o dist/main 

dist/main.o: main.c
	gcc main.c -o dist/main.o
	
dist/functions.o: lib/functions.c
	gcc -c lib/functions.c -o dist/functions.o
clean:
	rm -rf ./dist && mkdir ./dist