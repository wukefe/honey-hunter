
static B isLooseOrderUp(V x){
    DOIa(xn, if(vI(x,i)<=vI(x,i-1)){P("v1=%d,v0=%d\n",vI(x,i),vI(x,i-1)); getchar(); R 0;}) R 1;
    // DOIa(xn, if(vI(x,i)<vI(x,i-1))R 0) R 1;
}

static B isLooseOrderDown(V x){
    DOIa(xn, if(vI(x,i)>vI(x,i-1))R 0) R 1;
}

static void r4_hash_main(V z, V x, V y){ 
    V q7_ops  = JOIN_EQ;
    V q20_ops = initLiteralSymVector(3, (S []){"gt","eq","eq"});
    V q21_ops_0 = initLiteralSymVector(2, (S []){"eq","neq"});
    V q21_ops_1 = initLiteralSymVector(2, (S []){"neq","eq"});
    I minX, maxX;
    P("order ?: %d\n", isStrictOrder(vV(x,0),&minX,&maxX));
    P("order ?: %d\n", isStrictOrder(vV(x,1),&minX,&maxX));
    // pfnJoinIndex(z,x,y,JOIN_EQ);
    // pfnJoinIndex(z,x,y,ops);
    // pfnJoinIndex(z,x,y,q21_ops_0);
    // pfnJoinIndex(z,x,y,q7_ops);
    pfnJoinIndex(z,vV(x,1),vV(y,1),q7_ops);
    getInfoVar(z);
}

void profileData(V x){
    I minX,maxX;
    minX=maxX=vI(x,0);
    DOIa(xn, {if(minX>vI(x,i))minX=vI(x,i); if(maxX<vI(x,i))maxX=vI(x,i);})
    P("min = %d, max = %d\n", minX, maxX);
}

/*
 * min = 1, max = 10000
 * min = 3, max = 199962
 * min = 3, max = 199962
 * min = 1, max = 10000
 *
 * min = 1, max = 10000
 * min = 1, max = 200000
 * min = 1, max = 200000
 * min = 1, max = 10000
 *
 * note: too costly to merge two columns into one
 */
static void r4_hash_main_q9(V z, V x, V y){
    // DOI(vn(x), profileData(vV(x,i)))
    // DOI(vn(y), profileData(vV(y,i)))
tic();
    L row1 = vn(vV(x,0));
    V t0 = allocNode();
    initV(t0, H_L, row1);
    V x0=vV(x,0), x1=vV(x,1);
    DOI(row1, vL(t0,i)=vI(x0,i)*1000000LL+vI(x1,i))
    // 
    L row2 = vn(vV(y,0));
    V t1 = allocNode();
    initV(t1, H_L, row2);
    V y0=vV(y,0), y1=vV(y,1);
    DOI(row2, vL(t1,i)=vI(y0,i)*1000000LL+vI(y1,i))
toc();
    pfnJoinIndex(z, t0, t1, JOIN_EQ);
}

static I getMaxI(V x){
    I t=vI(x,0);
    DOIa(xn, if(t<vI(x,i))t=vI(x,i)) R t;
}

static I getGreaterBit(L x){
    L t = 1; I k = 0;
    while(t <= x) { t<<=1; k++; }
    R k;
}

static I r2_simple_cmpxx(const void * a, const void * b) {
    return ( *(I*)a - *(I*)b );
}

