#!/bin/sh

docker run -it -e keymap=tk -e keyboard=ergodox_ez --rm -v $('pwd'):/qmk:rw qmk
