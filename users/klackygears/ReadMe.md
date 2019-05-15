Copyright <2019> <James Smith> @<klackygears>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.




#<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>#
`---------------------------------------------------------------------------`
Flash dfu bootloader on pro micro with arduino uno using adruino as ISP.
`---------------------------------------------------------------------------`
#<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>#


`---------------------------------------------------------------------------`
#I am NOT an expert at this. I don't know much more than what I have here.#
*I created this documentation mostly so I wouldn't forget!*
#If you use this and break something, I am not responsible!#
`---------------------------------------------------------------------------`


I progressed through the following steps and used information from the following sources cited to help with this.


`---------------------------------------------------------------------------`
#1) Use Arduino IDE to load "Arduino as ISP" sketch to Uno.
`---------------------------------------------------------------------------`
File> Examples> ArduinoISP >ArduinoISP
Upload the Sketch and the Uno should be ready.


`---------------------------------------------------------------------------`
#2) Wiring Uno to Pro Micro (Leonardo clone)
`---------------------------------------------------------------------------`
https://schou.dk/linux/arduino/isp/

  Name    UNO     Pro Micro
  Power	  5V------VCC
  Ground  GND-----GND
  SCK	  13------15
  MISO	  12------14
  MOSI	  11------16
  Reset	  10------RST

`You can also use this guide to reflash the Caterina bootloader if you mess up. (I certainly did!)`


`---------------------------------------------------------------------------`
#3) Add capacitor to Uno between reset and ground
`---------------------------------------------------------------------------`
https://forum.arduino.cc/index.php?topic=431723.0
"Put a 10uf capacitor (or really anything over 1uF) between reset and ground on Uno after uploading arduino as ISP. Remove it before uploading another sketch to the Uno afterwards."
I used a 0.1uF because it's what I had on hand and it worked fine.


`---------------------------------------------------------------------------`
#4) Creating the hex for flashing the dfu bootloader and keymap at the same time
`---------------------------------------------------------------------------`
https://www.reddit.com/r/olkb/comments/8sxgzb/replace_pro_micro_bootloader_with_qmk_dfu/

   "First thing you want to do is configure your keymap's config.h to include the following info:
      
   #define QMK_ESC_OUTPUT F1 // usually COL
   #define QMK_ESC_INPUT D5 // usually ROW
   #define QMK_LED B0
   #define QMK_SPEAKER C6
      
   Check your keyboard's config.h file for the column and row PINs. I would recommend choosing the key that you use for ESC as the key you use the escape key.
   B0 is one of the two LEDs on the Pro Micro itself. It will flash as an indicator light. And since it's already there, no reason NOT to use it.
   If you have a speaker, then use the pin for that, so you get nice audio feedback on the status.
   Also, you may want to add `BOOTLOADER = qmk-dfu` to your rules.mk file, so it handles some of the "extra" stuff properly.
   Once you've done that, it's time to compile the firmware. If you use the `:production` target, this will compile a normal hex file, as well as _bootloader and _production hex
   files. The _production hex will be what we want. This contains the bootloader and the firmware,
   so we only have to flash once. (rather than flash the bootloader, and THEN flash the firmware)."

Thanks drashna For this helpful guide! `Read through this carefully, it's helpful on the next steps also.`


`---------------------------------------------------------------------------`
#5) Writing terminal command and setting options correctly for avrdude (-c -p -P -b -U)
`---------------------------------------------------------------------------`
https://www.nongnu.org/avrdude/user-manual/avrdude_4.html#Option-Descriptions
Gives a detailed explanation of what these options represent. I also Googled a lot to make sure mine were correct. I used Arduino IDE and `ls /dev/tty.*` to find the correct port (-P).

https://www.reddit.com/r/olkb/comments/9ctx37/qmk_burn_dfu_bootloader_into_keyboard_with/
Has an example of the command for Windows and helps as a general guide.
Thanks GAMELASTER!

My command is below step 6 and includes the EEPROM option drashna's guide used.


`---------------------------------------------------------------------------`
#6) General info and flashing EEPROM
`---------------------------------------------------------------------------`
https://github.com/qmk/qmk_firmware/blob/master/keyboards/lets_split/readme.md
This wipes the EEPROM and you'll need to reload it. drashna's guide gives the command to flash it at the same time. Otherwise the above guide is what you'll want.

https://beta.docs.qmk.fm/for-makers-and-modders/isp_flashing_guide
ISP Flashing Guide



`---------------------------------------------------------------------------`
#Command I used in Terminal (Mac OS) from qmk_firmware directory (cd qmk_firmware)

avrdude -c stk500v1 -p m32u4 -P /dev/cu.usbmodem14201 -b 19200 -U flash:w:"helix_rev2_klackygears_production.hex":a -U lfuse:w:0x5E:m -U hfuse:w:0xD9:m -U efuse:w:0xC3:m -U lock:w:0x3F:m -U eeprom:w:"eeprom-righthand.eep":a

`---------------------------------------------------------------------------`
#Command for non split example
avrdude -c stk500v1 -p m32u4 -P /dev/cu.usbmodem14201 -b 19200 -U flash:w:"c39_klackygears_production.hex":a -U lfuse:w:0x5E:m -U hfuse:w:0xD9:m -U efuse:w:0xC3:m -U lock:w:0x3F:m



`---------------------------------------------------------------------------`
*Once again*
#I am NOT an expert at this. I don't know much more than what I have here.#
*I created this documentation mostly so I wouldn't forget!*
*If you use this and break something, I am not responsible!*
*Use at your own risk.*
#Best of luck with your experiments!#
`---------------------------------------------------------------------------`

`20190515`
