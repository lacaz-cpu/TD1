#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct pgm{
    int height,width,max_value;
    unsigned char **pixels;
}pgm;

pgm * pgm_alloc(int height,int width, int max_value);

void pgm_free(pgm * p);

void sup_input(FILE * fichier);

pgm * pgm_read_asc(char * fname);

int pgm_write_asc(struct pgm * p, char * fname);

void pgm_negative(pgm * src , pgm ** dst);

void pgm_extract(char * fname,pgm * pgm_t,int dx,int dy,int height,int width);

unsigned char * pgm_get_histogram(pgm * p);

void pgm_write_histogram(pgm * p, char * fname );