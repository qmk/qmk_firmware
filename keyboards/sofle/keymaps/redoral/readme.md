# redoral's custom VIA compatible keymap for Sofle v2

Based on the `via` keymap and modified it to my own keymap and OLED display preference.

![Real life image of the OLEDs with this firmware](./screenshots/header.webp?raw=true "Header")

### Features:

-   Qwerty base, custom MO(1) layer tailored to my own preference
-   All transparent MO(2) and MO(3) layers (to start from scratch)
-   The OLED on master half shows selected layer and caps lock state and is rotated, also my name because I didn't know what else to put on there. I suggest updating that string to whatever you like
-   The OLED on the other half shows a Witcher signs image (as seen on the photo)
-   Mouse keys support, MO(1) layer by default has mouse key bindings on offhand board
-   1000 hz definition on `config.h` because I am not sure if that is default?
-   VIA support


### Notes

-   I use this on my Sofle v2 prebuilt by [ergomech.store](https://ergomech.store).
-   I use an RP2040 controller so I have to convert it for that mc when building the firmware, like the following:

```sh
qmk flash -kb sofle -km redoral -e CONVERT_TO=promicro_rp2040
```
