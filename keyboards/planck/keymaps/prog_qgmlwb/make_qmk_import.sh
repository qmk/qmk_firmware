#!/bin/bash

pre='{"keyboard":"planck/rev5","keymap":"defaultish_8c03349","layout":"LAYOUT_ortho_4x12","layers":'
mid="$(cat layers.json)"
post=',"author":"","notes":""}'

echo -e "$pre\n$mid\n$post" >qmk_import.json
