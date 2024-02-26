# Orthograph

Split ortho keyboard with RGB backlighting

* Keyboard Maintainer: [vladkvit](https://github.com/vladkvit)
* Hardware Supported: Two PCBs + thin Pro Micro compatible boards (Elite C has been extensively tested). Boards with castellated holes (Elite C style) are much easier to install. Maximum thickness is around 3-3.5mm, so a stock Pro Micro (4mm) will not work.
* Hardware Availability: https://github.com/vladkvit/orthograph_keyboard for PCB, https://cad.onshape.com/documents/4f736d64448134c948af475a/w/ccab05fd44a7db98ce27216a/e/49ebfb6b27080b9b45bea74a?renderMode=0&uiState=64dd45dbc62cae486db10048 and https://cad.onshape.com/documents/5ff52821d2cb196f3db3d1e8/w/04b7cb21b748da89c8df31e6/e/486b72e32db97b2dfdf00af8 for the hardware 

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb orthograph -km default

Flashing example for this keyboard:
    qmk flash -kb orthograph -km default
    Then, flash EEPROM with handedness (left / right) on both sides.

The reset button is on the underside of each half of the keyboard.

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
