t.m.k. Keyboard Firmware Collection
====================================
This is a keyboard firmware with some features for Atmel AVR controller.

Source code is available here: <http://github.com/tmk/tmk_keyboard>


Features
--------
* Mouse key - Mouse control by keyboard
* System Control Key - Power Down, Sleep, Wake Up and USB Remote Wake up
* Media Control Key - Volume Down/Up, Mute, Next/Prev track, Play, Stop and etc. 
* USB NKRO - Can send 120 keys(+ 8 modifiers) simultaneously.
* PS/2 mouse support - integrate PS/2 mouse(TrackPoint) into keyboard as composite device.


Projects
--------
### converter
* ps2_usb - PS/2 keyboard to USB
* adb_usb - ADB keyboard to USB
* m0110_usb - Machintosh 128K/512K/Plus keyboard to USB
* terminal_usb - IBM Model M terminal keyboard(PS/2 scancode set3) to USB
* sony_usb - Sony NEWS keyboard to USB
* x68k_usb - Sharp X68000 keyboard to USB

### keyboard
* hhkb - Happy Hacking Keyboard professional
* macway - Compact keyboard mod
* hbk - Happy Buckling sprint keyboard(IBM Model M mod)

[GH_macway]:    http://geekhack.org/showwiki.php?title=Island:11930
[GH_hhkb]:      http://geekhack.org/showwiki.php?title=Island:12047
[GH_ps2]:       http://geekhack.org/showwiki.php?title=Island:14618
[GH_adb]:       http://geekhack.org/showwiki.php?title=Island:14290
[GH_hhkb_bt]:   http://geekhack.org/showwiki.php?title=Island:20851
[GH_m0110]:     http://geekhack.org/showwiki.php?title=Island:24965
[GH_sony]:      http://geekhack.org/showwiki.php?title=Island:25759
[GH_terminal]:  http://geekhack.org/showwiki.php?title=Island:27272
[GH_x68k]:      http://geekhack.org/showwiki.php?title=Island:29060
[GH_hbk]:       http://geekhack.org/showwiki.php?title=Island:29483



Files & Directories
-------------------
### Top
* common/       common codes
* protocol/     keyboard protocol support
* keyboard/     keyboard projects
* converter/    protocol converter projects
* doc/          documents

### Keyboard Protocols
* pjrc/         PJRC USB stack
* vusb/         Objective Development V-USB
* iwrap/        Bluetooth HID for Bluegiga iWRAP
* ps2           PS/2 protocol
* adb           Apple Desktop Bus protocol
* m0110         Macintosh 128K/512K/Plus keyboard protocol
* news          Sony NEWS keyboard protocol
* x68k          Sharp X68000 keyboard protocol


Build & Program
---------------
### Build firmware
To compile you need `AVR GCC`, `AVR Libc` and `GNU make`.
You can use [WinAVR][1] on Windows and [CrossPack][2] on Mac.

    $ cd <project>
    $ make

The firmware will be compiled as a file tmk_<project>.hex.

[1]:  http://winavr.sourceforge.net/
[2]: http://www.obdev.at/products/crosspack/index.html

### Program Controller
If you have proper program command in Makefile just type this.

    $ make program

As for `Teensy` you can use `PJRC's loader` to program hex file. <http://www.pjrc.com/teensy/loader.html>



Build Options
-------------
### `Makefile`
#### 1. MCU and Frequency.
    MCU = atmega32u4       # Teensy 2.0
    #MCU = at90usb1286      # Teensy++ 2.0
    F_CPU = 16000000

#### 2. Features
Note that ***comment out*** to disable them.
    MOUSEKEY_ENABLE = yes	# Mouse keys
    PS2_MOUSE_ENABLE = yes	# PS/2 mouse(TrackPoint) support
    EXTRAKEY_ENABLE = yes	# Enhanced feature for Windows(Audio control and System control)
    NKRO_ENABLE = yes		# USB Nkey Rollover

#### 3. Programmer
Set proper command for your controller, bootloader and programmer.
    # for PJRC Teensy
    PROGRAM_CMD = teensy_loader_cli -mmcu=$(MCU) -w -v $(TARGET).hex

    # for Atmel AT90USBKEY
    PROGRAM_CMD = dfu-programmer $(MCU) flash $(TARGET).hex

    # avrdude
    PROGRAM_CMD = avrdude -p $(MCU) -c avrispmkII -P USB -U flash:w:$(TARGET).hex
    PROGRAM_CMD = avrdude -p $(MCU) -c usbasp -U flash:w:$(TARGET).hex
    PROGRAM_CMD = avrdude -p $(MCU) -c arduino -P COM1 -b 57600 -U flash:w:$(TARGET).hex

### `config.h`
#### 1. USB vendor/product ID and device description
    #define VENDOR_ID       0xFEED
    #define PRODUCT_ID      0xBEEF
    /* device description */
    #define MANUFACTURER    t.m.k.
    #define PRODUCT         Macway mod
    #define DESCRIPTION     t.m.k. keyboard firmware for Macway mod

#### 2. Keyboard matrix configuration
    #define MATRIX_ROWS 8
    #define MATRIX_COLS 8
    #define MATRIX_HAS_GHOST

### 3. Mouse keys configuration

### 4. PS/2 mouse configuration


Keymap
------


Build your own firmware
-----------------------


Debuging
--------
Use PJRC's `hid_listen` to see debug messages and press `<COMMAND> + H` to debug menu. 
See `config.h` for definition of `<COMMAND>` key combination.


Other Keyboard Projects
-----------------------
### PJRC USB Keyboard/Mouse Example
- <http://www.pjrc.com/teensy/usb_keyboard.html>
- <http://www.pjrc.com/teensy/usb_mouse.html>

### kbupgrade
- <http://github.com/rhomann/kbupgrade>
- <http://geekhack.org/showwiki.php?title=Island:8406>

### c64key
- <http://symlink.dk/projects/c64key/>

### rump
- <http://mg8.org/rump/>
- <http://github.com/clee/rump>

### dulcimer
- <http://www.schatenseite.de/dulcimer.html>

### humblehacker-keyboard
- <http://github.com/humblehacker>
- <http://www.humblehacker.com/keyboard/>
- <http://geekhack.org/showwiki.php?title=Island:6292>

### ps2avr
- <http://sourceforge.net/projects/ps2avr/>
