// Parsing time (ms): 0.145
 // - #: 2
 // - #: 4
// Total # of fused stmts: 6
static I q16_autofusion_6(V z, V *x);
static I q16_patternindex_1(V *z, V *x, V y);
static I q16_autofusion_4(V z, V *x);
static I q16_patternindex_2(V *z, V *x, V y);
static I q16_peephole_fp4_0(V z, V x, V y);
static I q16_patternindex_3(V *z, V *x, V y);

static I q16_autofusion_6(V z, V *x){
    V x0=x[0]; // t27
    V x1=x[1]; // t20
    V x2=x[2]; // t29
    Q id0=getSymbol("Brand#45");
    initV(z, H_B, vn(x0));
    DOP(vn(x0), vB(z,i)=AND(AND(vB(x0,i),NEQ(vQ(x1,i),id0)),NOT(vB(x2,i)))) R 0;
}
static I q16_patternindex_1(V *z, V *x, V y){
    V z0 = z[0]; // t55
    V z1 = z[1]; // t56
    V z2 = z[2]; // t57
    V x0 = x[0]; // t20
    V x1 = x[1]; // t21
    V x2 = x[2]; // t22
    initV(z0, H_Q, vn(y));
    initV(z1, H_Q, vn(y));
    initV(z2, H_I, vn(y));
    DOP(vn(z0), {
        vQ(z0,i) = vQ(x0, vL(y,i));
        vQ(z1,i) = vQ(x1, vL(y,i));
        vI(z2,i) = vI(x2, vL(y,i));
    })
    R 0;
}

static I q16_autofusion_4(V z, V *x){
    V x0=x[0]; // t63
    V x1=x[1]; // t49
    L lenZ = 0, parZ[H_CORE], offset[H_CORE];
    DOI(H_CORE, parZ[i]=offset[i]=0)
    CHECKE(getNumOfNonZero(x1,parZ));
    DOI(H_CORE, lenZ += parZ[i])
    DOIa(H_CORE, offset[i]=parZ[i-1]+offset[i-1])
    initV(z, H_I, lenZ);
    DOT(vn(x1), if(vB(x1,i)){L c=offset[tid]++;\
        vI(z,c) = vI(x0,i);})
    R 0;
}

static I q16_patternindex_2(V *z, V *x, V y){
    V z0 = z[0]; // t88
    V z1 = z[1]; // t89
    V z2 = z[2]; // t90
    V x0 = x[0]; // t73
    V x1 = x[1]; // t74
    V x2 = x[2]; // t75
    initV(z0, H_Q, vn(y));
    initV(z1, H_Q, vn(y));
    initV(z2, H_I, vn(y));
    DOP(vn(z0), {
        vQ(z0,i) = vQ(x0, vL(y,i));
        vQ(z1,i) = vQ(x1, vL(y,i));
        vI(z2,i) = vI(x2, vL(y,i));
    })
    R 0;
}

static I q16_peephole_fp4_0(V z, V x, V y){
    // z -> t94, x -> t80, y -> t87
    L r0 = vn(y);
    initV(z, H_L, r0);
    DOP(r0, {V t=vV(y,i); L len=vn(t); L tot=0; B f[199]={0};\
        DOJ(len, if(!f[j]){ \
        DOK(len, if(k!=j && vI(x,vL(t,j))==vI(x,vL(t,k))) f[k]=1)\
        f[j]=1; tot++;}) vL(z,i)=tot; }) R 0;
}

static I q16_patternindex_3(V *z, V *x, V y){
    V z0 = z[0]; // t97
    V z1 = z[1]; // t98
    V z2 = z[2]; // t99
    V z3 = z[3]; // t100
    V x0 = x[0]; // t88
    V x1 = x[1]; // t89
    V x2 = x[2]; // t90
    V x3 = x[3]; // t94
    initV(z0, H_Q, vn(y));
    initV(z1, H_Q, vn(y));
    initV(z2, H_I, vn(y));
    initV(z3, H_L, vn(y));
    DOP(vn(z0), {
        vQ(z0,i) = vQ(x0, vL(y,i));
        vQ(z1,i) = vQ(x1, vL(y,i));
        vI(z2,i) = vI(x2, vL(y,i));
        vL(z3,i) = vL(x3, vL(y,i));
    })
    R 0;
}


