Overview
========

This is a dvorak based layout for the Ergodox EZ. Its basic key layout is similar to the Atreus "dvorak_42_key" layout. In fact this layout was created for seamless switching between the Ergodox EZ and Atreus. On the base layer, the keys that don't exist on the Atreus are mapped to MEH shortcuts and can be interpreted by Autohotkey. This layout only makes use of the 42 keys that the Atreus also has for the main functionality. 

How to build 
------------
make ergodox_ez:dvorak_42_key:teensy

Layers
------
* BASE: basic dvorak layout
* KEYNAV: arrow-key navigation. Momentary toggle held by thumb allows the right hand to navigate through text as well as copy/paste/cut, page up/page down
* KEYSEL: similar to KEYNAV, except for shift-selection
* COMBINED: this is a layer that combines numbers, brackets and special characters. !@#$%^&*( can be type by shift+COMBINED+1/2/3/etc..
* MOUSE: mouse navigation, as well as browser tab-left/tab-right shortcuts
* SHELL_NAV: Linux Bash shortcuts (move forward/backward in command line, Ctrl+C, recall last argument, etc
* SHELL_SCREEN: Linux screen (run multiple terminals in one window) shortcuts such as open new tabs, switch between tabs