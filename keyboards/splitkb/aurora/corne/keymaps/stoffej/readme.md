

## OLEDs

Both the primary and secondary side should be filled with characters.


## Build 

qmk compile -kb splitkb/aurora/corne/rev1 -km stoffej -e CONVERT_TO=elite_pi



## generate ASCII

https://github.com/caksoylar/keymap-drawer

uses config.properties
https://github.com/yskoht/keymapviz

keymapviz qmk_firmware_work/keyboards/splitkb/aurora/corne/keymaps/stoffej/keymap.c -k crkbd 


## SVG generating and qmk c2json 
Creates a keymap.json from a keymap.c.

Note: Parsing C source files is not easy, therefore this subcommand may not work with your keymap. In some cases not using the C pre-processor helps.

Usage:

from qmk root

qmk c2json -kb splitkb/aurora/corne -km stoffej  keyboards/splitkb/aurora/corne/keymaps/stoffej/keymap.c -o keyboards/splitkb/aurora/corne/keymaps/stoffej/stoffej_keymap.json --no-cpp

 
 then upload to 
 https://keymap-drawer.streamlit.app/
 
 
get the yaml file from the download button
and place it in the keymap folder

can be done by command line interface also
keymap -c my_config.yaml draw my_keymap.yaml > stoffej.svg
