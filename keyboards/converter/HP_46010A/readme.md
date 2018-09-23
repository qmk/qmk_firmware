# HP 46010A

![46010A](https://deskthority.net/w/images/a/a5/HP_46010A_--_top.jpg)

A converter for the eponymous keyboard.

Keyboard Maintainer: [Listofoptions](https://github.com/listofoptions)  
Hardware Supported: HP 46010A, Teensy 2.0  

Make example for this keyboard (after setting up your build environment):

    make converter/HP_46010A:default

included in this directory is a arduino program for teensy 2.0 (only one tested, might work on others) to grab a copy of the keyboard matrix.
also included is a csv containing the matrix as an ordered by clock #, byte array
    
See [build environment setup](https://docs.qmk.fm/build_environment_setup.html) then the [make instructions](https://docs.qmk.fm/make_instructions.html) for more information.

to build the actual converter, you are going to need to either splice into the a connector or, use a multi-meter to buzz/ohm out which wires go where.
from the bottom of the pcb the pins are arraged as follows:

`
      4 5 6
     3 2 1  
`

connect a six pin modular connector of the 6p6c variaty.
then lop off the other end of the cable, striping the wires inside.
use the ohm-meter to find the corresponding wire for each pin on the bottom of the pcb

the pin meanings are as follows:
1 reset
2 no connection
3 vcc
4 data out
5 clock
6 ground

wire the ground and power pins to ground and 5v power on the teensy (or other avr device of your choice)
connect
on the teensy the connection is as follows

`
teensy - hp 46010A
gnd    - gnd (6)
vcc    - vcc (3)
PB0    - reset (1)
PB1    - clock (5)
PB3    - data out (4)
gnd    - no connection (2) -- optional
`
