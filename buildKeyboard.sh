#! /bin/bash

Y="\033[1;33m"
NC="\033[0m"

if [[ -z "${1}" ]]; then
    layout="default"
else
    layout=${1}
fi

qmk clean &&
    qmk compile -kb sofle/rev1 -km ${layout} &&
    echo -e "$Y<<<<< DISCONNECT KEYBOARD HALFS AND PLUG IN MASTER >>>>>$NC\n\n"
qmk flash -kb sofle/rev1 -km ${layout} &&
    echo -e "$Y<<<<< DISCONNECT KEYBOARD HALFS AND PLUG IN SLAVE >>>>>$NC\n\n"
qmk flash -kb sofle/rev1 -km ${layout}
