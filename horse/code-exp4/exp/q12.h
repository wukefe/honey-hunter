// Parsing time (ms): 0.146
 // - #: 7
 // - #: 7
 // - #: 4
 // - #: 9
// Total # of fused stmts: 27
static I q12_autofusion_10(V z, V *x);
static I q12_autofusion_5(V *z, V *x);
static I q12_autofusion_9(V z, V *x);
static I q12_autofusion_8(V z, V *x);
static I q12_peephole_fp1_0(V z, V x, V y);
static I q12_peephole_fp1_1(V z, V x, V y);
static I q12_patternindex_2(V *z, V *x, V y);

static I q12_autofusion_10(V z, V *x){
    V x0=x[0]; // t14
    V x1=x[1]; // t16
    V x2=x[2]; // t18
    V x3=x[3]; // t13
    V x4=x[4]; // t12
    initV(z, H_B, vn(x0));
    DOP(vn(x0), vB(z,i)=AND(AND(GEQ(vD(x0,i),19940101),LT(vD(x0,i),19950101)),AND(AND(MEMBER_CONST_Q(vQ(x1,i),x2),LT(vD(x3,i),vD(x0,i))),LT(vD(x4,i),vD(x3,i))))) R 0;
}
static I q12_autofusion_5(V *z, V *x){
    V x0=x[0]; // t51
    V x1=x[1]; // t27
    V x2=x[2]; // t55
    V x3=x[3]; // t16
    V z0=z[0]; // 
    V z1=z[1]; // 
    L parZ[H_CORE], offset[H_CORE], total = 0;
    DOI(H_CORE, parZ[i]=offset[i]=0)
    DOT(vn(x1), if(vB(x1,i)) parZ[tid]++)
    DOI(H_CORE, total+=parZ[i])
    DOIa(H_CORE, offset[i]=parZ[i-1]+offset[i-1])
    initV(z0, H_Q, total);
    initV(z1, H_Q, total);
    DOT(vn(x1),if(vB(x1,i)){ L c=offset[tid]++; \
        vQ(z0,c) = vQ(x0,vL(x2,i)); \
        vQ(z1,c) = vQ(x3,i);})
    R 0;
}

static I q12_autofusion_9(V z, V *x){
    V x0=x[0]; // t79
    Q id0=getSymbol("1-URGENT");
    Q id1=getSymbol("2-HIGH");
    initV(z, H_I, vn(x0));
    DOP(vn(x0), vI(z,i)=PLUS(MUL(OR(EQ(vQ(x0,i),id0),EQ(vQ(x0,i),id1)),1),MUL(NOT(OR(EQ(vQ(x0,i),id0),EQ(vQ(x0,i),id1))),0))) R 0;
}
static I q12_autofusion_8(V z, V *x){
    V x0=x[0]; // t79
    Q id0=getSymbol("1-URGENT");
    Q id1=getSymbol("2-HIGH");
    initV(z, H_I, vn(x0));
    DOP(vn(x0), vI(z,i)=PLUS(MUL(AND(NEQ(vQ(x0,i),id0),NEQ(vQ(x0,i),id1)),1),MUL(NOT(AND(NEQ(vQ(x0,i),id0),NEQ(vQ(x0,i),id1))),0))) R 0;
}
static I q12_peephole_fp1_0(V z, V x, V y){
    // z -> t104
    initV(z, H_L, vn(y));
    DOP(vn(y), {I a=0; V t=vV(y,i); DOJ(vn(t), a+=vI(x,vL(t,j))) vL(z,i)=a;}) R 0;
}

static I q12_peephole_fp1_1(V z, V x, V y){
    // z -> t107
    initV(z, H_L, vn(y));
    DOP(vn(y), {I a=0; V t=vV(y,i); DOJ(vn(t), a+=vI(x,vL(t,j))) vL(z,i)=a;}) R 0;
}

static I q12_patternindex_2(V *z, V *x, V y){
    V z0 = z[0]; // t110
    V z1 = z[1]; // t111
    V z2 = z[2]; // t112
    V x0 = x[0]; // t101
    V x1 = x[1]; // t104
    V x2 = x[2]; // t107
    initV(z0, H_Q, vn(y));
    initV(z1, H_L, vn(y));
    initV(z2, H_L, vn(y));
    DOP(vn(z0), {
        vQ(z0,i) = vQ(x0, vL(y,i));
        vL(z1,i) = vL(x1, vL(y,i));
        vL(z2,i) = vL(x2, vL(y,i));
    })
    R 0;
}


