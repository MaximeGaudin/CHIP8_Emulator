CC=g++
CFLAGS=-W -Wall -Wextra -ansi -pedantic -Wno-write-strings
LDFLAGS=
EXEC=C8E

SRC_DIR=src/
BIN_DIR=bin/

all: doc

doc: $(BIN_DIR)$(EXEC)
	doxygen >> /dev/null && \
	cd doc_tmp/latex/ && make >> /dev/null && cd ../../ && cp doc_tmp/latex/refman.pdf doc/Documentation.pdf && \
	cp -R doc_tmp/html doc/

$(BIN_DIR)$(EXEC): $(BIN_DIR)C8E.o $(BIN_DIR)Logs.o $(BIN_DIR)Memory.o
	$(CC) -o $@  $^ $(CFLAGS)

$(BIN_DIR)%.o: $(SRC_DIR)%.c
	$(CC) -o $@ -c $< $(CFLAGS)


clean:
	rm -f $(BIN_DIR)*.o

mrproper: clean
	rm -f $(BIN_DIR)$(EXEC)
