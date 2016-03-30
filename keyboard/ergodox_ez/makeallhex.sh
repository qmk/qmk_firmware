#!/bin/bash
#a quick tool to rebuild all the hex files for the keymaps in the ./keymaps/ directory
make clean
for f in ./keymaps/*
	do 
		MAPNAME=$(echo "$f"|sed -r 's#^./keymaps/##')
		make KEYMAP=$MAPNAME
		mv ergodox_ez.hex "$f/$MAPNAME.hex"
done
