#!/bin/bash
# adjust for cpu 
# -j 16 gave best result on a hyperthreaded quad core core i7

LIMIT=10
THREADS="-j 16"
KMAP=iso_split_rshift

echo "We need sudo later"
sudo ls 2>&1 /dev/null

function wait_bootloader {
	echo "Waiting for Bootloader..."
	local STARTTIME=$(date +"%s")
	local REMIND=0
    local EXEC=dfu-programmer
    local TARGET=atmega32u4
	while true
	do
		sudo $EXEC $TARGET get > /dev/null 2>&1
		[ $? -eq 0 ] && break
		ENDTIME=$(date +"%s")
		DURATION=$(($ENDTIME-$STARTTIME))
		if [ $REMIND -eq 0 -a $DURATION -gt $LIMIT ]
		then 
			echo "Did you forget to press the reset button?"
			REMIND=1
		fi
        sleep 1
	done
}
make clean
make KEYMAP=${KMAP} ${THREADS}
if [[ $? -eq 0 ]]
then
    echo "please trigger flashing!"
    wait_bootloader
    sudo make KEYMAP=${KMAP} dfu ${THREADS}
else
    echo "make failed"
    exit 77
fi
