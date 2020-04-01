#!/bin/bash
time ./setup_exp.sh "all" | mclient -d tpch1 -t performance
# time ./setup_exp.sh "partial" | mclient -d tpch1 -t performance

