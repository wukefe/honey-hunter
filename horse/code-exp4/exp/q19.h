// Parsing time (ms): 0.196
 // - #: 5
 // - #: 14
 // - #: 7
 // - #: 7
 // - #: 7
 // - #: 3
// Total # of fused stmts: 43
static I q19_autofusion_13(V z, V *x);
static I q19_patterncompress_0(V *z, V x, V *y);
static I q19_autofusion_12(V z, V *x);
static I q19_autofusion_11(V z, V *x);
static I q19_autofusion_10(V z, V *x);
static I q19_autofusion_9(V z, V *x);
static I q19_patterncompress_1(V *z, V x, V *y);
static I q19_autofusion_8(V z, V *x);

static I q19_autofusion_13(V z, V *x){
    V x0=x[0]; // t25
    V x1=x[1]; // t26
    V x2=x[2]; // t28
    Q id3=getSymbol("DELIVER IN PERSON");
    initV(z, H_B, vn(x0));
    DOP(vn(x0), vB(z,i)=AND(EQ(vQ(x0,i),id3),MEMBER_CONST_Q(vQ(x1,i),x2))) R 0;
}
static I q19_patterncompress_0(V *z, V x, V *y){
    V z0 = z[0]; // t33
    V z1 = z[1]; // t36
    V z2 = z[2]; // t37
    V z3 = z[3]; // t38
    V y0 = y[0]; // t13
    V y1 = y[1]; // t16
    V y2 = y[2]; // t17
    V y3 = y[3]; // t18
    L len = vn(x), k = 0;
    L lenZ = 0, parZ[H_CORE], offset[H_CORE];
    tic();
    DOI(H_CORE, parZ[i]=offset[i]=0)
    CHECKE(getNumOfNonZero(x,parZ));
    DOI(H_CORE, lenZ += parZ[i])
    DOIa(H_CORE, offset[i]=parZ[i-1]+offset[i-1])
    toc();
    initV(z0,H_I,lenZ);
    initV(z1,H_E,lenZ);
    initV(z2,H_E,lenZ);
    initV(z3,H_E,lenZ);
    tic();
    DOT(len, if(vB(x,i)){L c=offset[tid]++;\
        vI(z0,c) = vI(y0,i);\
        vE(z1,c) = vE(y1,i);\
        vE(z2,c) = vE(y2,i);\
        vE(z3,c) = vE(y3,i);\
    })
    toc();
    R 0;
}

