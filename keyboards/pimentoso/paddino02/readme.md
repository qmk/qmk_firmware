# Paddino02

10-keys DIY mechanical macropad/gamepad. Features staggered columns, 2 thumb keys, symmetric PCB (you can build right-handed and left-handed versions with the same PCB). 

Project page on Github, with build steps and 3d-printable files:

https://github.com/Pimentoso/Paddino02

### To compile:

`make pimentoso/paddino02/rev1:default` (legacy version)
`make pimentoso/paddino02/rev2/right:default`
`make pimentoso/paddino02/rev2/left:default`

### To flash:

`make pimentoso/paddino02/rev1:default:avrdude` (legacy version)
`make pimentoso/paddino02/rev2/right:default:avrdude`
`make pimentoso/paddino02/rev2/left:default:avrdude`

### Default keymap

![Keymap](https://raw.githubusercontent.com/qmk/qmk_firmware/master/keyboard/pimentoso/paddino02/keymap.png)
