# Footy

Footy is a foot pedal built on top of the [keeb.io Stampy](https://keeb.io/products/stampy-rp2040-usb-c-controller-board-for-handwiring) microcontroller. It is intended to be used with a speech to text application like 'handy' or superwhisper.

The case can be 3D printed from [here](https://makerworld.com/en/models/1185240-footy). The design is a fork of this [adafruit foot pedal](https://learn.adafruit.com/USB-foot-switch-circuit-python/overview).

The default keymap is for the letters A, B, and C to help you identify which switches are connected to which pins on the microcontroller. B is the center pin.

## Keymap

Right now there are two primary keymaps, one for 'handy' and one for 'superwhisper'.

Handy's default keymap is for the center switch to be RCTRL + RGUI.

Superwhisper's default keymap is for the center switch to be LOPT + SPACE.

## Build FW

`qmk compile -kb handwired/footy -km handy`