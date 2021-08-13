# TouhouPad

![TouhouPad](https://i.imgur.com/JeEqeEs.png)

A 10 key gamepad specifically for playing Touhou danmaku games.

You can find building instructions and gerber files to print the circuit board on the [project page.](https://github.com/Pimentoso/TouhouPad_v2)

* Keyboard Maintainer: [Michele Ferri](https://github.com/Pimentoso)
* Hardware Supported: Paddino02 PCB rev1, rev2 + Arduino Pro Micro
* Hardware Availability: the PCB is open source and can be freely printed at websites such as [JLCPCB](https://jlcpcb.com/)

Make example for this keyboard (after setting up your build environment):

    make pimentoso/touhoupad:default

The gamepad case is completely exposed on the underside, so to enter bootloader mode, just short the RST and GND pins of the pro micro using a metal object.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
