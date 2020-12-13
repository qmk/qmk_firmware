# Paddino02

10-keys DIY mechanical macropad/gamepad. Features staggered columns, 2 thumb keys, symmetric PCB (you can build right-handed and left-handed versions with the same PCB). 

Project page on GitHub, with build steps and 3d-printable files:

https://github.com/Pimentoso/Paddino02

* Keyboard Maintainer: [Michele Ferri](https://github.com/Pimentoso)
* Hardware Supported: Paddino02 PCB rev1, rev2 + Arduino Pro Micro
* Hardware Availability: the PCB is open source and can be freely printed at websites such as [JLCPCB](https://jlcpcb.com/)

### To compile:

`make pimentoso/paddino02/rev2/right:default`

`make pimentoso/paddino02/rev2/left:default`

`make pimentoso/paddino02/rev1:default` (legacy version of the PCB)

### To flash:

`make pimentoso/paddino02/rev2/right:default:flash`

`make pimentoso/paddino02/rev2/left:default:flash`

`make pimentoso/paddino02/rev1:default:flash` (legacy version of the PCB)

### Default keymap

![Keymap](https://raw.githubusercontent.com/Pimentoso/qmk_firmware/master/keyboards/pimentoso/paddino02/keymap.png)

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
