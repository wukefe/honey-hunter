## Server Mode

Run the following code to see the latest  instructions

    ./run.sh server

Extra manual work needed

    terminal 1:
        run mserver to start with 1/2/4/8/12 threads

    terminal 2:
        run code from ./run_client.sh and save log files
        then, run the python script cut.py to fetch numbers from log files

## Configurations

setup datafarm

    monetdbd create /mnt/local/hanfeng/datafarm/2019/TPCHDB
    monetdbd start  /mnt/local/hanfeng/datafarm/2019/TPCHDB
    monetdb create tpch1
    monetdb release tpch1
    mclient -d tpch1
        \<tpch/dss.ddl
        \<tpch/initTPCH1.txt

notes

    the working directory for Python binding is set to the current database
    path i.e. /mnt/sableintel/datafarm/2019/TPCHDB

## Exporting Data

[Syntax](https://www.monetdb.org/Documentation/Cookbooks/SQLrecipes/ExportingBulkData)

    COPY <select_query> INTO <file_name | STDOUT> ...

- It can be used to export intermediate data from database queries


