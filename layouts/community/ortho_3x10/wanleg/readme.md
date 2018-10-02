![Gherkin Wanleg Layout Image](https://i.imgur.com/nCPog2W.png)  
# Gherkin Wanleg Layout
This is the layout I came up with to preserve a standard QWERTY 104 key ANSI layout as much as possible, in as few layers as possible for a 30 key board.  
Here are the two Tap Dance keys I've set up for this board:

Legend Name | Single Tap | Double Tap | Hold  
--- | --- | --- | ---  
Sft//Cp | shift | caps lock | *null*
Q//Esc | KC_Q | escape | *null*

# Gherkin Flashing
## Windows
1. The standard Gherkin uses a ProMicro (or clone) microcontroller, which has the Caterina bootloader by default.
2. If you have never flashed your ProMicro with QMK before, you will need to short the RST pin to GND to put it into bootloader mode (you only have 7 seconds to flash once it enters bootloader mode). You may need to touch the RST pin to GND **TWICE** in quick succession if it doesn't flash with just one touch.  
3. Once connected to your computer, you should be able to flash using  
`make gherkin:wanleg:avrdude`  
4. Once you've been able to successfully flash the ProMicro, you should be able to use the `RESET` key for future flashes instead of shorting the RST pin.

## Linux  
### First Flash with QMK  
The built-in `:avrdude` QMK target in Linux doesn't work with the default Caterina bootloader on the ProMicro, so we have to use avrdude separately. The instructions below are adapted from https://deskthority.net/workshop-f7/how-to-use-a-pro-micro-as-a-cheap-controller-converter-like-soarer-s-t8448.html

1. To flash the device, you need to have AVRdude installed. You can do this via your distro's package manager (or compile from source if needed).
2. Once avrdude has been installed, open a terminal and run
`ls /dev/tty*`
3. Next, plug in your device and re-run `ls /dev/tty*`
There should be one more device than was seen previously. Make a note of it. For me, it's `/dev/ttyACM0`.
4. Navigate to the directory with your `.hex` file in it. Touch the RST pin to GND **TWICE** in quick succession, then run the following within 7 seconds:  
`sudo avrdude -p m32u4 -P YOUR_SERIAL_PORT -c avr109 -U flash:w:YOUR_FILENAME.hex`  
Replace YOUR_SERIAL_PORT with your serial port's device name, and YOUR_FILENAME.hex with the appropriate filename. For me, it looks like this:  
`sudo avrdude -p m32u4 -P /dev/ttyACM0 -c avr109 -U flash:w:gherkin_wanleg.hex`  
If you miss the 7 second window, the ProMicro will leave bootloader mode and the flash will fail. Hit `Control` + `C` to exit the `avrdude` command, connect RST to GND twice quickly, and try the `avrdude` command again.

### Subsequent Flashes with QMK
1. Re-flashing is similar to the initial flash procedure. Plug in your keyboard, open a terminal and run
`ls /dev/tty*`
2. Next, hit the `RESET` key on your keyboard and re-run the `ls /dev/tty*` command to find your keyboard's serial port.  
3. Flash your keyboard with the avrdude command you used for the initial flash within 7 seconds after hitting `RESET`.

# ProMicro Bootloader Replacement (Caterina to QMK DFU)
If you have an Arduino (or clone), you can replace the bootloader for a few extra features (e.g. no more 7 second "flash window", simplified Linux flashing, blinking LED when the ProMicro is in bootloader mode, ability to exit bootloader mode without unplugging your keyboard, among others).
The instructions below have been adapted from https://www.reddit.com/r/olkb/comments/8sxgzb/replace_pro_micro_bootloader_with_qmk_dfu/)
## Arduino Setup
1. Upload the ArduinoISP sketch onto your Arduino board (https://www.arduino.cc/en/Tutorial/ArduinoISP).
2. Wire the Arduino to the ProMicro

| Arduino | ProMicro |
| --- | --- |
| 10 | RST |
| 11 | 16 |
| 12 | 14 |
| 13 | 15 |
| GND | GND |
| 5V | VCC |

## Make the QMK DFU .hex
3. In `config.h` add the following. This is already set up in `qmk_firmware/layouts/community/ortho_3x10/wanleg`. You only need to do this on other keymaps.
```
#define QMK_ESC_OUTPUT B4
#define QMK_ESC_INPUT F7
#define QMK_LED B0
```
The `QMK_ESC_` lines define where the bootloader escape key is. Refer to the `MATRIX_ROW_PINS` and `MATRIX_COL_PINS` lines in your keyboard's `config.h` to choose your preferred key.  
You hit the bootloader escape key to exit bootloader mode after you've hit the RESET key to enter bootloader mode (e.g. if you change your mind and don't want to flash just then).  
On a Gherkin, B4/F7 corresponds to the top-left corner key.  
`B0` is an indicator light on one of the ProMicro's onboard LEDs. With QMK DFU, it will flash to indicate the ProMicro is in bootloader mode.  
You can add `#define QMK_SPEAKER C6` if you have a speaker hooked up to pin C6. The Gherkin PCB already uses pin C6 in its switch layout, so you cannot use a speaker on a standard Gherkin.  
4. Also, you should add `BOOTLOADER = qmk-dfu` to your `rules.mk` file, so it is flagged properly. Again, this is already set up in `qmk_firmware/layouts/community/ortho_3x10/wanleg`.  
5. Once you've made the required edits, it's time to compile the firmware. If you use the `:production` target when compiling, it will produce the usual `.hex` file as well as `_bootloader.hex` and `_production.hex` files. The `_production.hex` will be what we want. This contains the bootloader and the firmware, so we only have to flash once (rather than flash the bootloader, and THEN flash the firmware).
For example  
`make <keyboard>:<keymap>:production`  

## Burn QMK DFU
6. Navigate to the directory with your `_production.hex` file, and burn it with the following command  
`avrdude -b 19200 -c avrisp -p m32u4 -v -e -U lock:w:0x3F:m -U efuse:w:0xC3:m -U hfuse:w:0xD9:m -U lfuse:w:0x5E:m -U YOUR_production.hex -P comPORT`  
Change `comPORT` to whatever port is used by the Arduino (e.g. `com11` in Windows or `/dev/ttyACM0` in Linux). Use Device Manager in Windows to find the port being used. Use `ls /dev/tty*` in Linux. Change `YOUR_production.hex` to whatever you've created in the previous step.

## Using QMK DFU
7. Once QMK DFU is burned to your ProMicro, you can then flash subsequent hex files with
`make gherkin:<keymap>:dfu`  
