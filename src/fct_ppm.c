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

void sup_input(FILE * fichier){
	char car;
	fscanf(fichier, "%c",&car);
	while(car != '\n'){
		fscanf(fichier,"%c",&car);
	}
}

ppm *  ppm_read_asc(char * fname){
    FILE * fic = fopen(fname,"r");
    char c[2];
    int h,w,m;
    fscanf(fic,"%s",c);
    if(c[1] != '3'){
        return NULL;
    }
    sup_input(fic);
    sup_input(fic);
    fscanf(fic,"%d",&h);
    fscanf(fic,"%d",&w);
    fscanf(fic,"%d",&m);
    ppm * p = ppm_alloc(h,w,m);
    for(int i = 0; i < p->height; i++){
        for(int j = 0; j < p->width; j++){
            fscanf(fic,"%hhu",&(*p).pixels[i][j].r);
            fscanf(fic,"%hhu",&(*p).pixels[i][j].g);
            fscanf(fic,"%hhu",&(*p).pixels[i][j].b);
        }
    }
    return p;
}

int ppm_write_asc(char * fname, ppm * p){
    FILE * fic = fopen(fname, "w");
    if(fic == NULL)
        return 1;
    fprintf(fic ,"P3\n");
    fprintf(fic,"%d %d \n%d\n",p->height,p->width,p->max_value);
    for(int i = 0; i < p->height;i++){
        for(int j = 0;j < p->width;j++){
            fprintf(fic , "%hhu\n%hhu\n%hhu\n",p->pixels[i][j].r,p->pixels[i][j].g,p->pixels[i][j].b);
        } 
    }
    return 0;
}

int main(){
    ppm * p = ppm_read_asc("/home/lacaz/Bureau/TD1/src/eye_s_asc.ppm");
    ppm_write_asc("teton.ppm",p);
    return 0;
}