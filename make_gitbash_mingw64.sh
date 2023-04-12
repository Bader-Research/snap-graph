#!/bin/bash

./configure --enable-openmp LD=ld
cd src/sprng2.0/
make LIBTOOL="/c/Progra~1/Git/usr/bin/sh.exe ../../libtool"
cd ../..
make
