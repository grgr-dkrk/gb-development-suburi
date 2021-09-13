CC	= $${HOME}/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG
SRC = src/
BUILD = build/
RELEASE = release/

all:
	$(CC) -c -o $(BUILD)main.o $(SRC)main.c
	$(CC) -o $(RELEASE)rom.gb $(BUILD)main.o

