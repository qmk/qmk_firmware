Overview
========

This is a dvorak based layout for the Atreus. Its basic key layout is similar to the ergodox_ez "dvorak_42_key" layout. In fact this layout was created for seamless switching between the Ergodox EZ and Atreus. 

How to build and flash
----------------------

to build;
make atreus-dvorak_42_key

to flash:
avrdude -p atmega32u4 -c avr109 -U flash:w:atreus_dvorak_42_key.hex  -P COM7

Layers
------
* BASE: basic dvorak layout
* KEYNAV: arrow-key navigation. Momentary toggle held by thumb allows the right hand to navigate through text as well as copy/paste/cut, page up/page down
* KEYSEL: similar to KEYNAV, except for shift-selection
* COMBINED: this is a layer that combines numbers, brackets and special characters. !@#$%^&*( can be type by shift+COMBINED+1/2/3/etc..
* MOUSE: mouse navigation, as well as browser tab-left/tab-right shortcuts