https://learn.adafruit.com/using-qmk-on-rp2040-microcontrollers/adafruit-macropad-with-qmk

qmk compile -kb ciaanh/kanagawa2040 -km default

# Ciaanh Kanagawa2040


```sh
qmk compile -kb ciaanh/kanagawa2040 -km default
```

# Kanagawa

A 75% keyboard with oled and rotary encoder for Elite-C

    Keyboard Maintainer : Ciaanh

    Hardware Supported : Kanagawa PCB  

    Hardware Availability : https://github.com/Ciaanh/keyboards/tree/main/Kanagawa


Make example for this keyboard (after setting up your build environment):

    qmk compile -kb ciaanh/kanagawa -km default

Driver issues https://docs.qmk.fm/#/faq_build?id=unknown-device-for-dfu-bootloader


## Bootloader

Enter the bootloader in 4 ways:

* **Bootmagic reset**: Hold down the key just bellow the rotary encoder push-button on power-up.
* **Physical reset button**: Press twice the button on the side while the board is connected.
* **BOOT button** Hold down the rotary encoder push-button on power-up or reset.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.
