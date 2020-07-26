#include <stdio.h>
#include "global.h"

V data1, data2;

B isDataList(S line){
    DOI(strlen(line), if(line[i]==' ') R 1) R 0;
}

void loadDataListInit(V x, C typ, I row){
    switch(typ){
        case 'I': initV(x, H_I, row); break;
        case 'E': initV(x, H_E, row); break;
        default: EP("Unknown type: %c",typ);
    }
}

void loadData(V x, S fn){
    FILE *fp = fopen(fn, "r");
    if(!fp){
        P("File not found: %s\n", fn);
        exit(99);
    }
    C temp[99];
    if(fgets(temp, 99, fp)){
        if(isDataList(temp)){ // load list
            I size, row;
            sscanf(temp, "%d %d", &size, &row);
            initV(x, H_G, size);
            fgets(temp, 99, fp);
            C types[99];
            DOI(size, types[i]=temp[i*2])
            DOI(size, loadDataListInit(vV(x,i), types[i], row))
            for(I i=0; i<row; i++){
                if(fgets(temp, 99, fp)){
                    S line = temp;
                    DOJ(size, { // P("line = %s\n", line); getchar();
                        switch(types[j]){
                            case 'I': sscanf(line, "%d" , sI(vV(x,j))+i); break;
                            case 'E': sscanf(line, "%lf", sE(vV(x,j))+i); break;
                        } while((*line)!=' ')line++; line++; } )
                }
            }
            P("Imported list: %d %d\n", size, row);
            // printV(x);
            // DOI(size, printV2(vV(x,i), 10))
            // P("x: size = %lld, type = %s\n", xn,getTypeName(xp));
            // DOI(size, printV(vV(x,i)))
            // getchar();
        }
        else {  // load vector
            I num = atoi(temp);
            initV(x, H_I, num);
            for(I i=0; i<num; i++){
                if(fgets(temp, 99, fp)){
                    // P("line: %s\n", temp);
                    vI(x,i) = atoi(temp);
                }
            }
        }
    }
    else {
        P("Nothing here: %s\n", fn);
        exit(99);
    }
}

void printData(I *d, I size){
    P("size = %d\n", size);
    DOI(size, P("d[%lld] = %d\n",i,d[i]))
}

void loadAllData(S arg1, S arg2){
    data1 = (V)malloc(sizeof(V0));
    data2 = (V)malloc(sizeof(V0));
    initBackend();
    tic();
    loadData(data1, arg1);
    loadData(data2, arg2);
    P("\nLoaded:\n");
    P("  left [%s] = %lld\n", arg1, vn(data1));
    P("  right[%s] = %lld\n", arg2, vn(data2));
    P("\n");
    // printV(data1);
    // printV(data2);
    // DOI(4, printV(vV(data1,i)));
    // getchar();
    time_toc("Data loading time (ms): %g\n", elapsed);
}
 
static UL hash_murmur3_i32(I a){ // default: return 64-bit
    a ^= a >> 16;
    a *= 0x85ebca6b; // 2246822507
    a ^= a >> 13;
    a *= 0xc2b2ae35; // 3266489909
    a ^= a >> 16;
    R a;
}

I foo(V x){
    I c = 0;
    P("size = %lld\n", xn);
    tic();
    DOI(xn, c+=hash_LL(vI(x,i)))  // 800K
    time_toc("foo (ms): %g\n", elapsed);
    R c;
}


// #include ""

#define JOIN_EQ initLiteralSym((S)"eq")
#define JOIN_LT initLiteralSym((S)"lt")
void run_join(){
    V rtn = (V)malloc(sizeof(V0));
    tic();
    pfnJoinIndex(rtn,data1,data2,JOIN_EQ);
    time_toc("join takes (ms): %g\n\n", elapsed);
}

typedef struct Pos_i{ I x; L i; }Pos_i;
static void local_radixsort_core_int(Pos_i *val, I len){
    const L base = 8;
    const L size = (1<<base)-1; //255
    const L maxSize = 32;
    L     *tempC = (L    *)malloc(sizeof(L    )<<base);
    Pos_i *tempB = (Pos_i*)malloc(sizeof(Pos_i)*len);
    //WP("maxSize = %d\n", maxSize);
    for(L j=0; j<maxSize; j+=base){
        memset(tempC, 0, sizeof(L)<<base);
        DOI(len, tempC[((val[i].x)>>j) & size]++)
        DOIa(size+1, tempC[i] = tempC[i] + tempC[i-1])
        //printf("j = %d\n", j);
        for(L i=len-1;i>=0;i--){
            L k = ((val[i].x)>>j) & size;
            //printf("val = %lld, k = %d\n", val[i].x,k);
            tempC[k]--;
            tempB[tempC[k]] = val[i];
        }
        memcpy(val, tempB, sizeof(Pos_i) * len);
        //for(int i=0; i<len; i++){
        //    val[i] = B[i];
        //}
    }
    free(tempB);
    free(tempC);
}

