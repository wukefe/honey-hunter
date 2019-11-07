#!/bin/bash
machine=`hostname`

config_tigger(){
    datafarm="/mnt/local/hanfeng/hyper"
    dbpath="tpch1.dump"
    dbdriver=${datafarm}/bin/driver
    threads=( 1 2 4 8 12 )
    mkdir -p log
}

if [ $machine = "tigger" ]; then
    config_tigger
else
    error $machine
fi

tpch_dir="../tpch_2_17_0/hyper"
query="$(seq 1 10)"

run_thread(){
    THREADS=$1 ${dbdriver} ${datafarm}/${dbpath} -q `for i in ${query}; do echo ${tpch_dir}/$i.sql; done` 2> /dev/null
}

for t in "${threads[@]}"
do
    echo "thread $t"
    run_thread $t > log/t${t}-all.txt
done


