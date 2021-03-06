#include "global.h"
#include "compile.h"
#include "fuse.h"

L opt = 0;
I qid = -1;
// B isReadBin = true; /* reading from binary or text files */
extern L CSV_FILE_SCALE;

#define OPT_NONE (0==opt)
#define OPT_FE   (1==opt || 3==opt)
#define OPT_FP   (2==opt || 3==opt)

#define OPT_LF   OPT_FE
#define OPT_PH   OPT_FP

static L calcIntervalPrecise(struct timeval t0, struct timeval t1){
    return (t1.tv_sec-t0.tv_sec)*1000000 + t1.tv_usec-t0.tv_usec;
}

// return: ms (Linux/MacOS)
static E calcInterval(struct timeval t0, struct timeval t1){
    return calcIntervalPrecise(t0, t1) / 1000.0;
}

#include "loadcode.h" 

void run(int n, int id){
    L n2 = n>1?n+1:1;
    E *record=(E*)malloc(sizeof(E)*n2), total=0;
    initBackend();
    initTablesByQid(id); // load all tables
    L cur = getHeapOffset();
    DOI(n2, {setHeapOffset(cur); time_clear(); record[i]=compiled_main();})
    if(n>0){
        if(n>1) { DOIa(n2, total += record[i]) }
        else { total = record[0]; }
        P("q%02d>> Run with %lld times, last %d average (ms): %g |",id,n2,n,total/n);
        DOI(n2, P(" %g",record[i])) P("\n");
    }
    else { // n==0
        P("q%02d>> Run with 1 times, average (ms): %g | %g\n",id,record[0],record[0]);
    }
    free(record);
}

int getId(char* str){
    I len=strlen(str), x=len-1;
    while(x>=0 && str[x]!='q') x--;
    if(x>=0) return atoi(str+x+1);
    else {
        EP("Not a valid executable: %s, but horse-compile-q<id> is expected\n", str);
    }
}

int main(int argc, char** argv){
    if(argc!=4){
        printf("[Usage]: %s <scale> <opt> <n>\n",argv[0]);
        exit(1);
    }
    L scale= atoi(argv[1]);
    opt    = atoi(argv[2]);
    int n  = atoi(argv[3]);
    int id = getId(argv[0]);
    if(n<0){ EP("[n]: must be >=0\n"); }
    if(opt<0 || opt>3) { EP("0: not optimized; 1: lf; 2: peephole; 3: all\n"); }
    if(scale != 1 && scale != 2 && scale!=4 && scale!=8 && scale != 16) { EP("scale must be one of 1/2/4/8/16\n"); }
    P(">> Optimized HorseIR?: %s\n", 0==opt?"no":1==opt?"lf":2==opt?"peephole":"all");
    CSV_FILE_SCALE = scale;
    run(n, id);
    return 0;
}

