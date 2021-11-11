CC=gcc
CFLAGS=-std=c99 -Wall -Wextra
TARGET_DIR=/usr/local/bin

all: steam

steam: main.o
		$(CC) -o steam main.o

main.o: main.c
		$(CC) $(CFLAGS) -DTARGET_DIR=$(TARGET_DIR) -c main.c

clean:
		rm *.o steam

install: steam steam-chroot 
		install -d $(TARGET_DIR)
		install -s -g root -m 6111 steam -t $(TARGET_DIR)
		install -g root -m 755 steam-chroot -t $(TARGET_DIR)
		desktop-file-install --dir /usr/local/share/applications --rebuild-mime-info-cache --remove-key Icon --set-key Exec --set-value '$(TARGET_DIR)/steam %U' steam.desktop

uninstall:
		rm -f $(TARGET_DIR)/steam
		rm -f $(TARGET_DIR)/steam-chroot
		rm -f /usr/local/share/applications/steam.desktop
		update-desktop-database

.PHONY: all clean uninstall install
