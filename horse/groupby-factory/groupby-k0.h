
static B isLooseOrderUp(V x){
    DOIa(xn, if(vI(x,i)<vI(x,i-1)){P("a=%d,b=%d\n",vI(x,i),vI(x,i-1));R 0;}) R 1;
}

static B isLooseOrderDown(V x){
    DOIa(xn, if(vI(x,i)>vI(x,i-1))R 0) R 1;
}

static B isLooseOrder(V x, I *minX, I *maxX){
    if(isLooseOrderUp(x)){
        *minX = vI(x,0);
        *maxX = vI(x,xn-1);
        R 1;
    }
    else if(isLooseOrderDown(x)){
        *minX = vI(x,xn-1);
        *maxX = vI(x,0);
        R 1;
    }
    else EP("TODO");
}

static L* k0_createGroup(V x, L size){
    L *ht     = HASH_AL(L, size);
    L *offset = HASH_AL(L, size);
    tic();
    DOTa(size, memset(ht+sid, 0, sizeof(L)*len))
    DOI(xn, ht[vI(x,i)]++)
    time_toc("k0: build time (ms): %g\n", elapsed);
    tic();
    L c = 0, seg = 0;
    DOI(size, if(ht[i]){offset[i]=seg; seg+=ht[i]; c++;})
    time_toc("k0: init offset (ms): %g\n", elapsed);
    V z0 = allocNode(), z1 = allocNode();
    V tt = allocNode();
    initV(z0, H_L, c);
    initV(z1, H_G, c);
    initV(tt, H_L, xn);
    tic();
    L *segs = HASH_AL(L, c), id=0;
    DOI(size, if(ht[i]){segs[id++]=ht[i];})
    time_toc("k0: build segs (ms): %g\n", elapsed);
    // DOI(c, {V t=vV(z1,i); initV(t,H_L,0); vg(t)=vg(tt)+sizeof(L)*offset })
    tic();
    DOI(size, {I k=vI(x,i); vL(tt,offset[k])=vI(x,i); offset[k]++;})
    time_toc("k0: write indices (ms): %g\n", elapsed);
    printV2(tt, 120);
    R ht;
}

#ifndef DOTb
#define DOTb(n, x, ...) {L seg=(n)/H_CORE; \
    _Pragma(STRINGIFY(omp parallel __VA_ARGS__)) \
    { \
        L tid = omp_get_thread_num(); \
        for(L i=tid*seg+1,i2=(tid!=H_CORE-1?((tid+1)*seg):(n));i<i2;i++) x;\
    } \
}
#endif

#ifndef DOTc
#define DOTc(n, x, y, ...) {L seg=(n)/H_CORE; \
    _Pragma(STRINGIFY(omp parallel __VA_ARGS__)) \
    { \
        L tid = omp_get_thread_num(); \
        L pos = tid*seg; \
        x; \
        for(L i=pos+1,i2=(tid!=H_CORE-1?(pos+seg):(n));i<i2;i++) y;\
    } \
}
#endif



void k0_createGroupSimple(V x, L size){
    if(size < 1) EP("size must > 0");
    V z0 = allocNode(), z1 = allocNode();
tic();
    I parZ[H_CORE];
    DOI(H_CORE, parZ[i]=1)
    // DOIa(xn, if(vI(x,i)!=vI(x,i-1))tot++)
    tic();
    DOTb(xn, if(vI(x,i)!=vI(x,i-1))parZ[tid]++)
    toc();
    DOI(H_CORE, P("parZ[%lld] = %d\n", i, parZ[i]))
    L seg=xn/H_CORE;
    DOIa(H_CORE, {L k=seg*i; if(vI(x,k)==vI(x,k-1))parZ[i]--;})
    I tot = 0; DOI(H_CORE, tot+=parZ[i])
    P("tot = %d\n", tot);
time_toc("k0: count segs (ms): %g\n", elapsed);
    initV(z0, H_L, tot+1);
    initV(z1, H_G, tot);
    L *offset = sL(z0);
    vn(z0)=tot;
tic();
    L c = 1; offset[tot]=xn;
    I parN[H_CORE]; parN[0]=0;
    DOIa(H_CORE, parN[i]=parN[i-1]+parZ[i-1]) // parallel offset
    DOTc(xn, {if(tid==0 || (tid>0 && vI(x,pos)!=vI(x,pos-1)))offset[parN[tid]++]=pos;}, {if(vI(x,i)!=vI(x,i-1))offset[parN[tid]++]=i;})
    // DOI(20, P("offset[%lld] = %lld\n", i,offset[i]))
    // DOIa(xn, if(vI(x,i)!=vI(x,i-1))offset[c++]=i)
    // L ttt = 0; DOI(tot, ttt+=offset[i]) P("ttt = %lld\n", ttt);
time_toc("k0: compute offsets (ms): %g\n", elapsed);
    V tt = allocNode();
    initV(tt, H_L, xn);
tic();
    DOP(tot, {V t=vV(z1,i);
            vp(t)=H_L;
            vn(t)=offset[i+1]-offset[i];
            vg(t)=(G)(sL(tt)+offset[i]);
            DOJ(vn(t), vL(t,j)=j+offset[i])
            })
time_toc("k0: write values (ms): %g\n", elapsed);
    printV2(z0, 10);
    DOI(10, printV(vV(z1,i)))
    P("----test groupby ends----\n");
}

// fuse: groupby + sum(value item)
// return: keys and aggregated items
void k0_createGroupFuse1(V x, L size){
    if(size < 1) EP("size must > 0");
    V z0 = allocNode(), z1 = allocNode();
    tic();
    I seg = 1;
    DOIa(xn, if(vI(x,i)!=vI(x,i-1))seg++)
    // P("seg = %d\n",seg);
    time_toc("k0: count segs (ms): %g\n", elapsed);
    initV(z0, H_L, seg);
    initV(z1, H_E, seg);
    L *offset = sL(z0);
    tic();
    L c = 1; offset[0] = 0; offset[seg]=xn;
    DOIa(xn, if(vI(x,i)!=vI(x,i-1))offset[c++]=i)
    time_toc("k0: compute offsets (ms): %g\n", elapsed);
    tic();
    DOI(seg, vE(z1,i) = vI(x,offset[i])*(offset[i+1]-offset[i-1]))
    // P("len = %lld\n", offset[i+1]-offset[i]);
    // DOJ(offset[i+1]-offset[i], t+=vI(x,j+offset[i])) vE(z1,i)=t;})
    time_toc("k0: write values (ms): %g\n", elapsed);
    // printV2(z0, 10);
    printV2(z1, 20);
}

void k0_groupby_main(V z, V x){
    // pfnGroup(z,x);
    I minX, maxX;
    tic();
    B doGroupSpecial = isLooseOrder(x,&minX, &maxX);
    time_toc("k0: pre-probe (ms): %g\n", elapsed);
    if(doGroupSpecial){
        P("min = %d, max = %d\n", minX, maxX);
        // k0_createGroup(x, maxX);
        k0_createGroupSimple(x, maxX);
        // k0_createGroupFuse1(x, maxX); // correct, but not used
    }
    else EP("TODO");
}

static void run_groupby_k0(){
    V z = allocNode();
    tic();
    k0_groupby_main(z, data1);
    time_toc("group by time (ms): %g\n", elapsed);
}

