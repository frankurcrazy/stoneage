#!/bin/sh
OUT=include/longzoro/longzoro.h

make clean
echo "#ifndef __LONGZORO_H__
#define __LONGZORO_H__

//特殊功能控製----------------------------------------
#define _ATTESTAION_ID 23

#endif" > $OUT
make

tar -zcvf /csa/saserver/gmsv/gmsv_vip_23.tar.gz /csa/saserver/gmsv/gmsvjt /csa/saserver/gmsv/setup.cf 
