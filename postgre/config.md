Download Postgres

    wget https://ftp.postgresql.org/pub/source/v10.0/postgresql-10.0.tar.bz2

Install

    ./configure --prefix=/mnt/local/postgres10 --with-python PYTHON=/usr/bin/python2.7
    make
    make install

Alias

    ln -s /mnt/local/postgres10/bin/initdb
    ln -s /mnt/local/postgres10/bin/pg_ctl
    ln -s /mnt/local/postgres10/bin/postgres
    ln -s /mnt/local/postgres10/bin/psql

Create DB

    initdb -D POStGREDB
    pg_ctl -D /mnt/local/datafarm/POSTGREDB -l logfile start
    OR
    postgres -D /mnt/local/datafarm/POSTGREDB

Init DB (https://www.codementor.io/devops/tutorial/getting-started-postgresql-server-mac-osx)

    psql postgres
    CREATE ROLE chf WITH LOGIN PASSWORD '123';
    ALTER ROLE chf CREATEDB;

Command lines

    \du: list of users
    \list:

    psql -U chf -d tpchdb
    psql -U chf -d tpchdb -f ./tpch_2_17_0/dbgen/dss.ddl

Add superuser
    psql postgres
    ALTER USER myuser WITH SUPERUSER;

Load data (need pre-process to remove the last '|' in a row)

    copy nation from '/mnt/local/tpch-tbl/postgres/nation.tbl' with delimiter as '|';
    copy customer from '/mnt/local/tpch-tbl/postgres/customer.tbl' with delimiter as '|';
    copy lineitem from '/mnt/local/tpch-tbl/postgres/lineitem.tbl' with delimiter as '|';
    copy orders from '/mnt/local/tpch-tbl/postgres/orders.tbl' with delimiter as '|';
    copy partsupp from '/mnt/local/tpch-tbl/postgres/partsupp.tbl' with delimiter as '|';
    copy part from '/mnt/local/tpch-tbl/postgres/part.tbl' with delimiter as '|';
    copy region from '/mnt/local/tpch-tbl/postgres/region.tbl' with delimiter as '|';
    copy supplier from '/mnt/local/tpch-tbl/postgres/supplier.tbl' with delimiter as '|';

Add primary keys (the same as MonetDB)

    ALTER TABLE REGION ADD PRIMARY KEY (R_REGIONKEY);
    ALTER TABLE NATION ADD PRIMARY KEY (N_NATIONKEY);
    ALTER TABLE PART ADD PRIMARY KEY (P_PARTKEY);
    ALTER TABLE SUPPLIER ADD PRIMARY KEY (S_SUPPKEY);
    ALTER TABLE PARTSUPP ADD PRIMARY KEY (PS_PARTKEY,PS_SUPPKEY);
    ALTER TABLE CUSTOMER ADD PRIMARY KEY (C_CUSTKEY);
    ALTER TABLE LINEITEM ADD PRIMARY KEY (L_ORDERKEY,L_LINENUMBER);
    ALTER TABLE ORDERS ADD PRIMARY KEY (O_ORDERKEY);

Add indexing

    CREATE UNIQUE INDEX lineitem_idx ON lineitem (L_ORDERKEY, L_LINENUMBER);
    CREATE UNIQUE INDEX part_idx ON part (P_PARTKEY);

