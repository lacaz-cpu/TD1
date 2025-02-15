#include <stdio.h>
#include <stdlib.h>


typedef struct rgb{
    unsigned char r, g, b;
}rgb;

typedef struct ppm{
    int height,width,max_value;
    rgb ** pixels;
}ppm;