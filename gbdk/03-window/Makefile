CC	= $${HOME}/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG
SRC = src/
BUILD = build/
RELEASE = release/
STRUCTS = structs/

all:
	$(CC) -c -o $(BUILD)global.o $(SRC)global.c
	$(CC) -c -o $(BUILD)Player.o $(SRC)$(STRUCTS)Player.c
	$(CC) -c -o $(BUILD)Enemy.o $(SRC)$(STRUCTS)Enemy.c
	$(CC) -c -o $(BUILD)main.o $(SRC)main.c
	$(CC) -o $(RELEASE)rom.gb $(BUILD)main.o $(BUILD)global.o $(BUILD)Player.o $(BUILD)Enemy.o

