# CannonKeys Ripple HS

Ripple Keyboard by Upas

* Keyboard Maintainer: [Andrew Kannan](https://github.com/awkannan)
* Hardware Supported: STM32F072CBT6

Make example for this keyboard (after setting up your build environment):

    make cannonkeys/ripple_hs:default
    
Flashing example for this keyboard:

    make cannonkeys/ripple_hs:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard
* **Physical reset button**: Toggle the switch on the back of the pcb to "1" and briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.  In the pre-supplied keymaps it is on the second layer, replacing the R key.
