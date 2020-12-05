## Space65 layout (with split space row -- no pun intended)

This layout is optimized for vim users on MacOS.
The split space row == least travel possible (I've found). Coming from an Alice this is the only way I can find myself going back to a non-ergonomic 6X% board

###### Settings:

* The `ALT` and `CMD` keys are swapped to replicate the Mac layout
* vim-style arrow key bindings H J K L in Fn layer

###### Flashing:

* v1 PCB: in order to toggle BootLoader from a factory PCB you must hold down ESC + Modifier MO(1) before you plug the board in
* otherwise you just hold ESC before you plug the board in
* Next, to make the .hex file and subsequently flash the board run:

```$ make gray_studio/space65:keithlo:flash # be in the qmk_firmware directory to do this ```
* more info at the bottom if you're getting errors 


### Qwerty
```
,------------------------------------------------------------------------------------------------.
| ESC |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |   BSPC    | DEL  |
|------------------------------------------------------------------------------------------------+
|  TAB  |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |    \    | INS  |
|------------------------------------------------------------------------------------------------+
|   CAPS  |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    | PGUP |
|------------------------------------------------------------------------------------------------+
|   Shift   |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  | ?/ |   Shift   |  Up  | PGDN |
|------------------------------------------------------------------------------------------------+
| Ctrl |  Alt  |  Cmd |    Space   |  Fn  |      Cmd     |  Alt |  Fn  |    | Left | Down |Right |
`----------------------------------------------------------------------'    '--------------------'
```

### Fn Layer
```
,------------------------------------------------------------------------------------------------.
|     |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | Vol- | Vol+ |  Mute   | Mute |
|------------------------------------------------------------------------------------------------+
|        |RGB T|RGB M| Hue-| Hue+| Sat-| Sat+| Val-| Val+|      |      |    |      |      |      |
|------------------------------------------------------------------------------------------------+
|         | RGBP | RGPG | RGPK |    |     | Left| Down| Up |Right|     |    |  Play/Pause |      |
|------------------------------------------------------------------------------------------------+
|           |     |     |     |     |     |     |     |    | Scr- | Scr+ |         | PgUp |      |
|------------------------------------------------------------------------------------------------+
|      |       |      |            |      |              |     |      |     | Home | PgDn |  End |
`---------------------------------------------------------------------'     '--------------------'


Fn Layer Mapping   chars -> RGB commands
|------------------------------------------------------------------------------------------------+
|        |RGB T|RGB M| Hue-| Hue+| Sat-| Sat+| Val-| Val+|      |     |     |      |      |      |
|------------------------------------------------------------------------------------------------+
|        |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |      |     |     |      |      |      |
|------------------------------------------------------------------------------------------------+

|------------------------------------------------------------------------------------------------+
|         | RGBP | RGPG | RGPK |    |     | Left| Down| Up |Right|     |    |  Play/Pause |      |
|------------------------------------------------------------------------------------------------+
|         |  A   |   S  |   D  |    |     |  H  |  J  | K  |  L  |     |    |    Enter    |      |
|------------------------------------------------------------------------------------------------+
```


###### Flashing (debugging)
* Make sure you are holding ESC + MO(1) when you plug board in
* Release ESC + MO(1) if you are stuck in the ```dfu-programmer: no device present.
ERROR: Bootloader not found. Trying again in 5s.``` loop seen below

* You should see a screen like this when you make and flash 
```
qmk_firmware git:(master)$ make gray_studio/space65:keithlo:flash
QMK Firmware 0.8.107
Making gray_studio/space65 with keymap keithlo and target flash

avr-gcc (GCC) 8.3.0
Copyright (C) 2018 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

Size before:
   text	   data	    bss	    dec	    hex	filename
      0	  21836	      0	  21836	   554c	.build/gray_studio_space65_keithlo.hex

Copying gray_studio_space65_keithlo.hex to qmk_firmware folder                                      [OK]
Checking file size of gray_studio_space65_keithlo.hex                                               [OK]
 * The firmware size is fine - 21836/28672 (76%, 6836 bytes free)
dfu-programmer: no device present.
ERROR: Bootloader not found. Trying again in 5s.
dfu-programmer: no device present.
ERROR: Bootloader not found. Trying again in 5s.
Bootloader Version: 0x00 (0)
Erasing flash...  Success
Checking memory from 0x0 to 0x6FFF...  Empty.
Checking memory from 0x0 to 0x557F...  Empty.
0%                            100%  Programming 0x5580 bytes...
[>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]  Success
0%                            100%  Reading 0x7000 bytes...
[>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]  Success
Validating...  Success
0x5580 bytes written into 0x7000 bytes memory (76.34%).
qmk_firmware git:(master)$
```


shoutout @billiams for the base ascii art template
