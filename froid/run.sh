usage() {
    printf '%s\n\n' \
        "Usage: $0 <cmd>" \
        "  1) $0 pyfunc  <qid>    ## execute q{id}/q{id}.pyfunc" \
        "  2) $0 tpch    <qid>    ## standard tpch queries" \
        "  3) $0 profile <qid>    ## profile pyfunc queries"
    exit 1
}

DB_NAME="tpch1"
log_empty="call sys.querylog_empty();"
log_enable="call sys.querylog_enable();"
log_disable="call sys.querylog_disable();"

if [ $# -eq 2 ]; then
    cmd=$1
    if [ $cmd = "pyfunc" ]; then
        (set -x && cd q$2 && mclient -d ${DB_NAME} -t performance q$2.pyfunc)
    elif [ $cmd = "tpch" ]; then
        (set -x && cd ../tpch_2_17_0/monetdb && mclient -d ${DB_NAME} -t performance $2.sql)
    elif [ $cmd = "profile" ]; then
        (cd q$2 && echo "${log_empty}${log_enable}`cat q$2.pyfunc`${log_disable}" | mclient -d ${DB_NAME} -t performance)
        echo ""
        echo "Check query IDs"
        echo "  echo \"select id, query, avg(run) from sys.querylog_history group by id,query;\" | mclient -d ${DB_NAME} -t performance"
        echo ""
        echo "See query numbers"
        echo "  echo \"select * from sys.querylog_calls;\" | mclient -d ${DB_NAME} -t performance"
    else
        usage
    fi
else
    usage
fi

## Reference
# https://www.monetdb.org/Documentation/Cookbooks/SQLrecipes/QueryHistory

