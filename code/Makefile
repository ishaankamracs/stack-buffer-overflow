CC = gcc
CFLAGS = -O0 -g -fno-stack-protector

all: login login_addresses

login: login.c
	$(CC) $(CFLAGS) -o login login.c

login_addresses: login_addresses.c
	$(CC) $(CFLAGS) -o login_addresses login_addresses.c

clean:
	rm -f login login_addresses
