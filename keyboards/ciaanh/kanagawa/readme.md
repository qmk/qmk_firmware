# Kanagawa

A 75% keyboard with oled and rotary encoder for Raspberry Pico

    Keyboard Maintainer : Ciaanh

    Hardware Supported : Kanagawa PCB rev 2.1

    Hardware Availability : https://github.com/Ciaanh/keyboards/tree/main/Kanagawa


Make example for this keyboard (after setting up your build environment):

```sh
qmk compile -kb ciaanh/kanagawa/iso -km default

qmk compile -kb ciaanh/kanagawa/ansi -km default
```

## Bootloader

* **Bootmagic reset**: Hold down the rotary encoder push-button on power-up.
* **Physical buttons**: Press both the reset and the Bootsel button on the back while the board is connected.
