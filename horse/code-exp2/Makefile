# Note:
# libhorse.a must be placed before libpcre2-8.a

gcc_lynx       = gcc
gcc_tigger     = gcc-8
gcc_sableintel = gcc-8

targ = compile
cccc = ${gcc_${sys}} #clang-6 / gcc-8
cccl = clang-6
include_files = main.c 
include_dirs  = -I${HORSE_LIB_INCLUDE} -I${HORSE_SRC_CODE}
include_libs  = -L${HORSE_LIB_LIB} -lcore -lpcre2-8
include_flags = -DQALL -std=c99 -fopenmp -lm -lstdc++ -march=native 
include_flags_c = $(include_flags) -DSELECT_C # -v -ftime-report

ifeq ($(opt),debug)
	opt_level = -g
else ifeq ($(opt),profile)
	opt_level = -g -O3
else
	opt_level = -O3
endif

all: q19

## GCC debugging option: https://stackoverflow.com/a/21861251
## adding the option `-v -ftime-report`

## @echo hello $@, shows the name of target
## `echo $@ | tr a-z A-Z` returns the name of the target with uppercase

## NO_PROFILE_INFO: don't show line profiling information
##       HORSE_EXP: load queries under exp/
##       HORSE_CUR: load queries under cur/

q%:
	$(cccc) -o "compile-$@" \
    $(opt_level)       \
    $(include_files)   \
    $(include_dirs)    \
    $(include_libs)    \
    $(include_flags_c) \
    -DINCLUDE_`echo $@ | tr a-z A-Z` -DHORSE_${src} $(report)

