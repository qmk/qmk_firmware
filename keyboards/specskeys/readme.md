# specs_keys - REV 1 (confirmed working, typing on it now :D)
* Keyboard Maintainer: [specs32](https://github.com/yourusername)

### TKL ISO keyboard based on an g80-3000HAD running QMK

15 Years ago I found 2 g80-3000 HAD Keyboards in the trash, one broke lately so I designed a PCB to mount these sweet sweet Cherry MX black switches on it.

The base plate is the acryl plate from an old TFT Monitor cut to size and sanded. (roughly)
Between PCB and baseplate is some foamy stuff for dampening.


So, except the pcb and the mcu and a couple smd parts this thing is completly salvaged from trash.

Overall cost per board with parts (except switches) : 18 €

(8 € per PCB and 10 € for SMD parts, rest is salvaged, so this is probably the cheapest build out there)


Features  :
  - ATMega 32U4 @ 8 MHz (why the crystal ... such a waste, sigh)
  - USB-C jack **with FUSE and full ESD protection** (gnd vcc d+ d-)
  - MOSFET controlled bottom backlighting pads for 14 LEDs with resistors plus 2 extra 2mm connectors for lantern style lightning
  - Scroll and caps indicators (active low atm.. I kinda like it)
  - SPI interface and reset
  - 340mA overall power consumption with full lights (I put in UV / pink LEDs and 14 Ω Resistors)


the QMK layout and config can be found here :  https://github.com/specs32/specs_keys/tree/main/specskeys

I hex the MCU with avrdude from cli after QMK compile, somehow I had trouble with bootloaders all my life ^^ (also safer this way .. I guess;))

> qmk_firmware [master]× » avrdude -c usbasp -p m32u4 -B10 -U lfuse:w:0xD2:m -U hfuse:w:0x98:m -U efuse:w:0xFF:m

> qmk_firmware [master]× » avrdude -c usbasp -pm32u4 -B10 -Uflash:w:.build/specskeys_default.hex                

designed with kicad nightly Version: (5.99.0-10004-g132ec37b56), release build
and some gimp

credits :

- evyd13 and ebastler (to modify the g80-3003 design was my initial attempt but I did build the PCB from scratch then)
- the designers of evil80 (whoever that might be, couldn't find any infos on that) I used some of their qmk layout information as info for mine

License on the KiCAD Design files : ♥ CC-BY-SA-4.0

All other parts of this build inherit their Licenses from their origin.

![3d-VIEW](https://github.com/specs32/specs_keys/blob/main/gh80-3003-nicosmod/gh80-3003-nicosmod.png)

![PCB](https://github.com/specs32/specs_keys/blob/main/gh80-3003-nicosmod/pcb.png) 

![FOTO1](https://github.com/specs32/specs_keys/blob/main/photo_2021-05-04_18-33-33.jpg)

![FOTO2](https://github.com/specs32/specs_keys/blob/main/photo_2021-05-04_18-33-43.jpg)

