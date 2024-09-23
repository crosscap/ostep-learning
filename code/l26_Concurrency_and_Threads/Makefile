.PHONY: all clean
files = t0 t1

all: $(files)

$(files): %: %.c
	gcc -o $@ $< -Wall

clean:
	rm -f $(files)
