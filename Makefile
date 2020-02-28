CC=gcc
CFLAGS=-c -Wall -g -I src
SDIR=src
BDIR=bin
ODIR=obj
EXC=mallard

all: main
	mkdir $(ODIR)
	mkdir $(BDIR)
	mv *.o $(ODIR)
	mv $(EXC) $(BDIR)

main: *.o
	$(CC) *.o -o $(EXC)
	
*.o: $(SDIR)/*.c
	$(CC) $(CFLAGS) $(SDIR)/*.c

clean:
	rm -r $(BDIR)
	rm -r $(ODIR)
