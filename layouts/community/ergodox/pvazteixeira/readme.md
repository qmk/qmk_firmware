# pedro's ergodoxes

layout shared between the 'classic' and 'infinity' versions

## flashing

### classic
run `make ergodox_ez:pvazteixeira:teensy` and press the reset button

### infinity
plug in left only and run `sudo make ergodox_infinity:keymapname:dfu-util`

plug in right and run `sudo make ergodox_infinity:keymapname:dfu-util MASTER=right`


## see also

* [QMK docs - layouts](https://docs.qmk.fm/#/feature_layouts)
* [Ergodox infinity](https://github.com/qmk/qmk_firmware/tree/master/keyboards/ergodox_infinity)