// heap full .....
static void r4_hash_main_q9_v0(V z, V x, V y){
    V x0=vV(x,0), x1=vV(x,1), y0=vV(y,0), y1=vV(y,1);
    L rowx = vn(x0), rowy=vn(y0);
    V t0 = allocNode(), t1 = allocNode();
    initV(t0, H_I, rowx);
    // I bit0=getGreaterBit(getMaxI(x1));
    // P("bit = %d\n", bit0);
    I offset0 = getMaxI(x1)+1;
    DOP(rowx, vI(t0,i)=(vI(x0,i)*offset0)+vI(x1,i))
    // B ff = 0; DOIa(rowx, if(vI(t0,i)==vI(t0,i-1)){ff=1;P("t0[%lld]=%d, t0[%lld]=%d\n",i,vI(t0,i),i,vI(t0,i-1));break;}) P("ff = %d\n",ff);
    // I minX, maxX;
    // B f = isStrictUnique(t0, &minX, &maxX);
    //P("min = %d, max = %d, f = %d\n", minX, maxX, f);
    initV(t1, H_I, rowy);
    // I bit1=getGreaterBit(getMaxI(y1));
    I offset1=getMaxI(y1)+1;
    DOP(rowy, vI(t1,i)=(vI(y0,i)*offset1)+vI(x1,i))
    pfnJoinIndex(z, t0, t1, JOIN_EQ);
    // I m0=getMaxI(x0);
    // I m1=getMaxI(x1);
    // I m2=getMaxI(x2);
    // I m3=getMaxI(x3);
    // L row = vn(x0);
    // L k = 0;
    // DOI(row, for(int j=i+1; j<row; j++){if(vI(x0,i)==vI(x0,j) && vI(x1,i)==vI(x1,j)) k++; })
    // P("k = %lld\n", k); // 0
    // P("max: x0 = %d, bit = %d\n", getMaxI(x0),getGreaterBit(getMaxI(x0))); // 14
    // P("max: x1 = %d, bit = %d\n", getMaxI(x1),getGreaterBit(getMaxI(x1))); // 18
    // P("max: x2 = %d, bit = %d\n", getMaxI(x2),getGreaterBit(getMaxI(x2))); // 18
    // P("max: x3 = %d, bit = %d\n", getMaxI(x3),getGreaterBit(getMaxI(x3))); // 14
    // L c=0;
    // DOI(vn(x0), if(vI(x0,i)==vI(x3,i) && vI(x1,i)==vI(x2,i))c++)
    // P("c = %lld\n", c);
    // V y0=vV(y,0), y1=vV(y,1), y2=vV(y,2), y3=vV(y,3);
    // P("max: y0 = %d, bit = %d\n", getMaxI(y0),getGreaterBit(getMaxI(y0))); // 14
    // P("max: y1 = %d, bit = %d\n", getMaxI(y1),getGreaterBit(getMaxI(y1))); // 18
    // P("max: y2 = %d, bit = %d\n", getMaxI(y2),getGreaterBit(getMaxI(y2))); // 18
    // P("max: y3 = %d, bit = %d\n", getMaxI(y3),getGreaterBit(getMaxI(y3))); // 14
    // L c=0;
    // DOI(vn(y0), if(vI(y0,i)==vI(y3,i) && vI(y1,i)==vI(y2,i))c++)
    // P("c = %lld\n", c);
}

static void r4_hash_main_q9_v1(V z, V x, V y){
    V t0 = allocNode(); initV(t0, H_G, 2);
    V t1 = allocNode(); initV(t1, H_G, 2);
    *vV(t0,0)= *vV(x,0);
    *vV(t0,1)= *vV(x,1);
    *vV(t1,0)= *vV(y,0);
    *vV(t1,1)= *vV(y,1);
    // pfnJoinIndex(z, t0, t1, JOIN_EQ);
    // pfnJoinIndex(z, x, y, JOIN_EQ);
    V x0 = vV(x,0), x1 = vV(x,1);
    V y0 = vV(y,0), y1 = vV(y,1);
    L c = 0;
    P("loop size: %lld x %lld\n", vn(x0),vn(y0));
    DOI(vn(x0), DOJ(vn(y0), if(vI(x0,i)==vI(y0,j)&&vI(x1,i)==vI(y1,j))c++))
    P("c = %lld\n", c);
}


static void run_join_r4(){
    V rtn = (V)malloc(sizeof(V0));
    tic();
    r4_hash_main_q9_v1(rtn,data1,data2);
    // r4_hash_main_q9_v0(rtn,data1,data2);
    // r4_hash_main_q9(rtn,data1,data2);
    // r4_hash_main(rtn,data1,data2);
    time_toc("join takes (ms): %g\n\n", elapsed);
}

