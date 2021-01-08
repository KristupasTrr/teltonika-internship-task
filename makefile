OBJS = main.c
CFLAG = -Wall
CC = gcc
.PHONY : all

all:clean main

clean:
	$(RM) main

main: ${OBJS}
	${CC} ${CFLAG} $< -o $@ 
