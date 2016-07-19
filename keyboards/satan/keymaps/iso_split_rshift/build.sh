#!/bin/bash
# adjust for cpu 
# -j 16 gave best result on a hyperthreaded quad core core i7
THREADS="-j 16"
KMAP=iso_split_rshift
echo "We need sudo later"
sudo ls 2>&1 /dev/null
make clean
make KEYMAP=${KMAP} ${THREADS}
if [[ $? -eq 0 ]]
then
    echo "please trigger flashing! you have 5 seconds"
    sleep 5
    sudo make KEYMAP=${KMAP} dfu ${THREADS}
else
    echo "make failed"
    exit 77
fi
