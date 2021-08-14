CC=gcc
CFLAGS=-std=c99 -Wall -Wextra
TARGET_DIR=/usr/local/bin

all: steam

steam: main.o
		$(CC) -o steam main.o

main.o: main.c
		$(CC) $(CFLAGS) -c main.c

clean:
		rm *.o steam

install: steam steam-chroot 
		install -d $(TARGET_DIR)
		install -s -g root -m 6111 steam -t $(TARGET_DIR)
		install -g root -m 755 steam-chroot -t $(TARGET_DIR)

uninstall:
		rm -f /usr/local/bin/steam
		rm -f /usr/local/bin/steam-chroot

.PHONY: all clean uninstall install
