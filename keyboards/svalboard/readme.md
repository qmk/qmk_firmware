# Svalboard RP2040

![Svalboard](https://www.svalboard.com)

Svalboard - Datahand Forever!

Keyboard Maintainer: [morganvenable](https://github.com/morganvenable/) [@morganmoto](https://twitter.com/morganmoto)  
Hardware Supported: RP2040, Svalboard Alpha 
Hardware Availability: [Store](https://www.svalboard.com)

Build example for this keyboard (after setting up your build environment):
```
qmk compile -kb svalboard -km default
```
You can then copy the UF2 file from your qmk_firmware root directory to the device's drive letter.

Or you can flash directly with:
```
qmk flash --keyboard svalboard --keymap default
```

Svalboard currently uses the EE_HANDS flag to set handedness, so the MCU is either Left or Right, permanently. If for some reason you need to reflash this parameter to be the other hand, you must add the appropriate side bootloader parameter to program the eeprom -- this cannot be done by drag-and-drop of a UF2 file:
```
qmk flash --keyboard svalboard --keymap default -bl uf2-split-left
qmk flash --keyboard svalboard --keymap default -bl uf2-split-right
```

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader
Errata -- you need to hold BOOT while plugging in USB to enter bootloader mode, because early units have a schematic gaffe on the reset button.
There is a rework available, but it involves desoldering a resistor and running a wire -- not reccommended.