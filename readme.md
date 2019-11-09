# Experiments for TPC-H

|   CPU-based  |   GPU-based  |
| :----------: | :----------: |
| MonetDB      | OmniSci      |
| Hyper        | xxx          |
| HorseIR      | HorseIR      |

## Configuration

- sable-tigger: 12 cores + 32 GB RAM


## Setup for each system

### MonetDb

[Source code download](https://www.monetdb.org/downloads/sources/)

- version 11.33.3 (Apr 2019)
- version 11.29.3 (Mar 2018)
- version 11.27.9 (Jul 2017-SP2)

Embedded Python configuration

    ./bootstrap
    ./configure --prefix=<install_directory> --enable-debug=no --enable-assert=no --enable-optimize=yes
    make -j4 && make install

Setup Python

    monetdb stop tpch1
    monetdb set embedpy=true tpch1
    monetdb start tpch1

Setup Python with mserver5

    mserver5 --set embedded_py=true


### HyPer

- v2015 fails to run on sable-tigger


### HorseIR - CPU



