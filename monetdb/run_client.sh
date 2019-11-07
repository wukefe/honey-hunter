#!/bin/bash

mclient=mclient-19

time ./setup_exp.sh "all" | ${mclient} -d tpch1


