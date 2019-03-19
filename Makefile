default: link

link:dist dist/main.o dist/map_lib.o dist/functions.o
	gcc dist/main.o dist/functions.o -o dist/main 

dist/main.o: main.c
	gcc -c -Wall main.c -o dist/main.o
	
dist/functions.o: lib/functions.c
	gcc -c -Wall lib/functions.c -o dist/functions.o

dist/map_lib.o: lib/map_lib.c
	gcc -c -Wall lib/map_lib.c -o dist/map_lib.o

clean:
	rm -rf ./dist && mkdir ./dist
