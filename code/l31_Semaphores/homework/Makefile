CC     := gcc
CFLAGS := -Wall -Werror -I../include -pthread

OS     := $(shell uname -s)
LIBS   :=
ifeq ($(OS),Linux)
	LIBS += -pthread
endif

SRCS   := \
    fork-join.c \
	rendezvous.c \
	barrier.c \
	reader-writer.c \
	reader-writer-nostarve.c \
	mutex-nostarve.c

OBJS   := ${SRCS:c=o}
PROGS  := ${SRCS:.c=}

.PHONY: all clean
all: ${PROGS}

%.o: %.c Makefile
	${CC} ${CFLAGS} -c $<

${PROGS} : % : %.o Makefile
	${CC} $< -o $@ ${LIBS}

clean:
	rm -f ${PROGS} ${OBJS}
