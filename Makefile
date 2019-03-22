#The code below is taken from moodle 
CC      = gcc
CFLAGS  = -c -Wall
LIBDIR  = lib
BINDIR  = dist
OBJECTS = dist dist/main.o dist/functions.o

default: link

link: $(OBJECTS)
	$(CC) $? -o $(BINDIR)/simulate

$(BINDIR)/main.o: main.c
	$(CC) $(CFLAGS) main.c -o $(BINDIR)/main.o

$(BINDIR)/functions.o: $(LIBDIR)/functions.c
	$(CC) $(CFLAGS) $(LIBDIR)/functions.c -o $(BINDIR)/functions.o

clean:
	rm -rf ./$(BINDIR) && mkdir $(BINDIR)

