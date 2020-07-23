// Parsing time (ms): 0.104
 // - #: 5
// Total # of fused stmts: 5
static I q4_peephole_fp3_0(V z, V *x, V *y);
static I q4_autofusion_4(V z, V *x);
static I q4_autofusionlist_2(V z, V *x);
static I q4_patternindex_1(V *z, V *x, V y);

static I q4_peephole_fp3_0(V z, V *x, V *y){
    // z -> t63
    V x0 = x[0]; // t36
    V x1 = x[1]; // t37
    V y0 = y[0]; // t58
    V y1 = y[1]; // t59
    L r0 = vn(y1);
    initV(z, H_B, r0);
    DOP(vn(y0), if(vD(x0,i)<vD(x1,i))vB(z,vL(y0,i))=1) R 0;
}

static I q4_autofusion_4(V z, V *x){
    V x0=x[0]; // t6
    V x1=x[1]; // t63
    V x2=x[2]; // t7
    L parZ[H_CORE], offset[H_CORE], total = 0;
    DOI(H_CORE, parZ[i]=offset[i]=0)
    DOT(vn(x0), if(AND(AND(GEQ(vD(x0,i),19930701),LT(vD(x0,i),19931001)),vB(x1,i))) parZ[tid]++)
    DOI(H_CORE, total+=parZ[i])
    DOIa(H_CORE, offset[i]=parZ[i-1]+offset[i-1])
    initV(z, H_Q, total);
    DOT(vn(x0), \
        if(AND(AND(GEQ(vD(x0,i),19930701),LT(vD(x0,i),19931001)),vB(x1,i))){L c=offset[tid]++; vQ(z,c)=vQ(x2,i);})
    R 0;
}
static I q4_autofusionlist_2(V z, V *x){
    V x0=x[0]; // t70
    V x1=x[1]; // t77
    initV(z, H_L, vn(x1));
    DOP(vn(z), vL(z,i)=vn(vV(x1,i))) R 0;
}
static I q4_patternindex_1(V *z, V *x, V y){
    V z0 = z[0]; // t84
    V z1 = z[1]; // t85
    V x0 = x[0]; // t78
    V x1 = x[1]; // t81
    initV(z0, H_Q, vn(y));
    initV(z1, H_L, vn(y));
    DOP(vn(z0), {
        vQ(z0,i) = vQ(x0, vL(y,i));
        vL(z1,i) = vL(x1, vL(y,i));
    })
    R 0;
}


static E compiled_main(){
    V t0 = allocNode(); V t6 = allocNode(); V t7 = allocNode(); V t11 = allocNode(); 
    V t12 = allocNode(); V t13 = allocNode(); V t23 = allocNode(); V t24 = allocNode(); 
    V t41 = allocNode(); V t60 = allocNode(); V t36 = allocNode(); V t61 = allocNode(); 
    V t37 = allocNode(); V t70 = allocNode(); V t62 = allocNode(); V t63 = allocNode(); 
    V t80 = allocNode(); V t64 = allocNode(); V t81 = allocNode(); V t82 = allocNode(); 
    V t74 = allocNode(); V t58 = allocNode(); V t83 = allocNode(); V t75 = allocNode(); 
    V t59 = allocNode(); V t84 = allocNode(); V t76 = allocNode(); V t85 = allocNode(); 
    V t77 = allocNode(); V t86 = allocNode(); V t78 = allocNode(); V t87 = allocNode(); 
    V t79 = allocNode(); V t88 = allocNode(); 
    tic();
    PROFILE(4,0, pfnLoadTable(t0, initLiteralSym("orders")));
    PROFILE(5,0, pfnColumnValue(t6, t0, initLiteralSym("o_orderdate")));
    PROFILE(6,0, pfnColumnValue(t7, t0, initLiteralSym("o_orderpriority")));
    PROFILE(10,0, pfnLoadTable(t23, initLiteralSym("lineitem")));
    PROFILE(11,0, pfnColumnValue(t24, t23, initLiteralSym("l_orderkey")));
    PROFILE(12,0, pfnColumnValue(t36, t23, initLiteralSym("l_commitdate")));
    PROFILE(13,0, pfnColumnValue(t37, t23, initLiteralSym("l_receiptdate")));
    PROFILE(15,0, pfnValues(t58, t24));
    PROFILE(16,0, pfnKeys(t59, t24));
    PROFILE(20,0, q4_peephole_fp3_0(t63,(V []){t36,t37}, (V []){t58,t59}));
    PROFILE(22,0, q4_autofusion_4(t70, (V[]){t6,t63,t7}));
    PROFILE(23,0, pfnList(t74, 1, (V []){t70}));
    // getInfoVar(t70);
    // Variable t70 has type H_Q and len 52523
    PROFILE(24,0, pfnGroup(t75, t74));
    PROFILE(25,0, pfnKeys(t76, t75));
    // getInfoVar(t76); getchar();
    // Variable t76 has type H_L and len 5
    PROFILE(26,0, pfnValues(t77, t75));
    PROFILE(27,0, pfnIndex(t78, t70, t76));
    PROFILE(30,0, q4_autofusionlist_2(t81, (V[]){t70,t77}));
    PROFILE(31,0, pfnList(t82, 1, (V []){t78}));
    PROFILE(32,0, pfnOrderBy(t83, t82, initLiteralBool(1)));
    PROFILE(33,0, q4_patternindex_1((V []){t84, t85}, (V []){t78, t81}, t83));
    PROFILE(35,0, copyV(t86,initLiteralSymVector(2, (S []){"o_orderpriority", "order_count"})));
    PROFILE(36,0, pfnList(t87, 2, (V []){t84, t85}));
    PROFILE(37,0, pfnTable(t88, t86, t87));
    E elapsed = calc_toc();
    printV2(t88, 20);
    return elapsed;
}
