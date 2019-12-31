# Frenchdev : My take on a splitted keyboard for dev and french language
Concept based on
 - [ergodox](https://ergodox-ez.com/)
 - [katy](https://deskthority.net/workshop-f7/katy-keyboard-or-k80cs-key80-contoured-split-t8524.html)

with the added possibility to connect up to 6 external switches like pedals,
 and somewhat like the katy, not all keys are on the same level for easier reach.

### Photos
- [default layout](http://i.imgur.com/r2Nvr4p.png)
- [editable layout on keyboard layout editor](http://www.keyboard-layout-editor.com/#/gists/4480e3ab8026eb7c710a7e22203ef4aa) (keys placement is NOT precise on this)
- [the thing when finished](http://imgur.com/a/6FY8v) 
- [concept and cardboard mockup](http://imgur.com/a/R0vvs)

## Build instructions

    docker run --rm -e keymap=default -e keyboard=frenchdev --rm -v D:/Repositories/qmk:/qmk:rw edasque/qmk_firmware
    
## Laser-cuttable file
There is intentionnaly no hole for the TRRS connector, you are supposed to use a drill for it. 
This way if you don't want to use the pedals you don't have a useless hole. Plus it's cleaner.

## Side stickers
You can find my original file here : http://qmk.fm/frenchdev/example_printable_stickers.svg

I used it when training but now I use blanks and the layout is different. 
I still uploaded it because I think it can be a good jumpstart for any temporary stickers on the 
side of keycaps.

## List of parts
- I2C mcp23018
- [teensy 2](https://www.pjrc.com/store/teensy.html)
- 3 LED, 5mm tall with flat head
- 3 330 ohm resistor
- 2 470 ohm resistor
- 2 TRRS connectors
- 1 [micro usb breakout board](http://www.ebay.com/itm/-/201387922085?)
- 88 cherry/gateron switchs
- 94 4148 diodes
- 34 R4 keys
- 14 R3 keys
- 20 R2 keys
- 22 R1 keys

If you fancy adding pedals :
[these are good enough and cheap](https://www.amazon.fr/gp/product/B00V7WITKI/ref=oh_aui_detailpage_o04_s00?ie=UTF8&psc=1). You also need a RCA connector for each of those to replace the included cable

If you (or your coworkers) find them too loud you can replace the switch inside them. 
For once we don't really care about what's inside :) 

## Various indications

The PHYSICAL rows and columns are connected as such :

on right hand (slave) :

              I2C mcp23018
           .-------   --------.
      GND -| 1 VSS \_/  NC 28 |
           | 2 NC       A7 27 |- C15
       R5 -| 3 B0       A6 26 |- C14
       R4 -| 4 B1       A5 25 |- C13
       R3 -| 5 B2       A4 24 |- C12
       R2 -| 6 B3       A3 23 |- C11
       R1 -| 7 B4       A2 22 |- C10
       R0 -| 8 B5       A1 21 |- C9
           | 9 B6       A0 20 |- C8
           | 10 B7    INTA 19 |
      VCC -| 11 VDD   INTB 18 |
      SCL -| 12 SCL     NC 17 |
      SDA -| 13 SDA    RST 16 |- VCC
           | 14 NC    ADDR 15 |- GND
           `------------------'

and on left hand (main) :

                  TEENSY
           .------------------.
           | GND          VCC |
       C7 -| B0            F0 |- R5
       C6 -| B1            F1 |- R4
       C5 -| B2            F4 |- R3
       C4 -| B3            F5 |- R2
     LEDC -| B7            F6 |- R1
      SCL -| D0            F7 |- R0
      SDA -| D1            B6 |- LEDB
       C3 -| D2            B5 |- LEDA
       C2 -| D3            B4 |
       C1 -| C6            D7 |
       C0 -| C7            D6 |- GND
           | D5            D4 |
           | VCC          RST |
           | E6           GND |
           `------------------'

We use pull up resistor for SCL and VDA, see https://github.com/ErgoDox-EZ/docs/blob/master/ErgoDox%20EZ%20Schematic.pdf for example

The connector is a standard TRRS (jack with audio + mic)

Diode direction is row to column

