#The code below is taken from moodle 
#Operating System module: Make Files (Makefile):Resource: Makefile Version 2 (Variables)
#https://2019-moodle.dkit.ie/course/view.php?id=8732
CC      = gcc
CFLAGS  = -c -Wall
LIBDIR  = lib
BINDIR  = dist
OBJECTS = $(BINDIR)/main.o\
										$(BINDIR)/functions.o

default: link

link: $(OBJECTS)
	$(CC) $? -o $(BINDIR)/stimulate

$(BINDIR)/main.o: main.c
	$(CC) $(CFLAGS) main.c -o $(BINDIR)/main.o

$(BINDIR)/functions.o: $(LIBDIR)/functions.c
	$(CC) $(CFLAGS) $(LIBDIR)/functions.c -o $(BINDIR)/functions.o

clean:
	rm -rf ./$(BINDIR) && mkdir $(BINDIR)

