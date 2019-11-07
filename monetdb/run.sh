#!/bin/bash
machine=`hostname`
dbserver=monetdbd-19
db=monetdb-19
mserver=mserver5-19
mode="thread"  # thread/all

config_tigger(){
    datafarm="/mnt/local/hanfeng/datafarm"
    dbpath="TPCHDB/tpch1"
}

error(){
    echo "Error>> $1"
    exit 1
}

if [ $machine = "tigger" ]; then
    config_tigger
else
    error $machine
fi

setup_database(){
    (set -x && cd ${datafarm} && ${dbserver} start TPCHDB && ${db} status)
    if [ $? -ne 0 ]; then
        error "Database initilization fails"
    fi
}

close_database(){
    (set -x && cd ${datafarm} && ${dbserver} stop TPCHDB)
}

run_code(){
    setup_database ## begin
    # run code
    close_database ## end
}

if [ $mode = "thread" ]; then
    printf '%s\n' \
        "Init mserver, please" "" \
        "1) run the following code (\\q to exit)" \
        "2) open a new terminal and run ./run_client.sh &> log/all-t1.txt" "" \
        "3) report summarized result: grep -A 3 avg_query log/all-t1.txt | python cut.py" ""
    mkdir -p log
    echo "${mserver} --dbpath=${datafarm}/${dbpath} --set monet_vault_key=${datafarm}/${dbpath}/.vaultkey --set gdk_nr_threads=1"
else
    run_code
    error "Add support for mode: ${mode}"
fi