static E compiled_main(){
    V t100 = allocNode(); V t98 = allocNode(); V t101 = allocNode(); V t99 = allocNode(); 
    V t110 = allocNode(); V t102 = allocNode(); V t111 = allocNode(); V t103 = allocNode(); 
    V t112 = allocNode(); V t104 = allocNode(); V t113 = allocNode(); V t105 = allocNode(); 
    V t114 = allocNode(); V t106 = allocNode(); V t115 = allocNode(); V t107 = allocNode(); 
    V t108 = allocNode(); V t109 = allocNode(); V t0 = allocNode(); V t1 = allocNode(); 
    V t20 = allocNode(); V t12 = allocNode(); V t21 = allocNode(); V t13 = allocNode(); 
    V t22 = allocNode(); V t14 = allocNode(); V t23 = allocNode(); V t24 = allocNode(); 
    V t16 = allocNode(); V t25 = allocNode(); V t26 = allocNode(); V t18 = allocNode(); 
    V t51 = allocNode(); V t27 = allocNode(); V t19 = allocNode(); V t44 = allocNode(); 
    V t55 = allocNode(); V t72 = allocNode(); V t56 = allocNode(); V t57 = allocNode(); 
    V t90 = allocNode(); V t91 = allocNode(); V t83 = allocNode(); V t92 = allocNode(); 
    V t84 = allocNode(); V t93 = allocNode(); V t85 = allocNode(); V t94 = allocNode(); 
    V t86 = allocNode(); V t95 = allocNode(); V t87 = allocNode(); V t79 = allocNode(); 
    V t96 = allocNode(); V t88 = allocNode(); V t97 = allocNode(); V t89 = allocNode(); 
    tic();
    PROFILE(4,0, pfnLoadTable(t0, initLiteralSym("lineitem")));
    PROFILE(5,0, pfnColumnValue(t1, t0, initLiteralSym("l_orderkey")));
    PROFILE(6,0, pfnColumnValue(t12, t0, initLiteralSym("l_shipdate")));
    PROFILE(7,0, pfnColumnValue(t13, t0, initLiteralSym("l_commitdate")));
    PROFILE(8,0, pfnColumnValue(t14, t0, initLiteralSym("l_receiptdate")));
    PROFILE(9,0, pfnColumnValue(t16, t0, initLiteralSym("l_shipmode")));
    PROFILE(10,0, copyV(t18,initLiteralSymVector(2, (S []){"MAIL", "SHIP"})));
    PROFILE(19,0, q12_autofusion_10(t27, (V[]){t14,t16,t18,t13,t12}));
    PROFILE(20,0, pfnLoadTable(t44, initLiteralSym("orders")));
    PROFILE(21,0, pfnColumnValue(t51, t44, initLiteralSym("o_orderpriority")));
    PROFILE(22,0, pfnValues(t55, t1));
    PROFILE(23,0, pfnCompress(t56, t27, t55));
    PROFILE(24,0, pfnWhere(t57, t27));
    PROFILE(26,0, q12_autofusion_5((V []){t79,t72}, (V []){t51,t27,t55,t16}));
    PROFILE(33,0, q12_autofusion_9(t89, (V[]){t79}));
    PROFILE(40,0, q12_autofusion_8(t96, (V[]){t79}));
    PROFILE(41,0, pfnList(t97, 1, (V []){t72}));
    // getInfoVar(t72);
    // Variable t72 has type H_Q and len 30988
    PROFILE(42,0, pfnGroup(t98, t97));
    PROFILE(43,0, pfnKeys(t99, t98));
    // getInfoVar(t99); getchar();
    // Variable t99 has type H_L and len 2
    PROFILE(44,0, pfnValues(t100, t98));
    PROFILE(45,0, pfnIndex(t101, t72, t99));
    PROFILE(48,0, q12_peephole_fp1_0(t104,t89,t100));
    PROFILE(51,0, q12_peephole_fp1_1(t107,t96,t100));
    PROFILE(52,0, pfnList(t108, 1, (V []){t101}));
    PROFILE(53,0, pfnOrderBy(t109, t108, initLiteralBool(1)));
    PROFILE(54,0, q12_patternindex_2((V []){t110, t111, t112}, (V []){t101, t104, t107}, t109));
    PROFILE(57,0, copyV(t113,initLiteralSymVector(3, (S []){"l_shipmode", "high_line_count", "low_line_count"})));
    PROFILE(58,0, pfnList(t114, 3, (V []){t110, t111, t112}));
    PROFILE(59,0, pfnTable(t115, t113, t114));
    E elapsed = calc_toc();
    printV2(t115, 20);
    return elapsed;
}

