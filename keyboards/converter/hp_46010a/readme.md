# HP 46010A

![46010A](https://deskthority.net/w/images/a/a5/HP_46010A_--_top.jpg)

A converter for the eponymous keyboard.

Keyboard Maintainer: [Listofoptions](https://github.com/listofoptions)  
Hardware Supported: HP 46010A, Teensy 2.0  

Make example for this keyboard (after setting up your build environment):

    make converter/HP_46010A:default
    
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

to get a matrix created if your board uses a different one (i used the US layout) please see the following gists:
for the matrix itself: https://gist.github.com/listofoptions/cdf70d94767e9c6c027741850a24c568
for the program to generate the matrix: https://gist.github.com/listofoptions/d245e370678024edbe5bed8c8ab17999

to build the actual converter, you are going to need to either splice into the a connector or, use a multi-meter to buzz/ohm out which wires go where.
from the bottom of the pcb the pins are arraged as follows:


      4 5 6
     3 2 1  


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


teensy | HP 46010A
----|-----
gnd | gnd (6)
vcc | vcc (3)
PB0 | reset (1)
PB1 | clock (5)
PB3 | data out (4)
gnd | no connection (2) -- optional
