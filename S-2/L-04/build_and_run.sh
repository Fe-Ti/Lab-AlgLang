#!/bin/bash
# Copyright 2021 Fe-Ti <btm.007@mail.ru>
# build script V1
echo [....] Building...
if [ ! -e main ]
then
	g++ -Wall --pedantic --pedantic *.cpp -o main
	RET_VAL=$?
else
	RET_VAL=0
fi

if [ $RET_VAL -ne 0 ]
then
	echo [1A[fail] $RET_VAL
else
	echo [1A[ ok ]
	echo Running without valgrind
	sleep 2
	./main 0

	echo Running with valgrind.
	sleep 2
	valgrind ./main 1
fi

