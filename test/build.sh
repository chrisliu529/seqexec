#!/bin/bash

cd ../src && ./build.sh && cd ../test && \
gcc -Wall -Werror=cpp -o alloc alloc.c && \
gcc -Wall -Werror=cpp -o dealloc dealloc.c && \
gcc -Wall -Werror=cpp -o inc inc.c && \
gcc -Wall -Werror=cpp -o read read.c && \
gcc -Wall -Werror=cpp -o rm_sem rm_sem.c
