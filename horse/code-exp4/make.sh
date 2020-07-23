#!/bin/bash
usage(){
    printf '%s\n\n' \
        "Usage: (default optimization: release)" \
        "  1) $0 <exp> <qid>   ## create a query under exp/" \
        "  2) $0 lib           ## build libcore.a"
    exit 1
}

sys=`hostname`
if [ "$#" -eq 1 ]; then
    if [ $1 = "lib" ]; then
        (set -x && cd ${HORSE_SRC_CODE} && ./make.sh lib)
    else
        usage
    fi
elif [ "$#" -eq 2 ]; then
    folder=$1 ; id=$2
    if [ $1 = "exp" ]; then
        (set -x && cp "${folder}/q${id}.h" gencode.h)
        (set -x && make q${id} sys=${sys})
    else
        usage
    fi
else
    usage
fi

