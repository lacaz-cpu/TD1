CC = gcc
CFLAGS = -Wall -c -std=c99
SRC_DIR = src/
OBJ_DIR = obj
BIN = bin/
INC = -I include/
EXE = build

all: $(EXE)

fct_pgm.o: $(SRC_DIR)fct_pgm.c 
	$(CC) $(CFLAGS)  $< -c $(INC) -o $(OBJ_DIR)/$@

test_pgm.o: $(SRC_DIR)test_pgm.c 
	$(CC) $(CFLAGS)  $< -c $(INC) -o $(OBJ_DIR)/$@

fct_ppm.o: $(SRC_DIR)fct_ppm.c
	$(CC) $(CFLAGS)  $< -c $(INC) -o $(OBJ_DIR)/$@


ppm : fct_ppm.o fct_pgm.o 
	$(CC) $(OBJ_DIR)/* -o $@ 

pgm : fct_pgm.o test_pgm.o 
	$(CC) $(OBJ_DIR)/* -o $@ 

clean : 
	rm -f ppm 
	rm -f pgm
	rm -rf $(OBJ_DIR)/*
	rm -rf $(BIN)*