# Experiments for TPC-H

## Folder Structure

Environment variables

    export ROOT_HONEY=$PWD


|   CPU-based  |   GPU-based  |
| :----------: | :----------: |
| MonetDB      | OmniSci      |
| Hyper        | Hawk         |
| HorsePower   | HorsePower   |

## Introduction to Systems

In this section, there is a list of related systems and their basic usage.

### MonetDB

[Source code download](https://www.monetdb.org/downloads/sources/)

    - version 11.33.3 (Apr 2019)
    - version 11.29.3 (Mar 2018)
    - version 11.27.9 (Jul 2017-SP2)

Embedded Python configuration ([MonetDB + Python](https://www.monetdb.org/blog/embedded-pythonnumpy-monetdb))

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

Its binary version 2015 runs on sable-intel, however, it fails to run on
sable-tigger because of unsupported instructions found.


### HorsePower

Usage

    ./horse -help



