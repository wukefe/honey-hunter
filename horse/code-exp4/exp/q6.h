// Parsing time (ms): 0.082
 // - #: 13
// Total # of fused stmts: 13
static I q6_autofusion_1(V z, V *x);

static I q6_autofusion_1(V z, V *x){
    V x0=x[0]; // t12
    V x1=x[1]; // t6
    V x2=x[2]; // t8
    V x3=x[3]; // t7
    E c = 0; L tot=0;
    initV(z, H_E, 1);
    DOP(vn(x0), if(AND(AND(AND(GEQ(vD(x0,i),19940101),LT(vD(x0,i),19950101)),LT(vE(x1,i),24)),AND(GEQ(vE(x2,i),0.05),LEQ(vE(x2,i),0.07)))){\
	c+=MUL(vE(x3,i),vE(x2,i));}, reduction(+:c))
    vE(z,0) = c;
    R 0;
}

static E compiled_main(){
    V t0 = allocNode(); V t6 = allocNode(); V t7 = allocNode(); V t8 = allocNode(); 
    V t20 = allocNode(); V t12 = allocNode(); V t21 = allocNode(); V t22 = allocNode(); 
    V t23 = allocNode(); V t32 = allocNode(); V t24 = allocNode(); V t33 = allocNode(); 
    V t25 = allocNode(); V t26 = allocNode(); V t18 = allocNode(); V t43 = allocNode(); 
    V t19 = allocNode(); V t44 = allocNode(); V t45 = allocNode(); V t46 = allocNode(); 
    V t47 = allocNode(); 
    tic();
    PROFILE(4,0, pfnLoadTable(t0, initLiteralSym((S)"lineitem")));
    PROFILE(5,0, pfnColumnValue(t6, t0, initLiteralSym((S)"l_quantity")));
    PROFILE(6,0, pfnColumnValue(t7, t0, initLiteralSym((S)"l_extendedprice")));
    PROFILE(7,0, pfnColumnValue(t8, t0, initLiteralSym((S)"l_discount")));
    PROFILE(8,0, pfnColumnValue(t12, t0, initLiteralSym((S)"l_shipdate")));
    PROFILE(21,0, q6_autofusion_1(t44, (V[]){t12,t6,t8,t7}));
    PROFILE(22,0, copyV(t45,initLiteralSym((S)"revenue")));
    PROFILE(23,0, pfnList(t46, 1, (V []){t44}));
    PROFILE(24,0, pfnTable(t47, t45, t46));
    E elapsed = calc_toc();
    printV2(t47, 20);
    return elapsed;
}
