# Bastyl_firmware

## Important information

If you modify this firmware, make sure to always have a RESET key that can be triggered using only the master side ! This way you ensure that you can always flash the keyboard, even if you mess up.

Otherwise if you're stuck, open the case and reset manually by shorting Gnd and Rst.

## Details

qmk firmware for the Bastyl keyboard

Made to be used with qmk 0.10.40 +

### Modify using qmk

* Clone qmk
* make the required changes to `keymap.c`
* `make bastyl_via:via` 
* flash with qmk toolbox

### Modify using via

* Load `keyboards/bastyl_via/jsons/bastyl.json` into via
* Connect your keyboard, it should be recognized
* Make the required changes to the keymap using the gui
