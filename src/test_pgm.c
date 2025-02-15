#include "fct_pgm.h"


int main(){
    pgm * p = pgm_read_asc("./src/eye_s_asc.pgm");
    pgm_write_asc(p,"./bin/t.pgm");
    pgm * dst;
    pgm_negative(p,&dst);
    pgm_write_asc(dst,"./bin/test.pgm");
    pgm_extract("./bin/t.pgm",pgm_read_asc("./src/eye_s_asc.pgm"),20,20,250,250);
    return 0;
}