#!/bin/bash

include_folder="-I${HORSE_LIB_INCLUDE} -I${HORSE_SRC_CODE}"
include_lib="-L${HORSE_LIB_LIB} -lcore -lpcre2-8"
include_flag="-std=c99 -fopenmp -lm -lstdc++ -march=native"

(set -x && gcc-8 -O3 -o "group" \
    main.c \
    ${include_folder} \
    ${include_lib} \
    ${include_flag}
)

