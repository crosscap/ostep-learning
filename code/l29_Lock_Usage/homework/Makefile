CC     := gcc
CFLAGS := -Wall -Werror -I../include -pthread

SRCS   := p2.c p3.c p4.c p5.c p6.c
PROGS  := ${SRCS:.c=}

.PHONY: all clean
all: ${PROGS}

${PROGS} : % : %.c Makefile
	${CC} $< -o $@ ${CFLAGS}

clean:
	rm -f ${PROGS}
