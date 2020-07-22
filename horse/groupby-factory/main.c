#include <stdio.h>
#include "global.h"

V data1;

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

void loadAllData(S arg1){
    data1 = (V)malloc(sizeof(V0));
    initBackend();
    tic();
    loadData(data1, arg1);
    P("\nLoaded:\n");
    P("  data [%s] = %lld\n", arg1, vn(data1));
    P("\n");
    // printV(data1);
    // DOI(4, printV(vV(data1,i)));
    // getchar();
    time_toc("Data loading time (ms): %g\n", elapsed);
}

#include "groupby-k0.h"

int main(int argc, char **argv){
    // printf("argc = %d\n", argc);
    if(argc == 3){
        loadAllData(argv[1]);
        I strategy = atoi(argv[2]);
        switch(strategy){
            case 0: run_groupby_k0();  break;
            default: EP("Unknown strategy number: %d\n", strategy);
        }
    }
    else {
        P("Usage: %s <data> <strategy>\n", argv[0]);
        exit(99);
    }
    return 0;
}


