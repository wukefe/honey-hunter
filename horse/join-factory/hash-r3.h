

static void r3_hash_main(V z, V x, V y){
    // P("size = %d, row = %d\n", vn(x), vn(vV(x,0)));
    // r2_hash_main(z,vV(x,3),vV(y,3));
    pfnJoinIndex(z,vV(x,3),vV(y,3),JOIN_EQ);
}


static void run_join_r3(){
    V rtn = (V)malloc(sizeof(V0));
    tic();
    r3_hash_main(rtn,data1,data2);
    time_toc("join takes (ms): %g\n\n", elapsed);
}

