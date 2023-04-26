https://learn.adafruit.com/using-qmk-on-rp2040-microcontrollers/adafruit-macropad-with-qmk

# Kanagawa

A 75% keyboard with oled and rotary encoder for Elite-C

    Keyboard Maintainer : Ciaanh

    Hardware Supported : Kanagawa PCB rev 2.1

    Hardware Availability : https://github.com/Ciaanh/keyboards/tree/main/Kanagawa


Make example for this keyboard (after setting up your build environment):

```sh
qmk compile -kb ciaanh/kanagawa/iso -km default

qmk compile -kb ciaanh/kanagawa/ansi -km default
```

## Bootloader

Enter the bootloader in 4 ways:

* **Bootmagic reset**: Hold down the key just bellow the rotary encoder push-button on power-up.
* **Physical reset button**: Press twice the button on the side while the board is connected.
* **BOOT button** Hold down the rotary encoder push-button on power-up or reset.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.
