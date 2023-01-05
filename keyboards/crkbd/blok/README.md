# Corne Blok

An edition of the Corne keyboard using the RP2040-based Blok microcontroller.
The Blok is pin-compatible with the ProMicro and other similar boards.

Make example for this board (after setting up your build environment):

```sh
qmk compile -kb crkbd/blok -km default
```


## Bootloader

Enter the bootloader in 4 ways:

* **Bootmagic reset**: Hold down the key in the Q or P positions according to
  the QWERTY layout
* **BOOT button** Hold down right button on the bottom of the Blok MCU
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.