static E compiled_main(){
    V t100 = allocNode(); V t98 = allocNode(); V t101 = allocNode(); V t99 = allocNode(); 
    V t102 = allocNode(); V t103 = allocNode(); V t0 = allocNode(); V t1 = allocNode(); 
    V t7 = allocNode(); V t8 = allocNode(); V t9 = allocNode(); V t20 = allocNode(); 
    V t21 = allocNode(); V t30 = allocNode(); V t22 = allocNode(); V t31 = allocNode(); 
    V t32 = allocNode(); V t16 = allocNode(); V t50 = allocNode(); V t42 = allocNode(); 
    V t26 = allocNode(); V t51 = allocNode(); V t43 = allocNode(); V t27 = allocNode(); 
    V t44 = allocNode(); V t28 = allocNode(); V t29 = allocNode(); V t63 = allocNode(); 
    V t55 = allocNode(); V t80 = allocNode(); V t64 = allocNode(); V t56 = allocNode(); 
    V t48 = allocNode(); V t73 = allocNode(); V t57 = allocNode(); V t49 = allocNode(); 
    V t90 = allocNode(); V t74 = allocNode(); V t91 = allocNode(); V t75 = allocNode(); 
    V t92 = allocNode(); V t84 = allocNode(); V t68 = allocNode(); V t93 = allocNode(); 
    V t85 = allocNode(); V t69 = allocNode(); V t94 = allocNode(); V t86 = allocNode(); 
    V t95 = allocNode(); V t87 = allocNode(); V t96 = allocNode(); V t88 = allocNode(); 
    V t97 = allocNode(); V t89 = allocNode(); 
    tic();
    PROFILE(4,0, pfnLoadTable(t0, initLiteralSym("supplier")));
    PROFILE(5,0, pfnColumnValue(t1, t0, initLiteralSym("s_suppkey")));
    PROFILE(6,0, pfnColumnValue(t7, t0, initLiteralSym("s_comment")));
    PROFILE(7,0, pfnLike2(t8, t7, initLiteralSym("%Customer%Complaints%")));
    PROFILE(8,0, pfnCompress(t9, t8, t1));
    PROFILE(9,0, pfnLoadTable(t16, initLiteralSym("part")));
    PROFILE(10,0, pfnColumnValue(t20, t16, initLiteralSym("p_brand")));
    PROFILE(11,0, pfnColumnValue(t21, t16, initLiteralSym("p_type")));
    PROFILE(12,0, pfnColumnValue(t22, t16, initLiteralSym("p_size")));
    PROFILE(13,0, copyV(t26,initLiteralI32Vector(8, (I []){49, 14, 23, 45, 19, 3, 36, 9})));
    PROFILE(14,0, pfnMember(t27, t22, t26));
    PROFILE(16,0, pfnLike2(t29, t21, initLiteralSym("MEDIUM POLISHED%")));
    PROFILE(19,0, q16_autofusion_6(t32, (V[]){t27,t20,t29}));
    PROFILE(20,0, pfnLoadTable(t42, initLiteralSym("partsupp")));
    PROFILE(21,0, pfnColumnValue(t43, t42, initLiteralSym("ps_partkey")));
    PROFILE(22,0, pfnColumnValue(t44, t42, initLiteralSym("ps_suppkey")));
    PROFILE(23,0, pfnValues(t48, t43));
    PROFILE(24,0, pfnIndex(t49, t32, t48));
    PROFILE(25,0, pfnCompress(t50, t49, t48));
    PROFILE(26,0, pfnWhere(t51, t49));
    PROFILE(27,0, q16_patternindex_1((V []){t55, t56, t57}, (V []){t20, t21, t22}, t50));
    PROFILE(30,0, pfnFetch(t63, t44));
    PROFILE(31,0, q16_autofusion_4(t64, (V[]){t63,t49}));
    PROFILE(32,0, pfnMember(t68, t64, t9));
    PROFILE(33,0, pfnNot(t69, t68));
    PROFILE(34,0, pfnCompress(t73, t69, t55));
    PROFILE(35,0, pfnCompress(t74, t69, t56));
    PROFILE(36,0, pfnCompress(t75, t69, t57));
    PROFILE(37,0, pfnCompress(t80, t69, t64));
    PROFILE(38,0, pfnList(t84, 3, (V []){t73, t74, t75}));
    // getInfoVar(t73); getInfoVar(t74); getInfoVar(t75);
    // Variable t73 has type H_Q and len 118274
    // Variable t74 has type H_Q and len 118274
    // Variable t75 has type H_I and len 118274
    PROFILE(39,0, pfnGroup(t85, t84));
    PROFILE(40,0, pfnKeys(t86, t85));
    // getInfoVar(t86); getchar();
    // Variable t86 has type H_L and len 18314
    PROFILE(41,0, pfnValues(t87, t85));
    PROFILE(42,0, q16_patternindex_2((V []){t88, t89, t90}, (V []){t73, t74, t75}, t86));
    PROFILE(48,0, q16_peephole_fp4_0(t94,t80,t87));
    PROFILE(49,0, pfnList(t95, 4, (V []){t94, t88, t89, t90}));
    PROFILE(50,0, pfnOrderBy(t96, t95, initLiteralBoolVector(4, (B []){0, 1, 1, 1})));
    PROFILE(51,0, q16_patternindex_3((V []){t97, t98, t99, t100}, (V []){t88, t89, t90, t94}, t96));
    PROFILE(55,0, copyV(t101,initLiteralSymVector(4, (S []){"p_brand", "p_type", "p_size", "supplier_cnt"})));
    PROFILE(56,0, pfnList(t102, 4, (V []){t97, t98, t99, t100}));
    PROFILE(57,0, pfnTable(t103, t101, t102));
    E elapsed = calc_toc();
    printV2(t103, 20);
    return elapsed;
}

