#include "fct_ppm.h"

ppm * ppm_alloc(int height,int width,int max_value){
    ppm * ppm_t = (ppm*)malloc(sizeof(ppm));
    ppm_t->height = height;
    ppm_t->width = width;
    ppm_t->max_value = max_value;
    ppm_t->pixels = (rgb**)malloc(height*sizeof(rgb*));
    for(int i = 0;i < height;i++){  
        ppm_t->pixels[i] = (rgb*)malloc(width*sizeof(rgb));
        for(int j = 0; j <width ; j ++)
            ppm_t->pixels[i][j].r = ppm_t->pixels[i][j].g = ppm_t->pixels[i][j].b = max_value; 
    }
    return ppm_t;
} 

void ppm_free(ppm * ppm_t){
    for(int i = 0; i < ppm_t->height;i++)
        free(ppm_t->pixels[i]);
    free(ppm_t->pixels);
    free(ppm_t);
}

int main(){
    return 0;
}