static I q19_autofusion_12(V z, V *x){
    V x0=x[0]; // t6
    V x1=x[1]; // t4
    V x2=x[2]; // t7
    V x3=x[3]; // t52
    Q id2=getSymbol("Brand#12");
    initV(z, H_B, vn(x0));
    DOP(vn(x0), vB(z,i)=AND(AND(AND(GEQ(vI(x0,i),1),LEQ(vI(x0,i),5)),EQ(vQ(x1,i),id2)),MEMBER_CONST_Q(vQ(x2,i),x3))) R 0;
}
static I q19_autofusion_11(V z, V *x){
    V x0=x[0]; // t6
    V x1=x[1]; // t4
    V x2=x[2]; // t7
    V x3=x[3]; // t63
    Q id1=getSymbol("Brand#23");
    initV(z, H_B, vn(x0));
    DOP(vn(x0), vB(z,i)=AND(AND(AND(GEQ(vI(x0,i),1),LEQ(vI(x0,i),10)),EQ(vQ(x1,i),id1)),MEMBER_CONST_Q(vQ(x2,i),x3))) R 0;
}
static I q19_autofusion_10(V z, V *x){
    V x0=x[0]; // t6
    V x1=x[1]; // t4
    V x2=x[2]; // t7
    V x3=x[3]; // t74
    Q id0=getSymbol("Brand#34");
    initV(z, H_B, vn(x0));
    DOP(vn(x0), vB(z,i)=AND(AND(AND(GEQ(vI(x0,i),1),LEQ(vI(x0,i),15)),EQ(vQ(x1,i),id0)),MEMBER_CONST_Q(vQ(x2,i),x3))) R 0;
}
static I q19_autofusion_9(V z, V *x){
    V x0=x[0]; // t84
    V x1=x[1]; // t36
    V x2=x[2]; // t85
    V x3=x[3]; // t86
    initV(z, H_B, vn(x0));
    DOP(vn(x0), vB(z,i)=OR(OR(AND(vB(x0,i),AND(GEQ(vE(x1,i),1),LEQ(vE(x1,i),11))),AND(vB(x2,i),AND(GEQ(vE(x1,i),10),LEQ(vE(x1,i),20)))),AND(vB(x3,i),AND(GEQ(vE(x1,i),20),LEQ(vE(x1,i),30))))) R 0;
}
static I q19_patterncompress_1(V *z, V x, V *y){
    V z0 = z[0]; // t106
    V z1 = z[1]; // t107
    V y0 = y[0]; // t37
    V y1 = y[1]; // t38
    L len = vn(x), k = 0;
    L lenZ = 0, parZ[H_CORE], offset[H_CORE];
    DOI(H_CORE, parZ[i]=offset[i]=0)
    CHECKE(getNumOfNonZero(x,parZ));
    DOI(H_CORE, lenZ += parZ[i])
    DOIa(H_CORE, offset[i]=parZ[i-1]+offset[i-1])
    initV(z0,H_E,lenZ);
    initV(z1,H_E,lenZ);
    DOT(len, if(vB(x,i)){L c=offset[tid]++;\
        vE(z0,c) = vE(y0,i);\
        vE(z1,c) = vE(y1,i);\
    })
    R 0;
}

static I q19_autofusion_8(V z, V *x){
    V x0=x[0]; // t91
    V x1=x[1]; // t37
    V x2=x[2]; // t38
    E c = 0; L tot=0;
    initV(z, H_E, 1);
    DOP(vn(x0), if(vB(x0,i)){\
	c+=MUL(vE(x1,i),MINUS(1,vE(x2,i)));}, reduction(+:c))
    vE(z,0) = c;
    R 0;
}

