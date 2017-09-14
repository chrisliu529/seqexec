#!/bin/bash

shmid=`./alloc`
total=200000000
step=1000000
for (( i=0; i<$total; i+=$step )); do
    ./seqexec --key=test ./inc $shmid $step &
done

shmid2=`./alloc`
for (( i=0; i<$total; i+=$step )); do
    ./seqexec --key=test2 ./inc $shmid2 $step &
done

sleep 10
n=`./read $shmid`
ipcrm -m $shmid
if [ "$total" == "$n" ]; then
    echo "test1 ok"
else
    echo "test nok: $n"
    exit 1
fi

n=`./read $shmid2`
ipcrm -m $shmid2
if [ "$total" == "$n" ]; then
    echo "test2 ok"
    exit 0
fi

echo "test nok: $n"
exit 1
