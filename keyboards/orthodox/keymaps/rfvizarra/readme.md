# A personal Orthodox Layout

![Orthodox](https://i.imgur.com/RQ5SKj4.jpg)

This is the layout for my daily driver orthodox. It's based on a custom handwire keyboard that I've been using for quite some time. It's based on Plank's/Let's split layouts for the lower/raise layers. I added the shift, control/enter, alt/altgr and del to the thumb cluster.

To build the firmware run from qmk's project folder

    make orthodox/rev3:rfvizarra

And to flash it, run

    make orthodox/rev3:rfvizarra:avrdude

reset your keyboard pro micro while connected to the PC with a micro usb cable.

Repeat on both halves.

See [install build tools](https://docs.qmk.fm/install-build-tools) then the [build/compile instructions](https://docs.qmk.fm/build-compile-instructions) for more information.
