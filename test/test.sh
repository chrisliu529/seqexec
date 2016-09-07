#!/bin/bash

shmid=`./alloc`
total=2000000000
step=10000000
for (( i=0; i<$total; i+=$step )); do
    ./seqexec ./inc $shmid $step &
done
sleep 20
n=`./read $shmid`
./dealloc $shmid
if [ "$total" == "$n" ]; then
    echo "test ok"
    exit 0
fi
echo "test nok: $n"
exit 1
