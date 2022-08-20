CC=gcc
CFLAGS+= -Wall
EXTRA_CFLAGS=
HW=forkpipe
NSD=nsd

all: $(NSD) $(HW)

$(HW): forkpipe.o
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) forkpipe.c -o $(HW)

forkpipe.o: forkpipe.c
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -c forkpipe.c

$(NSD): nsd_main.o nd.o nsd.o nd.h nsd.h
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) nsd_main.o nd.o nsd.o -o $(NSD)

nsd_main.o: nsd_main.c
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -c nsd_main.c

nsd.o: nsd.c
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -c nsd.c 

nd.o: nd.c
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -c nd.c

clean:
	rm *.o $(NSD) $(HW) 
