.PHONY: all clean

files = main-race-delete main-race-add-one main-race-add-two

all: $(files)

$(files): % : %.c
	gcc -o $@ $< -Wall

clean:
	rm -f $(files)
