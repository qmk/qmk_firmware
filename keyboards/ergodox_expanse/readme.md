# ErgoDox Expanse

The ErgoDox Expanse is a DIY hand-wired version of the EdgoDox Infinity using the Teensy 3.2 board as the controller. The display used is a 128x64 OLED display with the SSD1306 controller instead of the Infinty LCD. RGB backlight support is planned but not yet tested.

The only keymap tested is the 'ballanux' one, intended for spanish layout, but any other ergodox keymap should work.

## Wiring instructions

This is the cabling that matches the configuration on the software. For easy wiring different color cables can be used. All the required cables can be obtained by scraping an old parallel port printer cable. Both sides of the keyboard are wired in the same way.

The wiring for master/slave communication between both sides is at the bottom table. Only the master side should be connected to the computer. To avoid supply issues between both sides it is recommended to put a diode between the 5V from the master and the 5V to the slave. An old USB cable could be cut and used for this purpose. It doesn't need to be shielded so a thin one can be used. The diode can be a 1N4148 or similar.

The current prototype doesn't have RGB backlighting, but it can be wired if desired as shown in Table 3. For this it is required to use a 'Neopixel led strip' (SK6812RGB) or similar and configure the software acordingly.


### Table 1. Key matrix wiring:

Matrix|uC Port|Teensy|Color
------|-------|------|-----
Col. 1|PTB2|PIN 19|Grey
Col. 2|PTB3|PIN 18|Brown
Col. 3|PTB18|PIN 32|White
Col. 4|PTB19|PIN 25|Blue
Col. 5|PTC0|PIN 15|Pink
Col. 6|PTC9|PIN 27|Green
Col. 7|PTC10|PIN 29|Purple
Col. 8|PTC11|PIN 30|Yellow
Col. 9|PTD0|PIN  2|Orange
Row. 1|PTD1|PIN 14|Brown/White
Row. 3|PTD5|PIN 20|Purple/White
Row. 2|PTD4|PIN  6|Black/White
Row. 4|PTD6|PIN 21|Yellow/Black
Row. 5|PTD7|PIN  2|Blue/White

Left side columns wiring:
![Left side columns wiring](https://i.imgur.com/J3Z6nuV.jpg)

Right side rows and columns wiring:
![Right side rows and columns wiring](https://i.imgur.com/VzcTDnk.jpg)

Wiring to the Teensy controller:
![Wiring to the Teensy controller](https://i.imgur.com/gfvivOr.jpg)

Teensy detail:
![Teensy detail](https://i.imgur.com/jIaTpQs.jpg)


### Table 2. OLED display wiring:

SD1306|uC Port|Teensy|Color
------|-------|------|-----
CS|PTC4|PIN 10|Grey/Black
RST|PTC8|PIN 28|Green/Black
D/C|PTC7|PIN 12|Pink/Black
SCK|PTC5|PIN 13|Blue/Black
MOSI|PTC6|PIN 11|Light blue

OLED wiring:
![OLED wiring](https://i.imgur.com/tWrabMi.jpg)

OLED detail:
![OLED detail](https://i.imgur.com/bqqstJm.jpg)

### Table 3. RGB backlighting

SD1306|uC Port|Teensy|Color
------|-------|------|-----
+5V|---|Vin|Red
DIN|PTB18|PIN17
GND|GND|GND|Black


### Connection diagram from master to the slave:
```
                     1N4148
		+5V Master ---|>|---- +5V Slave 
		TX0 ----------------------- RX1
		RX0 ----------------------- TX1
		GND ----------------------- GND
```

### Table 4. Master/Slave wiring:

M.Signal|M.Port|M.Teensy|Color|S.Signal|S.Port|S.Teensy
--------|------|--------|-----|--------|------|--------
+5V|---|Vin|1N4148|+5V|---|Vin
TX0|PTB17|PIN 1|Green|RX1|PTE1|PIN 26
RX0|PTB16|PIN 0|Blue|TX1|PTE0|PIN 31
GND|GND|GND|Black	GND|GND|GND

Master/Slave connection working:
![Master/Slave connection](https://i.imgur.com/h3It6Bm.jpg)

## Building and flashing


The Expanse is two completely independent keyboards, and needs to be flashed
for the left and right halves seperately.

Instead of using the Infinity bootloader we wil be using the Teensy Loader that can be found at:

https://www.pjrc.com/teensy/loader_cli.html


To flash them:

  - Make sure you are in the top-level qmk_firmware directory
  - Build the firmware with `make ergodox_expanse:keymapname`
  - Go to the build directory `cd .build`
  - Copy the teensy_loader_cli in this folder.
  - Plug in the left hand keyboard only.
  - Install the firmware with `teensy_loader_cli -mmcu=mk20dx256 -w ergodox_expanse_ballanux.hex`
  - Press the reset button on the Teensy 3.2 board; it will flash in a few seconds.
  - Go to the top-level qmk_firmware directory `cd ..`
  - Build right hand firmware with `make ergodox_expanse:keymapname MASTER=right`
  - Plug in the right hand keyboard only.
  - Go to the build directory `cd .build`
  - Install the firmware with `teensy_loader_cli -mmcu=mk20dx256 -w ergodox_expanse_ballanux.hex`
  - Press the reset button on the Teensy 3.2 board; it will flash in a few seconds.

More information on the Infinity firmware is available in the [TMK/chibios for
Input Club Infinity Ergodox](https://github.com/fredizzimo/infinity_ergodox/blob/master/README.md)

## Expanse Master/Two Halves

The Expanse is two completely independent keyboards, that can connect together.
You have a few options in how you flash the firmware:

- Flash the left half, rebuild the firmware with "MASTER=right" and then flash
  the right half.  This allows you to plug in either half directly to the
  computer and is what the above instructions do.

- Flash the left half, then flash the same firmware on the right.  This only
  works when the left half is plugged directly to the computer and the keymap
  is mirrored.  It saves the small extra step of rebuilding with
  "MASTER=right".

- The same as the previous one but with "MASTER=right" when you build the
  firmware, then flash the same firmware to both halves.  You just have to
  directly connect the right half to the computer.

- For minor changes such as changing only the keymap without having updated
  any part of the firmware code itself, you can program only the MASTER half.

- It is safest to program both halves though.
~

