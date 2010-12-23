CC=g++
CFLAGS=-W -Wall -Wextra -ansi -pedantic -Wno-write-strings -g
LDFLAGS=
APPLEFLAGS=-framework GLUT -framework OPENGL
EXEC=C8E

SRC_DIR=src/
BIN_DIR=bin/

all: $(BIN_DIR)$(EXEC)

$(BIN_DIR)$(EXEC): $(BIN_DIR)C8E.o $(BIN_DIR)Logs.o $(BIN_DIR)Memory.o $(BIN_DIR)CartridgeReader.o $(BIN_DIR)Display.o
	$(CC) -o $@ $(APPLEFLAGS) $^ $(CFLAGS)

$(BIN_DIR)%.o: $(SRC_DIR)%.c
	$(CC) -o $@ -c $< $(CFLAGS)


clean:
	rm -f $(BIN_DIR)*.o

mrproper: clean
	rm -f $(BIN_DIR)$(EXEC)
