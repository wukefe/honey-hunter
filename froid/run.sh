usage() {
    printf '%s\n' \
        "Usage: $0 <cmd>" "" \
        "  1) $0 pyfunc <qid>    ## execute q{id}/q{id}.pyfunc" "" \
        "  2) $0 tpch <qid>      ## standard tpch queries" ""
    exit 1
}

DB_NAME="tpch1"

if [ $# -eq 2 ]; then
    cmd=$1
    if [ $cmd = "pyfunc" ]; then
        (set -x && cd q$2 && mclient -d ${DB_NAME} -t performance q$2.pyfunc)
    elif [ $cmd = "tpch" ]; then
        (set -x && cd ../tpch_2_17_0/monetdb && mclient -d ${DB_NAME} -t performance $2.sql)
    else
        usage
    fi
else
    usage
fi



