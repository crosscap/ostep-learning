CC     := gcc
CFLAGS := -Wall -Werror -I../include -pthread

OS     := $(shell uname -s)
LIBS   :=
ifeq ($(OS),Linux)
	LIBS += -pthread
endif

SRCS   := mystat.c myls.c mytile.c myfind.c

OBJS   := ${SRCS:c=o}
PROGS  := ${SRCS:.c=}

.PHONY: all clean

all: ${PROGS}

${PROGS} : % : %.o Makefile
	${CC} $< -o $@ ${LIBS}

%.o: %.c Makefile
	${CC} ${CFLAGS} -c $<

clean:
	rm -f ${PROGS} ${OBJS}
