#!/bin/bash
machine=`hostname`
dbserver=monetdbd
db=monetdb
mserver=mserver5
mode="thread"  # thread/all

config_tigger(){
    datafarm="/mnt/local/hanfeng/datafarm/2019"
    dbpath="TPCHDB/tpch1"
}

config_intel(){
    datafarm="/mnt/local/datafarm/2019"
    dbpath="TPCHDB/tpch1"
}

error(){
    echo "Error>> $1"
    exit 1
}

if [ $machine = "tigger" ]; then
    config_tigger
elif [ $machine = "sableintel" ]; then
    config_intel
else
    error $machine
fi

function setup_database(){
    (set -x && cd ${datafarm} && ${dbserver} start TPCHDB && ${db} status)
    if [ $? -ne 0 ]; then
        error "Database initilization fails"
    fi
}

function close_database(){
    (set -x && cd ${datafarm} && ${dbserver} stop TPCHDB)
}

function restart_database(){
    close_database
    setup_database
}

function run_code(){
    setup_database ## begin
    # run code
    close_database ## end
}

function usage(){
    printf '%s\n' \
        ">> $0 <mode>" "" \
        "mode: server" \
        "  Init mserver, please" \
        "  1) run the following code (\\q to exit)" \
        "  2) open a new terminal and run ./run_client.sh &> log/all-t1.txt" \
        "  3) report summarized result: grep -A 3 avg_query log/all-t1.txt | python cut.py" "" \
        "mode: start" \
        "  Init a tpch sf1 database" "" \
        "mode: stop" \
        "  Stop a database" "" \
        "mode: restart" \
        "  Restart a database" ""
    if [ "$#" -eq 1 ]; then
        if [ "$1" -ne 0 ]; then
            exit $1
        fi
    else
        exit 99
    fi
}

setup_server(){
    mkdir -p log
    echo "${mserver} --set embedded_py=true --dbpath=${datafarm}/${dbpath} --set monet_vault_key=${datafarm}/${dbpath}/.vaultkey --set gdk_nr_threads=1"
}

if [ "$#" -eq 1 ]; then
    mode=$1
    if [ $mode = "server" ]; then
        usage 0
        setup_server
    elif [ $mode = "start" ]; then
        setup_database
    elif [ $mode = "stop" ]; then
        close_database
    elif [ $mode = "restart" ]; then
        restart_database
    else
        usage
    fi
else
    usage
fi


