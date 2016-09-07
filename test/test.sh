#!/bin/bash

shmid=`./alloc`
./seqexec ./inc $shmid 100000000 &
./seqexec ./inc $shmid 100000000 &
sleep 3
n=`./read $shmid`
./dealloc $shmid
if [ "200000000" == "$n" ]; then
    echo "test ok"
    exit 0
fi
echo "test nok: $n"
exit 1
