CC = cc
CFLAGS = -std=c11 -Wall -Wextra -Werror -pedantic -O0 -g

all: demo

demo: demo.c size_check.c size_check.h
	$(CC) $(CFLAGS) demo.c size_check.c -o demo

test_size: test_size.c size_check.c size_check.h
	$(CC) $(CFLAGS) test_size.c size_check.c -o test_size

test: test_size
	./test_size

sanitize:
	$(CC) $(CFLAGS) -fsanitize=address,undefined demo.c size_check.c -o demo_san
	./demo_san
	$(CC) $(CFLAGS) -fsanitize=address,undefined test_size.c size_check.c -o test_san
	./test_san

.PHONY: all test sanitize
