# Dactyl-CC / Ergo S-1

![DactylCC](https://i.imgur.com/CUbPLZCh.jpeg)
*Dactyl-CC*

![ErgoS-1](https://i.imgur.com/JTLCw3N.jpg)  
*Ergo S-1*

Modelled on the *Kinesis Advantage* (KA) 1|2, though missing it's function and program row, board(s) retain the finger and thumb key placements of the KA but opt to psychically split the handed key-wells instead.

Electronically both the Dactyl-CC and Ergo S-1 are indentical, though psychically the Ergo S-1 has larger casing designed to be used as a palm rest.

* Hardware Supported: Pro micro controller or clones of

### Dactyl-CC
* Keyboard Maintainer: [Michael Johns](https://github.com/mjohns)
* Hardware Availability: [Dactyl CC GitHub](https://github.com/mjohns/dactyl-cc)

Make example for this keyboard (after setting up your build environment):

    make handwired/dactyl_cc:default

Flashing example for this keyboard:

    make handwired/dactyl_cc:default:flash

    
### Ergo S-1
* Keyboard Maintainer: [Andrew Wells](https://github.com/wizarddata)
* Hardware Availability: [Ergo S-1 GitHub](https://github.com/wizarddata/Ergo-S-1)

*`handwired/ergo_s-1` is an alias of `handwired/dactly_cc`*

Make example for this keyboard (after setting up your build environment):

    make handwired/ergo_s-1:default

Flashing example for this keyboard:

    make handwired/ergo_s-1:default:flash


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
