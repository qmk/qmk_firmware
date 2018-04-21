# Atom47 rev2

This is the keymap for rev2 of the Atom47. Only 9 of those have been sold for testing purposes. It had a slightly misaligned usb port and the pcb was too thick (should've been 1.2mm instead of 1.6mm). The pcb only supports the default hardware layout, although /u/ChrisSwires has [modified his](https://www.reddit.com/r/MechanicalKeyboards/comments/7n2dua/not_your_average_core_with_honeywell/) and put a big spacebar in it.

## Support
Keyboard Maintainer: [Matthew Kerfoot(https://github.com/mkerfoot)  
Hardware Supported: Atom47 rev2  
Hardware Availability: None  


## Features
- QMK Firmware  
- In-switch leds  
- Through-hole micro usb connector (less likely to break off!)  
- Easily reachable reset button under the spacebar  
- In-switch CapsLock indicator  

## Build
To build the default keymap, simply run `make atom47/rev2:default`.

For an alternative, heavily modified layout you would just need to run `make atom47/rev2:LEdiodes`.

See [build environment setup](https://docs.qmk.fm/build_environment_setup.html) then the [make instructions](https://docs.qmk.fm/make_instructions.html) for more information.
