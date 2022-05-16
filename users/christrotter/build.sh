#!/bin/bash
HOME_DIR=/Users/chris.trotter/git/printing/qmk_fw
KB_DIR=$HOME_DIR/keyboards/handwired/tractyl_manuform_ct
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
    echo "INFO: Flashing first side..."
    make handwired/tractyl_manuform_ct/5x6_right:christrotter:flash
    echo "INFO: Now plug in the other side..."
    make handwired/tractyl_manuform_ct/5x6_right:christrotter:flash
else
    echo "WARN: You didn't specify either 'build' or 'flash'."
fi