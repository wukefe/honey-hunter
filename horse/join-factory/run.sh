#!/bin/bash

usage(){
    printf '%s\n\n' \
        "  1) $0 <qid>    # run a query with all data" \
        "Note: set threads, threads=1 $0 6   ## default: all threads"
    exit 1
}

execute_join(){
    for id in ${sets[@]}
    do
        (set -x && ./join data/q${qid}/d${id}-left.txt data/q${qid}/d${id}-right.txt 6) # 6
    done
}

run_query(){
    qid=$1
    ./make.sh
    if [ ${qid} = '2' ]; then
        # sets=(0 1 2 3 4 5)
        sets=(4)
    elif [ ${qid} = '3' ]; then
        sets=(0)
    elif [ ${qid} = '5' ]; then
        # sets=(0 1 2 3)
        sets=(3)
    elif [ ${qid} = '7' ]; then
        # sets=(0 1 2 3)
        sets=(3)
    elif [ ${qid} = '8' ]; then
        # sets=(0 1 2 3 4 5)
        sets=(0)
    elif [ ${qid} = '9' ]; then
        # sets=(0 1 2)
        sets=(1)
    elif [ ${qid} = '10' ]; then
        # sets=(0 1)
        sets=(1)
    elif [ ${qid} = '11' ]; then
        # sets=(0 1)
        sets=(0)
    elif [ ${qid} = '13' ]; then
        sets=(0)
    elif [ ${qid} = '17' ]; then
        # sets=(0 1 2)
        sets=(0)
    elif [ ${qid} = '18' ]; then
        # sets=(0 1)
        sets=(1)
    elif [ ${qid} = '20' ]; then
        sets=(0)
    elif [ ${qid} = '21' ]; then
        # sets=(0 1 2 3)
        sets=(2)
    else
        echo "Unknown query id: ${qid}"
        exit 1
    fi
    execute_join
}

if [ -z ${threads} ]; then
    threads=1
fi

# set threads
export OMP_PLACES=cores
export OMP_PROC_BIND=spread
export OMP_NUM_THREADS=${threads}


if [ $# -eq 1 ]; then
    run_query $1
else
    usage
fi

