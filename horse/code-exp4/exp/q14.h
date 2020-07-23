// Parsing time (ms): 0.113
 // - #: 2
 // - #: 3
 // - #: 8
 // - #: 3
// Total # of fused stmts: 16
static I q14_autofusion_7(V z, V *x);
static I q14_patternindex_0(V *z, V *x, V y);
static I q14_autofusion_3(V z, V *x);
static I q14_autofusion_6(V z, V *x);
static I q14_autofusion_5(V z, V *x);

static I q14_autofusion_7(V z, V *x){
    V x0=x[0]; // t12
    initV(z, H_B, vn(x0));
    DOP(vn(x0), vB(z,i)=AND(GEQ(vD(x0,i),19950901),LT(vD(x0,i),19951001))) R 0;
}
static I q14_patternindex_0(V *z, V *x, V y){
    V z0 = z[0]; // t58
    V z1 = z[1]; // t59
    V x0 = x[0]; // t26
    V x1 = x[1]; // t27
    initV(z0, H_E, vn(y));
    initV(z1, H_E, vn(y));
    DOP(vn(z0), {
        vE(z0,i) = vE(x0, vL(y,i));
        vE(z1,i) = vE(x1, vL(y,i));
    })
    R 0;
}

static I q14_autofusion_3(V z, V *x){
    V x0=x[0]; // t73
    V x1=x[1]; // t58
    V x2=x[2]; // t59
    Q id0=getSymbol("PROMO%");
    pcre2_code *re = getLikePatten("PROMO%");
    pcre2_match_data *match = pcre2_match_data_create_from_pattern(re, NULL);
    if(re==NULL) R 99;
    I jit_status = pcre2_jit_compile(re, PCRE2_JIT_COMPLETE);
    initV(z, H_E, 1);
    E r[H_CORE]; DOI(H_CORE, r[i]=0)
    DOLIKE(vn(x0), {
        B t = LIKEMATCH(getSymbolStr(vQ(x0,i)),getSymbolSize(vQ(x0,i)),re,match);
        r[tid]+=PLUS(MUL(t,MUL(vE(x1,i),MINUS(1,vE(x2,i)))),MUL(NOT(t),0));})
    E r0=0; DOI(H_CORE, r0+=r[i]) ve(z)=r0;
    pcre2_code_free(re);
    pcre2_match_data_free(match);
    R 0;
}

static I q14_autofusion_6(V z, V *x){
    V x0=x[0]; // t58
    V x1=x[1]; // t59
    E c = 0; L tot=0;
    initV(z, H_E, 1);
    DOP(vn(x0), c+=MUL(vE(x0,i),MINUS(1,vE(x1,i))))
    vE(z,0) = c;
    R 0;
}
static I q14_autofusion_5(V z, V *x){
    V x0=x[0]; // t87
    V x1=x[1]; // t88
    initV(z, H_E, vn(x0));
    DOP(vn(x0), vE(z,i)=DIV(MUL(100,ve(x0)),ve(x1))) R 0;
}

L q14_peephole_0(V *z, V y, V *x){
    V z0 = z[0]; // t21
    V z1 = z[1]; // t25
    V z2 = z[2]; // t26
    V x0 = x[0]; // t2
    V x1 = x[1]; // t6
    V x2 = x[2]; // t7
    L len = vn(y), k = 0;
    L lenZ = 0, parZ[H_CORE], offset[H_CORE];
    DOI(H_CORE, parZ[i]=offset[i]=0)
    CHECKE(getNumOfNonZero(y,parZ));
    DOI(H_CORE, lenZ += parZ[i])
    DOIa(H_CORE, offset[i]=parZ[i-1]+offset[i-1])
    initV(z0,vp(x0),lenZ);
    initV(z1,vp(x1),lenZ);
    initV(z2,vp(x2),lenZ);
    DOT(len, if(vB(y,i)){L c=offset[tid]++;vLL(z0,c)=vLL(x0,i);vE(z1,c)=vE(x1,i);vE(z2,c)=vE(x2,i);}) R 0;
}

L q14_loopfusion_1_new(V z, V *x){
    // z -> t84
    V x0 = x[0]; // t75
    V x1 = x[1]; // t55
    V x2 = x[2]; // t56
    E t = 0;
    initV(z,H_E,1);
    DOP(vn(x0), t+=PLUS(MUL(vB(x0,i),MUL(vE(x1,i),MINUS(1,vE(x2,i)))),MUL(NOT(vB(x0,i)),0)), reduction(+:t))
    ve(z) = t; R 0;
}


