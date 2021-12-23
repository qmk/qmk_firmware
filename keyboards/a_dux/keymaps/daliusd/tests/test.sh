#!/bin/sh

echo $1
cd ..
gcc -g tests/test.c -o tests/test && tests/test
date
