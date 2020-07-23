#!/bin/bash
machine=`hostname`
runs=10

usage(){
    printf '%s\n\n' \
        "$0 <option>" \
        "  1) $0 <run_id>                   # specify a run id" \
        "  2) $0 <run_id> time [report]     # get or report compilation time" \
        "  3) $0 <run_id> report [<thread>] # report execution time for all or a thread" \
        "  4) $0 <run_id> single <qid>      # run a single query" \
        "  5) $0 ls                         # show run IDs"
    exit 1 
}

error(){
    echo "[ERROR] $1"
    exit 99
}

set_env(){
    if [ $machine = "sableintel" ]; then
        if [ -z ${single_thread} ]; then
            threads=(1 2 4 8 16 32 64)
        else
            threads=(${single_thread})
        fi
    elif [ $machine = "tigger" ]; then
        threads=(1 2 4 8 16)
    else
        error "This repository is only for the machine <sableintel> and <tigger>, NOT for *${machine}*"
    fi
}

run_build(){
    local log_file="${log_folder}/build_log.txt"
    echo "** Logging to ${log_file} **"
    rm -f ${log_file}
    for id in {1..22}
    do
        echo "** Building query $id **"
        ./make.sh exp ${id} &>> ${log_file}
    done
}

run_build_time(){
    local log_file="${log_folder}/all_compile.txt"
    echo "** Logging to ${log_file} **"
    rm -f ${log_file}
    for id in {1..22}
    do
        echo "Compiling q$id"
        (set -x && time make q${id} sys=${machine} report="-ftime-report") &>> ${log_file}
    done
}

run_one(){
    local thread=$1
    local log_file="${log_folder}/all_t${thread}.txt"
    echo "** Logging to ${log_file} **"
    rm -f ${log_file}
    for id in {1..22}
    do
        ./run-query.sh ${id} ${runs} $thread &>> ${log_file}
    done
}

run_all(){
    run_build
    for thread in ${threads[@]}
    do
        run_one ${thread}
    done
}

run_single(){
    id=$1
    (set -x && ./make.sh exp ${id})
    for thread in ${threads[@]}
    do
        local log_file="${log_folder}/single_q${id}_t${thread}.txt"
        echo "** Logging to ${log_file} **"
        ./run-query.sh ${id} ${runs} $thread &> ${log_file}
    done
    # fetch ...
    for thread in ${threads[@]}
    do
        local log_file="${log_folder}/single_q${id}_t${thread}.txt"
        cat ${log_file} | grep "Run with" | cut -d'|' -f 1 | awk -F " " '{print $NF}'
    done
}


run_report(){
    local log_file="${log_folder}/all_t$1.txt"
    echo "Fetch execution time from ${log_file}"
    cat ${log_file} | grep "Run with" | cut -d'|' -f 1 | awk -F " " '{print $NF}'
}

run_report_all(){
    local tmp_file="/tmp/report.txt"
    rm -f ${tmp_file}
    for th in ${threads[@]}
    do
        local log_file="${log_folder}/all_t${th}.txt"
        cat ${log_file} | grep "Run with" | cut -d'|' -f 1 | awk -F " " '{print $NF}' >> ${tmp_file}
    done
    cat ${tmp_file} | python ../util/report-all.py
}

run_report_build(){
    local log_file="${log_folder}/all_compile.txt"
    echo "Fetch compilation time (s) from ${log_file}"
    cat ${log_file} | grep "TOTAL" | awk -F " " '{print $5}' | python ../code-exp2/util/convert.py
}

set_log(){
    log_folder="log/run$1"
    mkdir -p ${log_folder}
}

set_env
if [ $# -eq 1 ]; then
    if [ $1 = "ls" ]; then
        ls log
    else
        set_log $1
        time run_all
    fi
elif [ $# -eq 2 ]; then
    if [ $2 = "time" ]; then
        set_log $1
        time run_build_time
    elif [ $2 = "report" ]; then
        set_log $1
        run_report_all
    else
        usage
    fi
elif [ $# -eq 3 ]; then
    if [ $2 = "report" ]; then
        set_log $1
        run_report $3
    elif [ $2 = "time" -a $3 = "report" ]; then
        set_log $1
        run_report_build
    elif [ $2 = "single" ]; then
        set_log $1
        run_single $3
    else
        usage
    fi
else
    usage
fi
