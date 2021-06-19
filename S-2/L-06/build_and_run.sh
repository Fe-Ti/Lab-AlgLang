#!/bin/bash
# Copyright 2021 Fe-Ti <btm.007@mail.ru>
# build scripts V2
PRJ_NAME=main
RUN_SIMPLE=1
RUN_VALGRIND=0
REBUILD=0
COMPILE_OPTS=" -pthread "

for s in 2 4 #6 8 16 32 64
do
for t in 1 2 3 4 5 6 7 8
do
	for l in 10 20 100 1000 10000 100000 #1000000
	do
		cmd=" ${l} ${t} ${s}"
		source ../../build_and_run_cmds
	done
done
done
