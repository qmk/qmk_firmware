# ortho5by12 // Through Hole

A Plaid-style 5x12 design with two indicator LEDs.

Uses a Schottky 1N4729A/3.6V diode. This is left out of the Plaid BOM which is identical, except for number of 1N4148 diodes (60+attrition). I recommend using 10k resistors for the LEDs instead of the Plaid's 1.5k to make them less glaring. I reckon hsgw was just trying to shave down the parts cost by re-using the 1.5kohm.

I use a spare PCB as the backplate since it has the same dimensions.

This was developed on Linux Mint so you'll have to adapt the commands yourself if you run anything else.

pic here: https://www.reddit.com/r/MechanicalKeyboards/comments/g0ukw4/ortho5by12_through_hole/

* Keyboard Maintainer: [gipetto](https://github.com/itsnoteasy)
* Hardware Supported: ATmega328P with V-USB
* Hardware Availability: [PCB](https://github.com/itsnoteasy/misc/blob/master/ortho5by12.zip)

Make example for this keyboard (after setting up your build environment):

    make ortho5by12:default

Flash firmware:

    make ortho5by12:default:flash

Bootloader doesn't seem to work for the time being. I deleted the last line in ortho5by12.hex and copied the USBasp bootloader onto the end in a text editor, then flashed over AVRISP using a Teensy 2.0 (following the [QMK ISP Flashing Guide](https://docs.qmk.fm/#/isp_flashing_guide)). I used a cut up MCU socket soldered to stripboard to make an ISP programming socket. Remember to make fuse in the USBasp directory on a new MCU. 

## ISP pinout:

            R4

    Reset  SCK    MISO

    GND    MOSI   VCC

                         C5

## A few build notes:

I haven't found it easy to get into bootloader mode every time. sometimes there's no alternative but 
to use the ISP header, or pull the IC.

Put the switch diodes in with the banded end down towards the switches. This gives the fastest scan rate. If you don't and go by the silkscreen then you can swap COL2ROW/ROW2COL from whatever it currently is. The speed penalty is negligible anyway. The silkscreen is probably wrong, so do the component placement from KiCad nightly; it caught me out.
If you attempt to map the duplex matrix you will hate me so don't bother. I should have used one LED pin as an extra matrix pin, but in my naivete I thought it was used for a bootloader function. The duplexing is compensated for in a header file so you can use a standard Preonic keymap with any extra unavailable pins commented out. On the upside there's some funky twin LED code out there for Plaids which should be compatible.

Boot and Reset switches have swapped position to my other PCB to ease routing - Boot is on the right.

## Bootloader

Use USBaspLoader from hsgw's repository.

https://github.com/hsgw/USBaspLoader/tree/plaid

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions]
(https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our 
[Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
