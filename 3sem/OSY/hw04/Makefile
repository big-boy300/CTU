CC=clang
CFLAGS+= -Wall -g -O2
EXTRA_CFLAGS?=-fsanitize=address -fno-omit-frame-pointer
HW=prod-cons

$(HW): prod-cons.c
	$(CC) -pthread $(CFLAGS) $(EXTRA_CFLAGS) prod-cons.c -o $(HW)

clean:
	rm $(HW)
