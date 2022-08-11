# Lime Keyboard

![Lime Keyboard](https://github.com/HellSingCoder/LimeKeyboard/blob/main/media/lime_keyboard.jpeg?raw=true)

Lime is a 6×4+6 keys column-staggered split keyboard with encoder and joystick support. Based on [Lily58](https://github.com/kata0510/Lily58), [Corne](https://github.com/foostan/crkbd), [Helix](https://github.com/MakotoKurauchi/helix) and [Sofle](https://github.com/josefadamcik/SofleKeyboard) keyboards. This board features a reversible PCB, OLEDs, Underglow and Bluetooth support. The PCB has holes for floating or screwed mounts but can be also mounted with a gasket.

The Lime keyboard was created by [HellTM](https://github.com/HellSingCoder) with the help of the QMK and custom keyboard community.

Build guide and a build log not available yet

* Keyboard Maintainer: [HellSingCoder](https://www.simonepellegrino.com/) (GitHub: [HellTM](https://github.com/HellSingCoder))
* Hardware Supported: LimeKeyboard PCB, ProMicro  
* Hardware Availability: [PCB & Case Data](https://github.com/HellSingCoder/LimeKeyboard)

Make example for this keyboard (after setting up your build environment):

    make lime:default

Flashing example for this keyboard:

    make lime:default:flash

Press reset button on he keyboard when asked. You can do that in 3 ways:
* **Physical reset button**: Briefly press the button near the TRRS connector on the PCB - if you haven't installed one, short the pads instead
* **Keycode in layout**: Press the key mapped to `RESET` (`Lower` + `Raise` + `Esc` on the default layout)
* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard

Disconnect the first half, connect the second one and repeat the process.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
