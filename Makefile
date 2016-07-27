CC=gcc -std=c99 -Wall -g $(CFLAGS)

pipeserve: pipeserve.c list.h list.c buffer.h buffer.c
	$(CC) -o pipeserve pipeserve.c list.c buffer.c

clean:
	rm pipeserve

.phony: clean