static I local_binary_search(I v, Pos_i *val, I a, I b){
    if(b >= a){
        I pivot = (a+b)>>1;
        if(v < val[pivot].x){
            R local_binary_search(v, val, a, b-1);
        }
        else if(v > val[pivot].x){
            R local_binary_search(v, val, a+1, b);
        }
        else {
            R pivot;
        }
    }
    else R -1;
}

// sort + binary = not work (too slow)
void run_join_sort(){
    V d1 = data1;
    V d2 = data2;
    I len= vn(d1);
    Pos_i *pos = (Pos_i*)malloc(sizeof(Pos_i)*len);
    DOP(len, {pos[i].x=vI(d1,i); pos[i].i=i;})
tic();
    local_radixsort_core_int(pos, len);
toc();
    DOI(20, P("pos[%lld].x = %d\n",i,pos[i].x))
    L c = 0; I len1=len-1;
tic();
    DOI(vn(d2), {I k=local_binary_search(vI(d2,i),pos,0,len1);
            //if(k>=0) { P("v = %d, index = %d\n",vI(d2,i),k); getchar(); }
            if(k>=0)c++;})
toc();
    P("c = %lld\n", c);
}

static UI getHashTableSize(L x){
    // if(x < 16) R 16;
    // L n=16; while(n>0 && n<=x){n<<=1;}
    // R n<<1;
    x <<= 1; L n=1; while(n>0 && n<x){n<<=1;}
    R n;
}

static B isStrictOrderUp(V x){
    //DOIa(xn, if(vI(x,i)<=vI(x,i-1)){P("v1=%d,v0=%d\n",vI(x,i),vI(x,i-1)); getchar(); R 0;}) R 1;
    DOIa(xn, if(vI(x,i)<=vI(x,i-1))R 0) R 1;
}

static B isStrictOrderDown(V x){
    DOIa(xn, if(vI(x,i)>=vI(x,i-1))R 0) R 1;
}

static B isStrictOrder(V x, I *minX, I *maxX){
    if(isStrictOrderUp(x)){
        *minX = vI(x,0);
        *maxX = vI(x,xn-1);
        R 1;
    }
    else if(isStrictOrderDown(x)){
        *minX = vI(x,xn-1);
        *maxX = vI(x,0);
        R 1;
    }
    R 0;
}

I simple_cmp(const void * a, const void * b) {
    return ( *(I*)a - *(I*)b );
}

/// static B isStrictUnique(V x, I *minX, I *maxX){
///     if(isStrictOrder(x,minX,maxX)){
///         R 1;
///     }
///     else{
///         P("?????\n");
///         I *temp = HASH_AL(I, xn);
///         memcpy(temp, sI(x), sizeof(I)*xn);
///         // DOI(20, P("temp1[%lld] = %d\n", i,temp[i]))
///         qsort(temp, xn, sizeof(I), simple_cmp);
///         V0 t0; V t = &t0;
///         vn(t) = xn;
///         vp(t) = H_I;
///         vg(t) = (S)temp;
///         // printV(t);
///         // DOI(20, P("temp2[%lld] = %d\n", i,temp[i]))
///         R isStrictOrder(t,minX,maxX);
///     }
/// }


#include "hash-r0.h"
#include "hash-r1.h"
#include "hash-r2.h"
#include "hash-r3.h"
#include "hash-r4.h"

int main(int argc, char **argv){
    // printf("argc = %d\n", argc);
    if(argc == 3){
        loadAllData(argv[1], argv[2]);
        // printV2(data2, 10);
        // P("foo = %d\n", foo(data2));
        run_join();
    }
    else if(argc == 4){
        loadAllData(argv[1], argv[2]);
        I strategy = atoi(argv[3]);
        switch(strategy){
            case 0: run_join();      break;
            case 1: run_join_sort(); break;
            case 2: run_join_r0();   break;
            case 3: run_join_r1();   break;
            case 4: run_join_r2();   break;
            case 5: run_join_r3();   break;
            case 6: run_join_r4();   break;
            default: EP("Unknown strategy number: %d\n", strategy);
        }
    }
    else {
        P("Usage: %s <left_data> <right_data> [strategy]\n", argv[0]);
        exit(99);
    }
    return 0;
}


