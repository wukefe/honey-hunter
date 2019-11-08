
## Server Mode

Run the following code to see the latest  instructions

    ./run.sh server

Extra manual work needed

    terminal 1:
        run mserver to start with 1/2/4/8/12 threads

    terminal 2:
        run code from ./run_client.sh and save log files
        then, run the python script cut.py to fetch numbers from log files

## MonetDB Configurations

setup datafarm

    monetdbd-19 create /mnt/local/hanfeng/datafarm/2019
    monetdbd-19 start  /mnt/local/hanfeng/datafarm/2019
    monetdb-19 create tpch1
    monetdb-19 release tpch1
    mclient-19 -d tpch1
        \<tpch/dss.ddl
        \<tpch/initTPCH1.txt



