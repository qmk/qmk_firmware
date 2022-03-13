# YD3xn15mx

![YD3xn15mx](https://i.imgur.com/RdrcBlbl.jpg)

* A macro keyboard with 15 keys and 3 encoders

* Keyboard Maintainer: [Thunderbird2086](https://github.com/Thunderbird2086)
* Hardware Supported: Macro Keyboard 15 Keys + 3 Knobs
* Hardware Availability: [AliExpress](https://www.aliexpress.com/wholesale?catId=0&initiative_id=SB_20220214015758&SearchText=Macro+Keyboard+Knob+15Key+%2B+3+Knob)

Make example for this keyboard (after setting up your build environment):

    make yd3xn15mx:default

Flashing example for this keyboard:

    make yd3xn15mx:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
  ![reset switch](https://i.imgur.com/EI1dUYQ.jpeg)
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
