objects = null malloc out_of_range print_freed vector
all: $(objects)

null: null.c
	gcc -g -o null null.c -Wall

malloc: malloc.c
	gcc -g -o malloc malloc.c -Wall

out_of_range: out_of_range.c
	gcc -g -o out_of_range out_of_range.c -Wall

print_freed: print_freed.c
	gcc -g -o print_freed print_freed.c -Wall

interst_free: interst_free.c
	gcc -g -o interst_free interst_free.c -Wall

vector: vector.c
	gcc -g -o vector vector.c -Wall

clean:
	rm -f $(objects) interst_free