CC = gcc
CFLAGS = -Wall -g -Wpedantic
LDFLAGS = 

http_utils.a: http_utils.h

.PHONY: clean
clean:
	rm -f *~ *.o .*.*~ http-utils.a

.PHONY: all
all: clean http-server
