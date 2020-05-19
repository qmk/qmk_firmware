# ortho5by12 // Through Hole

a plaid style 5x12 design with two indicator leds.

schottky 1N4729A/3.6V (this is left out of the plaid bom which is identical except for number of 1n4148 diodes(60+attrition)
I recommend using 10k resistors for the leds instead of the plaids 1.5K to make them less glaring. I reckon hsgw was just 
trying to shave down the parts cost by re-using the 1.5Kohm.
I use a spare pcb as the backplate since it has the same dimensions.
This was developed on linux mint so you'll have to adapt the commands yourself if you run anything else.

pic here: https://www.reddit.com/r/MechanicalKeyboards/comments/g0ukw4/ortho5by12_through_hole/

* Keyboard Maintainer: [gipetto](https://github.com/itsnoteasy)
* Hardware Supported: ATMEGA328p with vusb [PCB](https://github.com/itsnoteasy/misc/blob/master/ortho5by12.zip)
* Hardware Availability: no

Make example for this keyboard (after setting up your build environment):
    make ortho5by12:default

Flash firmware:
 make ortho5by12:default:flash

bootloader doesn't seem to work for the time being. i deleted the last line in ortho5by12.hex and copied the usbasp bootloader
 onto the end in a test editor, then flashed over avrisp using a teensy2.0(following the qmk isp flashing guide) 
I used a cut up mcu socket soldered to stripboard to make an isp programming socket. remember to make fuse in the usbasp 
directory on a new mcu. 

avrdude -c avrisp -p m328p -P /dev/ttyACM0 -b19200 -U flash:w:ortho5by12_default.hex
avrdude -c usbasp -b19200 -p m328p

ISP pinout

        r4

reset  sck   miso


gnd    mosi  vcc

                     c5

a few build notes:

I haven't found it easy to get into bootloader mode every time. sometimes there's no alternative but 
to use the isp header, or pull the ic.

put the switch diodes in with the banded end down towards the switches. this gives the fastest scan 
rate. if you don't and go by the silkscreen then you can swap col2row/row2col from whatever it currently is. 
the speed penalty is negligible anyway.
the silkscreen is probably wrong so do the component placement from kicad nightly. it caught me out.
If you attempt to map the duplex matrix you will hate me so don't bother. I should have used one led
pin as an extra matrix pin, but in my naivete i thought it was used for a bootloader function.
the duplexing is compensated for in a header file so you can use a standard preonic keymap with
any extra unavailable pins commented out. on the upside there's some funky twin led code out there 
for plaids which should be compatible.
boot and reset switches have swapped position to my other pcb to ease routing. boot is on the right.

## Bootloader
use usbasploader in his repository.
https://github.com/hsgw/USBaspLoader/tree/plaid


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions]
(https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our 
[Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
