#!/bin/bash

usage(){
    printf '%s\n\n' \
        "  1. $0 <id> all              # run all tests" \
        "  2. $0 <id> client <thread>  # run tests for one kind of threads" \
        "  3. $0 <id> report <thread>  # report execution time"
    exit 1
}

init_system(){
    machine=`hostname`
    if [ ${machine} = "sableintel" ]; then
        threads=(1 2 4 8 16 32 64)
    elif [ ${machine} = "tigger" ]; then
        threads=(1 2 4 8 16)
    else
        echo "Unsupported: ${machine}"
        exit 1
    fi
}

run_test(){
    port="50005"
    for th in ${threads[@]}
    do
        echo "Setup ${th} thread(s)"
        monetdb -p ${port} set nthreads=${th} tpch1
        monetdb -p ${port} start tpch1
        (time ./setup_exp.sh "all" | mclient -d tpch1 -t performance &> ${folder}/exp_t${th}.txt)
        monetdb -p ${port} stop tpch1
    done
}

run_client(){
    (time ./setup_exp.sh "all" | mclient -d tpch1 -t performance) &> ${folder}/exp_t${1}.txt
}

set_log(){
    folder=log/run$1
    log=${folder}/run-log.txt
    mkdir -p ${folder}
    rm -f ${log}
}

init_system
if [ $# -eq 2 ]; then
    if [ $2 = "all" ]; then
        set_log $1
        run_test | tee ${log}
    else
        usage
    fi
elif [ $# -eq 3 ]; then
    if [ $2 = "client" ]; then
        set_log $1
        run_client $3 | tee ${log}
    elif [ $2 = "report" ]; then
        (set -x && grep -A 3 avg_query log/run$1/exp_t$3.txt | python cut.py)
    else
        usage
    fi
else
    usage
fi


#time ./setup_exp.sh "partial" | mclient -d tpch1 -t performance



