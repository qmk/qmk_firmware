# Baumkuchen

![takashicompany/baumkuchen](https://i.imgur.com/NS39x44h.png)

Baumkuchen is a 13-key macropad with a radial key layout.  
The board can be used as a circuit or as a switch plate by cutting out the keyswitch Pro Micro part.  
It is compatible with Cherry MX compatible keyswitches, and a rotary encoder can be optionally installed.  
LEDs can also be mounted to make it glow.  
The board is reversible, allowing you to choose the arrangement of keys and Pro Micro according to your usage style.

* Keyboard Maintainer: [takashicompany](https://github.com/takashicompany)
* Hardware Supported: Baumkuchen PCB, Pro Micro
* Hardware Availability: https://github.com/takashicompany/baumkuchen

Make example for this keyboard (after setting up your build environment):

    make takashicompany/baumkuchen:default

Flashing example for this keyboard:

    make takashicompany/baumkuchen:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
