CC=gcc
CFLAGS=-c -Wall -g -I src
SDIR=src
BDIR=bin
ODIR=obj
EXC=mallard
MKDIR=mkdir -p

all: main $(BDIR) $(ODIR)
	mv *.o $(ODIR)
	mv $(EXC) $(BDIR)

$(BDIR):
	$(MKDIR) $@

$(ODIR):
	$(MKDIR) $@

main: *.o
	$(CC) *.o -o $(EXC)
	
*.o: $(SDIR)/*.c
	$(CC) $(CFLAGS) $(SDIR)/*.c

clean:
	rm -r $(BDIR)
	rm -r $(ODIR)
