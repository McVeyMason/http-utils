CC = gcc
CFLAGS = -Wall -g -Wpedantic
LDFLAGS = 

.PHONY: default
defaut: libhttputils.a

utils-test: http_utils.o http_utils.h

libhttputils.a: libhttputils.a(http_utils.o)

http_utils.o: http_utils.h

.PHONY: clean
clean:
	rm -f *~ *.o .*.*~ libhttputils.a utils-test

.PHONY: all
all: clean libhttputils.a utils-test

.PHONY: test
test: utils-test
