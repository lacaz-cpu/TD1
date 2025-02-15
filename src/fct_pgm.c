#include "fct_pgm.h"


pgm * pgm_alloc(int height,int width, int max_value){
    pgm * p = (pgm*)malloc(sizeof(pgm));
    p->pixels = (unsigned char**)malloc(height*sizeof(unsigned char*));
    p->height = height;
    p->width = width;
    p->max_value = max_value;
    for(int i = 0; i < height;i ++){
        p->pixels[i] = (unsigned char*)malloc(width*sizeof(unsigned char));
        for(int j = 0; j < width; j ++)
            p->pixels[i][j] = max_value;
    }
    return p; 
}

void pgm_free(pgm * p){
    for(int i = 0; i < p->height;i ++)
        free(p->pixels[i]);
    free(p->pixels);
    free(p);
}

void sup_input(FILE * fichier){
	char car;
	fscanf(fichier, "%c",&car);
	while(car != '\n'){
		fscanf(fichier,"%c",&car);
	}
}

pgm * pgm_read_asc(char * fname){
    int height,width,max_value;
    FILE * fic = fopen(fname,"r");
    sup_input(fic);
    sup_input(fic);
    fscanf(fic,"%d",&width);
    fscanf(fic,"%d",&height);
    fscanf(fic,"%d",&max_value);
    pgm * p = pgm_alloc(height,width,max_value);
    for(int i=0;i<p->height;i++){
		for(int j = 0;j<p-> width; j++){
			fscanf(fic,"%hhu",&p->pixels[i][j]);
		}
	}
	fclose(fic);
	return p;
}

int pgm_write_asc(struct pgm * p, char * fname){
	FILE * fic;
	int i,j;
	fic = fopen(fname, "w"); 
	if(fic == NULL){
		printf("fichier non ouvert");
		return 1;
	}
	fprintf(fic , "%s","P2\n");
	fprintf(fic, "%d %d\n%d\n",(*p).width,(*p).height,(*p).max_value);
	for(i = 0 ; i < (*p).height; i ++){
		for(j = 0; j < (*p).width; j ++){
			fprintf(fic, "%hhu\n",(*p).pixels[i][j]);
		}
	}
    return 0;
}
/*
pgm * pgm_read_bin(char * fname){
    FILE * fic = fopen(fname,"rb");
    int height,width,max_value;
    fread(&height,sizeof(height),1,fname);
    
}
*/

void pgm_negative(pgm * src , pgm ** dst){
    (*dst) = pgm_alloc(src->height,src->width,src->max_value);
    for(int i = 0;i < (*dst)->height;i++){
        for(int j = 0;j < (*dst)->width;j++){
            (*dst)->pixels[i][j] = (*dst)->max_value - (src->pixels[i][j]);
        }
    }
}

void pgm_extract(char * fname,pgm * pgm_t,int dx,int dy,int height,int width){
    int i,j;
    pgm * r = pgm_alloc(height,width,pgm_t->max_value);
    for(i = 0; i < height; i++)
        for(j = 0; j < width; j++)
            r -> pixels[i][j] = pgm_t -> pixels[dx+i][dy+j];
    pgm_write_asc(r,fname);
    pgm_free(r);
}

unsigned char * pgm_get_histogram(pgm * p){
	int max = (*p).max_value + 1;
	unsigned char * tab = (unsigned char*)malloc(max*sizeof(unsigned char));
	
	int i,y;
	
	for(i = 0; i < max; i ++)
		tab[i] = 0;
	for(i = 0; i < (*p).height; i++){
		for(y = 0; y < (*p).width; y++){
			tab[p -> pixels[i][y]]++;
		}
	}
	return tab;
}
void pgm_write_histogram(pgm * p, char * fname ){
	unsigned char * t = pgm_get_histogram(p);
	int i;
	FILE *fic = NULL;
	fic = fopen(fname,"w");
	if(fic == NULL){
		printf("fichier non ouvert");
	}
	for(i = 0;i < p-> max_value + 1;i ++){
		fprintf(fic, "%d  ",i);
		fprintf(fic, "%d\n",t[i]);	
	}
	fclose(fic);
	free(t);
}
