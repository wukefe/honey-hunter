## Modes

### Server Mode

Run the following code to see the latest instructions

    ./run.sh server

Extra manual work needed

    terminal 1:
        run mserver to start with 1/2/4/8/12 threads

    terminal 2:
        run code from ./run_client.sh and save log files
        then, run the python script cut.py to fetch numbers from log files

Fetch mserver commands (when run in default)

    ps aux | grep -i mserver


### Action Modes

start/stop/restart

    ./run.sh <action>


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


## Experiments

Server

    ./run.sh server     ## copy the command line and run in a new window

Run

    ./run_exp.sh &> log/run1/exp_t1.txt

Retrieve

    grep -A 3 avg_query log/run1/exp_t1.txt | python cut.py


### Performance measurement: Two methods

Method 1: Use profiling functions (e.g. q22 below)

    +------------+
    | query_time |
    +============+
    |         81 |
    |         78 |
    |         84 |
    |         81 |
    |         81 |
    |         80 |
    |         80 |
    |         81 |
    |         81 |
    |         81 |
    +------------+

Method 2: Run with `-t performance` can report execution time as well.

    run: 82.116 ms
    run: 83.478 ms
    run: 89.365 ms
    run: 86.348 ms
    run: 83.217 ms
    run: 83.666 ms
    run: 82.742 ms
    run: 81.940 ms
    run: 83.775 ms
    run: 83.316 ms
    run: 83.917 ms

We can see the method 1 is overall faster than the method 2.
In our experiments, we report the numbers from using method 1.



### Potential bug: q6 with more than 51 threads

If the given number of threads is greater than 51, the following error occurs:

    Could not allocate space

Likely a bug in the release, Nov2019-SP1.


