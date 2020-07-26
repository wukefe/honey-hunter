/*
 * version: r1
 * description: closed-addressing hash (not radix-based)
 */

typedef struct r1_hash_node { // 8*3+8=32
    C h_status;
    L h_index;
    I h_i;
}r1_HN0,*r1_HN;

static r1_HN r1_createHashTable(V x, L htSize){
    r1_HN ht = HASH_AL(r1_HN0, htSize);
    memset(ht, 0, sizeof(r1_HN0)*htSize);
    L htMask = htSize - 1;
    DOI(xn, {I id=hash_LL(vI(x,i)) & htMask;
            r1_HN t = ht+id;
            while(t->h_status){
                id++;
                id = id == htSize ? 0 : id;
                t = ht+id;
            }
            t->h_status = 1;
            t->h_index  = i;
            t->h_i      = vI(x,i);
            })
    return ht;
    // L total = 0;
    // DOI(htSize, {r1_HC t = ht[i];
    //         if(t){
    //             L c = 0;
    //             while(t){ c+=t->c_total; t=t->c_next;}
    //             P("t[%lld] = %lld\n",i,c);
    //             total += c;
    //         }
    //         })
    // P("total = %lld, xn = %lld\n", total,xn);
}

static r1_HN r1_findHashTable(r1_HN ht, L id, I v, I htSize){
    r1_HN t = ht+id;
    while(t->h_status){
        if(t->h_i == v) R t;
        if(++id == htSize) id=0;
        t = ht + id;
    }
    R 0;
}

static r1_HN* r1_probeHashTable(V x, r1_HN ht, L htSize){
    r1_HN *tempHN = HASH_AL(r1_HN, xn);
    L htMask = htSize - 1;
    L c = 0;
    DOI(xn, {L id=hash_LL(vI(x,i)) & htMask;
            r1_HN start=ht+id;
            // tempHN[i] = ht[id]?r1_findHashTable(ht[id], vI(x,i)):0;
            if(start->h_status){
                r1_HN t = r1_findHashTable(ht, id, vI(x,i), htSize);
                if(t) tempHN[c++] = t;
            }
            })
    // P(" c = %lld\n", c);
    return tempHN;
}

void r1_hash_main(V z, V x, V y){
    I minX, maxX;
    if(isStrictOrder(x,&minX,&maxX)){
        L hashSize = getHashTableSize(xn);
        tic();
        r1_HN ht = r1_createHashTable(x, hashSize);
        time_toc("r1: build time (ms): %g\n", elapsed);
        tic();
        r1_HN *tempHN = r1_probeHashTable(y, ht, hashSize);
        time_toc("r1: probe time (ms): %g\n", elapsed);
    }
    else {
        TODO("Support");
    }
}

static void run_join_r1(){
    V rtn = (V)malloc(sizeof(V0));
    tic();
    r1_hash_main(rtn,data1,data2);
    time_toc("join takes (ms): %g\n\n", elapsed);
}

