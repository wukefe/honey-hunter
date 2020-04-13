# Experiments for HorseIR Code

## code-exp1

Before run, check run id (choose a new id for a new run)

    ./run-all.sh ls

Run with common commands

    ./run-all.sh <run_id>  # run experiment with id
    ./make.sh 6 exp        # build q6
    ./run.sh exp 6 10      # build q6 and run 10 times

Originate

    - copy from v1 (see the legacy section)

Upgrade with new libraries

    - header: ${HORSE_SRC_CODE}/global.h ${HORSE_LIB_INCLUDE}/pcre2.h
    - library: ${HORSE_LIB_LIB}/libcore.a ${HORSE_LIB_LIB}/libpcre2-8.a
    - compiler: gcc-8

Report execution time

    cat log/run1/all_t1.txt | grep "Run with" | cut -d'|' -f 1 | awk -F " " '{print $NF}'

Report total compilation time

    cat log/run1/all_compile.txt | grep "TOTAL" | awk -F " " '{print $5}'


## Legacy

Run all benchmarks (except 16 / 21)

    code
        v1/compile-static/exp
    
    logs
        v1/compile-static/logs/run-tigger


