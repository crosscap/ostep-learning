CC     := gcc
CFLAGS := -Wall -Werror -I../include -pthread

OS     := $(shell uname -s)
LIBS   :=
ifeq ($(OS),Linux)
	LIBS += -pthread
endif

SRCS   := \
    join_spin.c \
	join_modular.c \
	join.c \
	join_no_state_var.c \
	join_no_lock.c \
	single_pc_single_cv_if.c \
	single_pc_single_cv_while.c \
	single_pc.c \
	pc_single_cv.c \
	pc.c

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
