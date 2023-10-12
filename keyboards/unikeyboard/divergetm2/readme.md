# diverge tm2

A 4x6x2 split ortholinear keyboard with 2u spacebars like the Levinson (similar to Let's Split). Made by [Unikeyboard](https://unikeyboard.io).

Keyboard Maintainer: [IslandMan93](https://github.com/islandman93) and [xton](https://github.com/xton)  
Hardware Supported: Pro Micro  
Hardware Availability: [Diverge TM2](https://unikeyboard.io/product/diverge-tm/)

Make example for this keyboard (after setting up your build environment):

    make unikeyboard/divergetm2:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

# Flashing the first time

Disassemble the case so you have access to each Pro Micro. Flash each half with QMK Toolbox by connecting the USB cable and shorting RST and GND. After that, just use the soft reset key on your respective layout to reflash both halves. 

# Reflashing Animus

Reflashing the stock firmware is pretty easy. Just follow the same steps in the [original guide](https://imgur.com/a/8UapN). You will have to manually reset the Pro Micro (by shorting the GND and RST) during the upload step. Then reapply your keymap through Arbites.
