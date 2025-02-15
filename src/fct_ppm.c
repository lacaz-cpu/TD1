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
    fscanf(fic,"%d",&w);
    fscanf(fic,"%d",&h);
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
    fprintf(fic,"%d %d \n%d\n",p->width,p->height,p->max_value);
    for(int i = 0; i < p->height;i++){
        for(int j = 0;j < p->width;j++){
            fprintf(fic , "%hhu\n%hhu\n%hhu\n",p->pixels[i][j].r,p->pixels[i][j].g,p->pixels[i][j].b);
        } 
    }
    return 0;
}

ppm *  ppm_read_bin(char * fname){
    FILE * fic = fopen(fname,"rb");
    char c[2];
    int h,w,m;
    unsigned char car;
    fscanf(fic,"%s",c);
    if(c[1] != '6'){
        return NULL;
    }
    fscanf(fic,"%d",&w);
    fscanf(fic,"%d",&h);
    fscanf(fic,"%d",&m);
    ppm * p = ppm_alloc(h,w,m);
    fread(&car,sizeof(unsigned char),1,fic);
    for(int i = 0; i < p->height;i++){
        for(int j = 0;j < p->width;j++){
            fread(&p->pixels[i][j],sizeof(rgb),p->height*p->width,fic);
        } 
    }
    return p;
}

void ppm_write_bin(char * fname,ppm * p){
    FILE * fic = fopen(fname, "wb");
    fprintf(fic,"P6\n");
    fprintf(fic,"%d %d \n%d\n",p->width,p->height,p->max_value);
    for(int i = 0; i < p->height;i++){
        for(int j = 0;j < p->width;j++){
            fwrite(&p->pixels[i][j],sizeof(rgb),1,fic);
        } 
    }
}

void ppm_negative(ppm * src, ppm **dst){
    (*dst) = ppm_alloc(src->height,src->width,src->max_value);
    for(int i = 0; i < src->height;i++){
        for(int j = 0;j < src->width;j++){
            (*dst)->pixels[i][j].r = src->max_value -(src->pixels[i][j].r);
            (*dst)->pixels[i][j].g = src->max_value -(src->pixels[i][j].g);
            (*dst)->pixels[i][j].b = src->max_value -(src->pixels[i][j].b);
        }
    }
}

void ppm_extract(char * fname,ppm * ppm_t,int dx, int dy,int height,int width){
    ppm * p = ppm_alloc(height,width,ppm_t->max_value);
    for(int i = 0;i < height;i++){
        for(int j = 0;j < width;j++){
            p->pixels[i][j] = ppm_t->pixels[dx+i][dy+j];
        }
    }
    ppm_write_asc(fname,p);
}

unsigned char ** ppm_get_histogram(ppm * ppm_t){
    unsigned char ** hist = (unsigned char**)malloc(3*sizeof(unsigned char*));
    for(int i = 0; i < 3;i++)
        hist[i] = (unsigned char*)malloc(ppm_t->max_value*sizeof(unsigned char));
    for(int i = 0; i < ppm_t->height;i++){
        for(int j = 0;j < ppm_t->width;j++){
            hist[0][ppm_t->pixels[i][j].r];
            hist[0][ppm_t->pixels[i][j].g];
            hist[0][ppm_t->pixels[i][j].b];
        } 
    }
    return hist;
}

void ppm_write_histogram(ppm * p,char * fname){

}

int main(){
    ppm * p = ppm_read_asc("/home/lacaz/Bureau/TD1/src/eye_s_asc.ppm");
    /*
    ppm_write_asc("./bin/teton.ppm",p);
    ppm_write_bin("/home/lacaz/Bureau/TD1/bin/teton_bin.ppm",p);
    ppm * t = ppm_read_bin("/home/lacaz/Bureau/TD1/bin/teton_bin.ppm");
    ppm * tkt;
    ppm_negative(t,&tkt);
    ppm_write_asc("./bin/test.ppm",tkt);
    ppm_extract("./bin/test.ppm",p,20,20,250,250);
    */
    return 0;
}