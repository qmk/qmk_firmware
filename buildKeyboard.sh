#! /bin/bash

if [[ -z "${1}" ]]; then
    layout="default"
else
    layout=$1
fi

qmk clean &&
    echo -e "<<<<< DISCONNECT KEYBOARD HALFS AND PLUG IN MASTER >>>>>\n\n"
qmk flash -kb sofle/rev1 -km $layout &&
    echo -e "<<<<< DISCONNECT KEYBOARD HALFS AND PLUG IN SLAVE >>>>>\n\n"
qmk flash -kb sofle/rev1 -km $layout