static E compiled_main(){
    V t120 = allocNode(); V t121 = allocNode(); V t122 = allocNode(); V t106 = allocNode(); 
    V t107 = allocNode(); V t117 = allocNode(); V t118 = allocNode(); V t119 = allocNode(); 
    V t0 = allocNode(); V t1 = allocNode(); V t4 = allocNode(); V t6 = allocNode(); 
    V t7 = allocNode(); V t10 = allocNode(); V t13 = allocNode(); V t30 = allocNode(); 
    V t31 = allocNode(); V t16 = allocNode(); V t33 = allocNode(); V t25 = allocNode(); 
    V t17 = allocNode(); V t50 = allocNode(); V t26 = allocNode(); V t18 = allocNode(); 
    V t51 = allocNode(); V t60 = allocNode(); V t52 = allocNode(); V t36 = allocNode(); 
    V t28 = allocNode(); V t61 = allocNode(); V t53 = allocNode(); V t37 = allocNode(); 
    V t29 = allocNode(); V t70 = allocNode(); V t62 = allocNode(); V t54 = allocNode(); 
    V t38 = allocNode(); V t71 = allocNode(); V t63 = allocNode(); V t55 = allocNode(); 
    V t80 = allocNode(); V t72 = allocNode(); V t64 = allocNode(); V t56 = allocNode(); 
    V t48 = allocNode(); V t81 = allocNode(); V t73 = allocNode(); V t65 = allocNode(); 
    V t57 = allocNode(); V t49 = allocNode(); V t90 = allocNode(); V t82 = allocNode(); 
    V t74 = allocNode(); V t66 = allocNode(); V t58 = allocNode(); V t91 = allocNode(); 
    V t83 = allocNode(); V t75 = allocNode(); V t67 = allocNode(); V t59 = allocNode(); 
    V t84 = allocNode(); V t76 = allocNode(); V t68 = allocNode(); V t85 = allocNode(); 
    V t77 = allocNode(); V t69 = allocNode(); V t86 = allocNode(); V t78 = allocNode(); 
    V t87 = allocNode(); V t79 = allocNode(); V t88 = allocNode(); V t89 = allocNode(); 
    tic();
    PROFILE(4,0, pfnLoadTable(t0, initLiteralSym("part")));
    PROFILE(5,0, pfnColumnValue(t1, t0, initLiteralSym("p_partkey")));
    PROFILE(6,0, pfnColumnValue(t4, t0, initLiteralSym("p_brand")));
    PROFILE(7,0, pfnColumnValue(t6, t0, initLiteralSym("p_size")));
    PROFILE(8,0, pfnColumnValue(t7, t0, initLiteralSym("p_container")));
    PROFILE(9,0, pfnLoadTable(t10, initLiteralSym("lineitem")));
    PROFILE(10,0, pfnColumnValue(t13, t10, initLiteralSym("l_partkey")));
    PROFILE(11,0, pfnColumnValue(t16, t10, initLiteralSym("l_quantity")));
    PROFILE(12,0, pfnColumnValue(t17, t10, initLiteralSym("l_extendedprice")));
    PROFILE(13,0, pfnColumnValue(t18, t10, initLiteralSym("l_discount")));
    PROFILE(14,0, pfnColumnValue(t25, t10, initLiteralSym("l_shipinstruct")));
    PROFILE(15,0, pfnColumnValue(t26, t10, initLiteralSym("l_shipmode")));
    PROFILE(16,0, copyV(t28,initLiteralSymVector(2, (S []){"AIR", "AIR REG"})));
    PROFILE(19,0, q19_autofusion_13(t31, (V[]){t25,t26,t28}));
    // L c=0; DOI(vn(t31), c+=vB(t31,i)) P("c = %lld, ratio = %.2lf%%\n",c,100.0*c/vn(t31)); getchar();
    // c = 214377, ratio = 3.57%
    PROFILE(20,0, q19_patterncompress_0((V []){t33, t36, t37, t38}, t31, (V []){t13, t16, t17, t18}));
    PROFILE(28,0, copyV(t52,initLiteralSymVector(4, (S []){"SM CASE", "SM BOX", "SM PACK", "SM PKG"})));
    PROFILE(33,0, q19_autofusion_12(t57, (V[]){t6,t4,t7,t52}));
    PROFILE(39,0, copyV(t63,initLiteralSymVector(4, (S []){"MED BAG", "MED BOX", "MED PKG", "MED PACK"})));
    PROFILE(44,0, q19_autofusion_11(t68, (V[]){t6,t4,t7,t63}));
    PROFILE(50,0, copyV(t74,initLiteralSymVector(4, (S []){"LG CASE", "LG BOX", "LG PACK", "LG PKG"})));
    PROFILE(55,0, q19_autofusion_10(t79, (V[]){t6,t4,t7,t74}));
    PROFILE(57,0, pfnCompress(t81, t57, t1));
    PROFILE(58,0, pfnCompress(t82, t68, t1));
    PROFILE(59,0, pfnCompress(t83, t79, t1));
    PROFILE(60,0, pfnMember(t84, t33, t81));
    PROFILE(61,0, pfnMember(t85, t33, t82));
    PROFILE(62,0, pfnMember(t86, t33, t83));
    PROFILE(67,0, q19_autofusion_9(t91, (V[]){t84,t36,t85,t86}));
    PROFILE(68,0, q19_patterncompress_1((V []){t106, t107}, t91, (V []){t37, t38}));
    PROFILE(72,0, q19_autofusion_8(t119, (V[]){t91,t37,t38}));
    PROFILE(73,0, copyV(t120,initLiteralSym("revenue")));
    PROFILE(74,0, pfnList(t121, 1, (V []){t119}));
    PROFILE(75,0, pfnTable(t122, t120, t121));
    E elapsed = calc_toc();
    printV2(t122, 20);
    return elapsed;
}

