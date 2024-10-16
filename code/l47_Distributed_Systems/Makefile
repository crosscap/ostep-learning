CC     := gcc
CFLAGS := -Wall -Werror

SRCS   := client.c \
	server.c

OBJS   := ${SRCS:c=o}
PROGS  := ${SRCS:.c=}

.PHONY: all clean
all: ${PROGS}

${PROGS} : % : %.o Makefile
	${CC} $< -o $@ udp.c

%.o: %.c Makefile
	${CC} ${CFLAGS} -c $<

clean:
	rm -f ${PROGS} ${OBJS}