static E compiled_main(){
    V t0 = allocNode(); V t3 = allocNode(); V t7 = allocNode(); V t8 = allocNode(); 
    V t20 = allocNode(); V t12 = allocNode(); V t22 = allocNode(); V t50 = allocNode(); 
    V t42 = allocNode(); V t26 = allocNode(); V t18 = allocNode(); V t51 = allocNode(); 
    V t27 = allocNode(); V t19 = allocNode(); V t52 = allocNode(); V t37 = allocNode(); 
    V t38 = allocNode(); V t47 = allocNode(); V t80 = allocNode(); V t48 = allocNode(); 
    V t81 = allocNode(); V t73 = allocNode(); V t49 = allocNode(); V t90 = allocNode(); 
    V t82 = allocNode(); V t58 = allocNode(); V t91 = allocNode(); V t83 = allocNode(); 
    V t59 = allocNode(); V t92 = allocNode(); V t84 = allocNode(); V t93 = allocNode(); 
    V t85 = allocNode(); V t86 = allocNode(); V t78 = allocNode(); V t87 = allocNode(); 
    V t79 = allocNode(); V t88 = allocNode(); V t89 = allocNode(); 
    V m0 = allocNode();
    tic();
    PROFILE(4,0, pfnLoadTable(t0, initLiteralSym("lineitem")));
    PROFILE(5,0, pfnColumnValue(t3, t0, initLiteralSym("l_partkey")));
    PROFILE(6,0, pfnColumnValue(t7, t0, initLiteralSym("l_extendedprice")));
    PROFILE(7,0, pfnColumnValue(t8, t0, initLiteralSym("l_discount")));
    PROFILE(8,0, pfnColumnValue(t12, t0, initLiteralSym("l_shipdate")));
    PROFILE(11,0, q14_autofusion_7(t20, (V[]){t12}));
    if(false){
        PROFILE(12,0, pfnCompress(t22, t20, t3));
        PROFILE(13,0, pfnCompress(t26, t20, t7));
        PROFILE(14,0, pfnCompress(t27, t20, t8));
    }
    else { // expensive
        PROFILE(12,0, q14_peephole_0((V []){t22,t26,t27},t20,(V []){t3,t7,t8}));
    }
    PROFILE(15,0, pfnLoadTable(t37, initLiteralSym("part")));
    PROFILE(16,0, pfnColumnValue(t38, t37, initLiteralSym("p_partkey")));
    PROFILE(17,0, pfnColumnValue(t42, t37, initLiteralSym("p_type")));
    PROFILE(18,0, pfnEnum(t47, t38, t22));
    PROFILE(19,0, pfnValues(t48, t47));
    PROFILE(20,0, pfnKeys(t49, t47));
    PROFILE(21,0, pfnLen(t50, t49));
    PROFILE(22,0, pfnLt(t51, t48, t50));
    PROFILE(23,0, pfnWhere(t52, t51));
    PROFILE(24,0, q14_patternindex_0((V []){t58, t59}, (V []){t26, t27}, t52));
    PROFILE(26,0, pfnIndex(t73, t42, t48));
    if(false){ // faster
        P("fused\n");
        PROFILE(36,0, q14_autofusion_3(t87, (V[]){t73,t58,t59}));
    }
    else { // slower
        P("not fused\n");
        //PROFILE(27,0, pfnLike(m0, t73, initLiteralSym((S)"PROMO%")));
        PROFILE(27,0, pfnLike2(m0, t73, initLiteralSym((S)"PROMO%")));
        PROFILE(36,0, q14_loopfusion_1_new(t87, (V[]){m0,t58,t59}));
    }
    PROFILE(37,0, q14_autofusion_6(t88, (V[]){t58,t59}));
    PROFILE(39,0, q14_autofusion_5(t90, (V[]){t87,t88}));
    PROFILE(40,0, copyV(t91,initLiteralSym("promo_revenue")));
    PROFILE(41,0, pfnList(t92, 1, (V []){t90}));
    PROFILE(42,0, pfnTable(t93, t91, t92));
    E elapsed = calc_toc();
    printV2(t93, 20);
    return elapsed;
}

