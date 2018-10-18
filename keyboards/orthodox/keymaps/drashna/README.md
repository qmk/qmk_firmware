Overview
========

This is my personal Orthodox configuration, and my daily driver.

Most of the code resides in my userspace, rather than here, as I have multiple keyboards.

How to build 
------------
make orthodox/rev1:drashna:teensy

Layers
------
* QWERTY/DVORAK/COLEMAK/WORKMAN: basic layout, default set like the OLKB boards. Default is set and persists on power cycle.
* RAISE: Contains function keys and unshifted symbols
* LOWER: Contains function keys and shifted symbols
* ADJUST: contains special codes (layout defaults, RGB codes, Audio codes, and volume control)

All layers have RGB specific indicators, so you can see what layer you're on by the underglow.

Orthodox Specific Code
----------------------

Shift, Control and Alt all light up a specific RGB LED for a certain color, based on it's status, adding a visual indicator of OSMs or regular mods are held down.
