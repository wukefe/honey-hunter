/*
 * version: r2
 * description: table lookup
 */

#ifndef DOTa
#define DOTa(n, x, ...) {L seg=(n)/H_CORE; \
    _Pragma(STRINGIFY(omp parallel __VA_ARGS__)) \
    { \
        L tid = omp_get_thread_num(); \
        L sid = tid * seg; \
        L len = (tid!=H_CORE-1)?seg:(n-sid); \
        P("tid = %lld, sid = %lld, len = %lld\n", tid, sid, len); \
        x; \
    } \
}
#endif

static L* r2_createHashTable(V x, L size){
    L *ht = HASH_AL(L, size);
    P("size = %lld, bytes = %lld\n", size, size*sizeof(L));
    tic();
    DOTa(size, memset(ht+sid, -1, sizeof(L)*len))
    // memset(ht, -1, sizeof(L)*size);
    toc();
    tic();
    DOP(xn, ht[vI(x,i)]=i)
    toc();
    R ht;
}

static void r2_probeHashTable(V x, L *ht, I minX, I maxX){
    L *p_z0 = HASH_AL(L, xn);
    L *p_z1 = HASH_AL(L, xn);
    L c = 0;
    L offset[H_CORE], part = xn/H_CORE;
    DOI(H_CORE, offset[i]=i*part)
    L ttt = 0;
    tic();
    // DOT(xn, {I v=vI(x,i);if(v>=minX && v<=maxX){
    //         L k = ht[v];
    //         if(k>=0) { ttt++; p_z0[offset[tid]] = k; p_z1[offset[tid]++] = i; }
    //         }})
    DOI(xn, {I v=vI(x,i);if(v>=minX && v<=maxX){
            if(ht[v]>=0) { c++; /*p_z0[c] = k; p_z1[c++] = i; */ }
            }})
    toc();
    P("ttt = %lld, c = %lld\n", ttt,c);
    getchar();
    tic();
    if(H_CORE > 1){
        L *t_z0 = p_z0+offset[0], *t_z1 = p_z1+offset[0];
        DOIa(H_CORE, {L pos=i*part;  L seg=offset[i]-pos;
                memcpy(t_z0, p_z0+pos, sizeof(L)*seg);
                memcpy(t_z1, p_z1+pos, sizeof(L)*seg);
                t_z0 += seg;
                t_z1 += seg;
                })
    }
    DOI(H_CORE, c+=offset[i]-i*part)
    toc();
    // DOI(xn, {I v=vI(x,i); if(v>=minX && v<=maxX){
    //         L k = ht[v];
    //         if(k>=0) { p_z0[c] = k; p_z1[c] = i; c++; }
    //         }})
    P("result: c = %lld\n", c);
    DOI(20, P("%lld ", p_z0[i])) P("\n");
    DOI(20, P("%lld ", p_z1[i])) P("\n");
}

void r2_hash_main(V z, V x, V y){
    I minX, maxX;
    if(isStrictUnique(x,&minX,&maxX)){
        P("min = %d, max = %d\n", minX, maxX);
        // if(minX > 0 && maxX < 20000){
        if(minX >= 0){
            tic();
            L *ht = r2_createHashTable(x, maxX+1);
            time_toc("r2: build time (ms): %g\n", elapsed);
            tic();
            r2_probeHashTable(y, ht, minX, maxX);
            time_toc("r2: probe + write time (ms): %g\n", elapsed);
        }
        else {
            TODO("minX = %lld, maxX = %lld\n", minX, maxX);
        }
    }
    else {
        TODO("Support");
    }
}

static B findDuplicate(V x){
    for(I i=0,i2=xn; i<i2; i++){
        for(I j=i+1,j2=xn; j<j2; j++){
            if(vI(x,i) == vI(x,j)){
                P("== found: %d %d\n", i,j);
                R 1;
            }
        }
    }
    R 0;
}

static void run_join_r2(){
    V rtn = (V)malloc(sizeof(V0));
    // P("%d\n", isStrictOrder(data1));
    // P("%d\n", isStrictOrder(data2));
    // P("dup = %d\n", findDuplicate(data1));
    tic();
    r2_hash_main(rtn,data1,data2);
    // if(vn(data1)<=vn(data2))
    //     r2_hash_main(rtn,data1,data2);
    // else
    //     r2_hash_main(rtn,data2,data1);
    time_toc("join takes (ms): %g\n\n", elapsed);
}

