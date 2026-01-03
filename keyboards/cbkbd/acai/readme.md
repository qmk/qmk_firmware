# Acai

![Acai](https://imgur.com/eWKoH96.png)

A 10x4 ortholinear keyboard made and sold by Coffee Break Keyboards. PCB designed by Snipeye. Case designed by Rain and Obabo. [More info on cbkbd.com](https://www.cbkbd.com/product/acai)

* Hardware Supported: Acai PCB
* Hardware Availability: [cbkbd.com](https://www.cbkbd.com/product/acai-pcb)

Make example for this keyboard (after setting up your build environment):

    make cbkbd/acai:default

Flashing example for this keyboard:

    make cbkbd/acai:default:flash

See the [build environment setup](getting_started_build_tools) and the [make instructions](getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available