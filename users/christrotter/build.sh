#!/bin/bash
HOME_DIR=/Users/christrotter/git/printing/qmk_fw
KB_DIR=$HOME_DIR/keyboards/handwired/tractyl_manuform_ct/5x6_right
USER_DIR=$HOME_DIR/users/christrotter

if [ -z "$1" ];then
    echo "ERROR: Specify build or flash!"
    exit 1
else
    echo "INFO: We are going to $1"
fi

cd $HOME_DIR

if [ "$1" == "build" ];then
    echo "INFO: Just doing a build..."
    make handwired/tractyl_manuform_ct/5x6_right:christrotter
elif [ "$1" == "flash" ];then
    echo "INFO: Flashing RIGHT side..."
    make handwired/tractyl_manuform_ct/5x6_right:christrotter:dfu-split-right
    echo "INFO: Now plug in the LEFT side..."
    make handwired/tractyl_manuform_ct/5x6_right:christrotter:dfu-split-left
elif [ "$1" == "right" ];then
    echo "INFO: Flashing RIGHT side..."
    make handwired/tractyl_manuform_ct/5x6_right:christrotter:dfu-split-right    
elif [ "$1" == "left" ];then
    echo "INFO: Flashing LEFT side..."
    make handwired/tractyl_manuform_ct/5x6_right:christrotter:dfu-split-left    
else
    echo "WARN: You didn't specify either 'build' or 'flash'."
fi
