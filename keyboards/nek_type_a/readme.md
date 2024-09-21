# nek_type_a

![NEK Type A Keyboard](https://i.imgur.com/XFnjlQ9.jpg)

Natural Ergonomic Keyboard, Type A

Keyboard Maintainer: [Mike Roberts](https://github.com/ecopoesis)  
Hardware Supported: Custom PCBs from https://github.com/ecopoesis/nek-type-a  
Hardware Availability: https://github.com/ecopoesis/nek-type-a  

## Design

This is a column-driven split keyboard using three custom PCBs connected with ribbon cables. The left and right PCBs are
passive: they only have the diodes and switches needed to make the matrix. The center PCB has an Adafruit Feather 32u4 and
MCP23017 expander.

The left matrix has its rows and columns directly connected to the Feather. The right matrix has its rows connect to the
Feather (using the same pins as the left matrix) and its columns connected to the expander. The expander uses the LUFA
hardware TWI driver.

Bluetooth is enabled.

## Building

Make and install this keyboard (after setting up your build environment):
```
make nek_type_a:default:avrdude
```

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
