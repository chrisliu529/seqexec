#!/bin/bash

shmid=`./alloc`
total=200000000
step=1000000
for (( i=0; i<$total; i+=$step )); do
    ./seqexec ./inc $shmid $step &
done
sleep 10
n=`./read $shmid`
ipcrm -m $shmid
if [ "$total" == "$n" ]; then
    echo "test ok"
    exit 0
fi
echo "test nok: $n"
exit 1
