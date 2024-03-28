CC = clang
CFLAGS = -Wall -Wextra -Werror -g -I. -O0 -pthread

all: mutex.c test_mutex.c
	$(CC) $(CFLAGS) -o test_mutex mutex.c test_mutex.c

clean:
	rm -f test_mutex
