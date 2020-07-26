/*
 * version: r0
 * description: open-addressing hash (not radix-based)
 */

typedef struct r0_hash_node { // 8+4 = 12 (padding to 16)
    L h_index;
    I h_i;
}r0_HN0,*r0_HN;

typedef struct r0_hash_cell { // 8+3*16+8 = 64 (1 cache line)
    L c_total;
    r0_HN0 c_node[PRE_SIZE_CELL];
    struct r0_hash_cell *c_next;
}r0_HC0,*r0_HC;


static r0_HC* r0_createHashTable(V x, L htSize){
    r0_HC *ht = HASH_AL(r0_HC, htSize);
    memset(ht, 0, sizeof(r0_HC)*htSize);
    L htMask = htSize - 1;
    L k = 0;
    DOI(xn, {I id=hash_LL(vI(x,i)) & htMask;
            r0_HC t = ht[id];
            if(t){
                while(t->c_next) t = t->c_next;
                if(t->c_total < PRE_SIZE_CELL){
                    r0_HN r = t->c_node+t->c_total;
                    t->c_total++;
                    r->h_i     = vI(x,i);
                    r->h_index = i;
                }
                else {
                    TODO("add a new chunk");
                }
                k++;
            }
            else {
                r0_HC t0 = HASH_AL(r0_HC0, 1);
                r0_HN r = t0->c_node;
                r->h_i     = vI(x,i);
                r->h_index = i;
                t0->c_total = 1;
                t0->c_next = NULL;
                ht[id] = t0;
            }
         })
    return ht;
    // L total = 0;
    // DOI(htSize, {r0_HC t = ht[i];
    //         if(t){
    //             L c = 0;
    //             while(t){ c+=t->c_total; t=t->c_next;}
    //             P("t[%lld] = %lld\n",i,c);
    //             total += c;
    //         }
    //         })
    // P("total = %lld, xn = %lld\n", total,xn);
}

static r0_HN r0_findHashTable(r0_HC t, I v){
    while(t){
        DOI(t->c_total, {r0_HN x=t->c_node+i; if(x->h_i == v) R x;})
        t = t->c_next;
    }
    R 0;
}

static r0_HN* r0_probeHashTable(V x, r0_HC *ht, L htSize, L minX, L maxX){
    // r0_HN *tempHN = HASH_AL(r0_HN, xn);
    L *z0 = HASH_AL(L, xn);
    L *z1 = HASH_AL(L, xn);
    L htMask = htSize - 1;
    L c = 0;
    tic();
    DOI(xn, if(vI(x,i)>=minX && vI(x,i)<=maxX){
            L id=hash_LL(vI(x,i)) & htMask;
            // tempHN[i] = ht[id]?r0_findHashTable(ht[id], vI(x,i)):0;
            r0_HN t = ht[id]?r0_findHashTable(ht[id], vI(x,i)):0;
            if(t) { z0[c] = t->h_i; z0[c++] = i; }
            })
    toc();
    // L c = 0; DOI(xn, if(tempHN[i]) c++) P(" c = %lld\n", c);
     P(" c = %lld\n", c);  // 31680
     V zz0 = (V)malloc(sizeof(V0));
     V zz1 = (V)malloc(sizeof(V0));
     initV(zz0, H_L, c);
     initV(zz1, H_L, c);
     memcpy(vg(zz0), z0, sizeof(L)*c);
     memcpy(vg(zz1), z1, sizeof(L)*c);
    // return tempHN;
    return 0;
}

// static void r0_writeHashResult(V z0, V z1, r0_HN *tempHN, L size){
//     DOP(size, {vI(z0,i)=tempHN[i]->h_index;k
// }

void r0_hash_main(V z, V x, V y){
    I minX, maxX;
    if(isStrictOrder(x,&minX,&maxX)){
        L hashSize = getHashTableSize(xn);
        L matchedSize = 0;
        tic();
        r0_HC* ht = r0_createHashTable(x, hashSize);
        time_toc("r0: build time (ms): %g\n", elapsed);
        tic();
        r0_HN* tempHN = r0_probeHashTable(y, ht, hashSize, minX, maxX);
        time_toc("r0: probe time (ms): %g\n", elapsed);
        // initV(z, H_G, 2);
        // V z0 = (V)malloc(sizeof(V0));
        // V z1 = (V)malloc(sizeof(V0));
        // tic();
        // r0_writeHashResult(z0, z1, tempHN, matchedSize);
        // time_toc("r0: probe time (ms): %g\n", elapsed);
        // vV(z,0) = z0;
        // vV(z,1) = z1;

    }
    else {
        TODO("Support");
    }
}

static void check_q11_right(V x){
    L c=0;
    DOI(xn, if(vI(x,i)<33 || vI(x,i)>9990)c++)
    // size=800000, c=3360
    P("size=%lld, c=%lld\n",xn,c);
}

static void run_join_r0(){
    V rtn = (V)malloc(sizeof(V0));
    tic();
    r0_hash_main(rtn,data1,data2);
    // check_q11_right(data2);
    time_toc("join takes (ms): %g\n\n", elapsed);
}

