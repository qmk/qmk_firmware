# Mardopad

## Intro

This is a slightly modified VIA-compatible keymap for the Tidbit, created for mardoran.

## Firmware Creation/Flashing

* The board comes preflashed for you, so unless you want to modify the keymap yourself, you can skip to [VIA Configuration](#via-configuration).

* Drag this, and possibly the entire tidbit keyboard folder, from this branch to your local directory, as tidbit is not on the master repo.
```qmk_firmware/keyboards/nullbitsco/tidbit```
* Edit any changes you want to make to the encoder rotation keycodes between lines 77 and 100 in `keymap.c.`
* Compile this in unix-like shell by running the following:
```qmk compile -kb nullbitsco/tidbit -km mardopad```
* Press the reset button on the back of the board while it is plugged in, which will put it into bootloader mode.
* In QMK Toolbox, flash the firmware once you see that the ATmega32U4 is detected.
![QMK Toolbox screenshot](qmktoolbox.png)
* The board should now be functional and detectable on VIA.

## VIA Configuration

* Once the board is flashed, open an up-to-date installation of VIA.
* The board will not be detected automatically, which is why I've included a draft file called tidbit.json.
![VIA Design Tab](via-design.png)
* Look at the VIA design tab and choose to load a draft definition. Load the tidbit.json file.
* The board will now be editable in VIA. Have fun! 