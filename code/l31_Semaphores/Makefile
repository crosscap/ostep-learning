CC     := gcc
CFLAGS := -Wall -Werror -I../include -pthread

OS     := $(shell uname -s)
LIBS   :=
ifeq ($(OS),Linux)
	LIBS += -pthread
endif

SRCS   := \
    binary.c \
	join.c \
	producer_consumer_works_deadlock.c \
	producer_consumer_works.c \
	rwlock.c \
	dining_philosophers_deadlock.c \
	dining_philosophers_no_deadlock.c

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
