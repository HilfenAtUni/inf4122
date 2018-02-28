#!/bin/bash
SRC=gcc.man
DST=gcc.dst

function calcTime()
{
	buffer=$1
	rm -vf ${DST}
	echo "time ./mycopy -b ${buffer} ${SRC} ${DST}"
	time ./mycopy -b ${buffer} ${SRC} ${DST}
}

calcTime 1; # 2^0
calcTime 2;
calcTime 4;
calcTime 8;
calcTime 16;
calcTime 32;
calcTime 64;
calcTime 128;
calcTime 256;
calcTime 512;
calcTime 1024;
calcTime 2048; #2^11
calcTime 4096;
calcTime 8192;
calcTime 16384;
calcTime 32768;
calcTime 65536;
