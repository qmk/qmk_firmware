# 3dfoxc

A [3d-printed whitefox](https://www.thingiverse.com/thing:2952008) with an Elite-C microcontroller.

This is a build of [matt3o's "How to Build a Custom Keyboard" guide](https://matt3o.com/book/), except that I have replaced the Teensy with an [Elite-C v4](https://keeb.io/products/elite-c-low-profile-version-usb-c-pro-micro-replacement-atmega32u4). Presumably you could replace it with anything compatible.  The USB-C port had to be enlarged with dremel, and the mount for the Teensy was ground off and replaced with everyone's favorite rapid modeling polymer ... hot glue.

## Wiring

Badly, because I have never done this before. Build pics available upon request, I guess.


## Flashing

Use DFU for the Elite-C:

```
$ make handwired/3dfoxc:default:dfu
```