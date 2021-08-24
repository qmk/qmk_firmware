Overview
========

This is my personal Ergodox EZ configuration, and my daily driver.

Most of the code resides in my userspace, rather than here, as I have multiple keyboards.

How to build 
------------
make ergodox_ez:drashna:teensy

Layers
------
* QWERTY/DVORAK/COLEMAK/WORKMAN: basic layout, default set like the OLKB boards. Default is set and persists on power cycle.
* SYMB: F keys across the top, symbols on the left and numpad on the right.
* GAMEPAD: This is the QWERTY layout shifted to the right for FPS type games. Destiny and Overwatch are the primary games for this.
* DIABLO: This contains a Diablo 3 layout, that requires much less reaching or shifting. If Tap Dance is enabled, then it has a "spam" feature. See Userspace for details.
* MOUSE: mouse navigation

All layers have RGB specific indicators, so you can see what layer you're on by the underglow.

Ergodox Specific Code
---------------------

Aside from my userspace code, this includes LED indications for Shift (Green LED), Ctrl (Red LED), and Alt (Blue LED).
