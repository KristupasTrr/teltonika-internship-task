OBJS = linked_list.c
CFLAGS = -fpic -Wall -Wextra -pedantic -shared
CC = gcc
.PHONY : all

all:clean liblinkedlist.so

clean:
	$(RM) *.o *.so

liblinkedlist.so: ${OBJS}
	${CC} ${CFLAGS} -o $@ $<