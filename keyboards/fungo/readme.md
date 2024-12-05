# fungo split keyboard (fungo)


A split keyboard for my hands.

* Keyboard Maintainer: [bojiguard](https://github.com/bojiguard/)
* Hardware Supported: Pro Micro, elite-c, nicenano
* Hardware Availability: [fungo split keyboard](https://github.com/bojiguard/fungo-split-keyboard)

Make example for this keyboard (after setting up your build environment):

    make fungo/rev1:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).  


## Bootloader

* **Physical reset button**: Briefly press the button on the front of the PCB

## Characteristics

The circuits on the left and right keyboard are different.  
Hardware Information: [Document](https://github.com/bojiguard/fungo-split-keyboard)  
matrix: 5x7+3  
left : support oled  
right: support external spi connection  
all: battery switch, battery jack for nicenano  
