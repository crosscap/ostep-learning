all: test_system_call test_switch_context

test_system_call: test_system_call.c
	gcc -o test_system_call test_system_call.c -Wall

test_switch_context: test_switch_context.c
	gcc -o test_switch_context test_switch_context.c -Wall

clean:
	rm -f test_system_call test_switch_context