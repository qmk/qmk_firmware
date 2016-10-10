TMK Keyboard Firmware Core Library
==================================
This is a keyboard firmware library with some useful features for Atmel AVR and Cortex-M.

Source code is available here: <https://github.com/tmk/tmk_keyboard/tree/core>


Updates
-------
#### 2016/02/10
flabbergast's Chibios protocol was merged from <https://github.com/flabbergast/tmk_keyboard/tree/chibios>. See [protocol/chibios/README.md](protocol/chibios/README.md). Chibios protocol supports Cortex-M such as STM32 and Kinetis.

#### 2015/04/22
separated with TMK Keyboard Firmware Collection



Features
--------
These features can be used in your keyboard.

* Multi-layer Keymap  - Multiple keyboard layouts with layer switching
* Mouse key           - Mouse control with keyboard
* System Control Key  - Power Down, Sleep, Wake Up and USB Remote Wake up
* Media Control Key   - Volume Down/Up, Mute, Next/Prev track, Play, Stop and etc
* USB NKRO            - 248 keys(+ 8 modifiers) simultaneously
* PS/2 mouse support  - PS/2 mouse(TrackPoint) as composite device
* Keyboard protocols  - PS/2, ADB, M0110, Sun and other old keyboard protocols
* User Function       - Customizable function of key with writing code
* Macro               - Very primitive at this time
* Keyboard Tricks     - Oneshot modifier and modifier with tapping feature
* Debug Console       - Messages for debug and interaction with firmware
* Virtual DIP Switch  - Configurations stored EEPROM(Boot Magic)
* Locking CapsLock    - Mechanical switch support for CapsLock
* Breathing Sleep LED - Sleep indicator with charm during USB suspend
* Backlight           - Control backlight levels



TMK Keyboard Firmware Collection
--------------------------------
Complete firmwares for various keyboards and protocol converters.

<https://github.com/tmk/tmk_keyboard>



License
-------
**GPLv2** or later. Some protocol files are under **Modified BSD License**.
LUFA, PJRC and V-USB stack have their own license respectively.



Build Firmware and Program Controller
-------------------------------------
See [doc/build.md](doc/build.md).



Start Your Own Project
-----------------------
**TBD**
### Config.h Options
#### 1. USB vendor/product ID and device description
    #define VENDOR_ID       0xFEED
    #define PRODUCT_ID      0xBEEF
    #define MANUFACTURER    t.m.k.
    #define PRODUCT         Macway mod
    #define DESCRIPTION     t.m.k. keyboard firmware for Macway mod

#### 2. Keyboard matrix configuration
    #define MATRIX_ROWS 8
    #define MATRIX_COLS 8
    #define MATRIX_HAS_GHOST



Architecture
------------
    Architecture Diagram
                               +---------------+---------------+-------------+
                               |    Host       |   Keyboard    | Matrix, LED |
       ___________             |-----------+-+ +-------------+ | +-----------|
      /          /| Keys/Mouse | Protocol  |d| | Action      | | | Protocol  |
     /__________/ |<-----------|  LUFA     |r| |  Layer, Tap | | |  Matrix   |
     |.--------.| |   LED      |  V-USB    |i| |-------------| | |  PS/2,IBM |             __________________
     ||        || |----------->|  PJRC     |v| | Keymap      | | |  ADB,M0110|  Keys      / /_/_/_/_/_/_/_/ /|
     ||  Host  || |  Console   |  iWRAP(BT)|e| | Mousekey    | | |  SUN/NEWS |<----------/ /_/_/_/_/_/_/_/ / /
     ||________||/.<-----------|  UART     |r| | Report      | | |  X68K/PC98| Control  / /_/_/_/_/_/_/_/ / /
     `_========_'/|            |---------------------------------------------|-------->/___ /_______/ ___/ /
     |_o______o_|/             | Sendchar, Print, Debug, Command, ...        |         |_________________|/
                               +---------------------------------------------+              Keyboard



Debugging
--------
Use PJRC's `hid_listen` to see debug messages. You can use the tool for debug even if firmware use LUFA stack.

You can use xprintf() to display debug info on `hid_listen`, see `common/xprintf.h`.



Files and Directories
-------------------
### Top
* common/       - common codes
* protocol/     - keyboard protocol support
* doc/          - documents
* common.mk     - Makefile for common
* protocol.mk    - Makefile for protocol
* rules.mk      - Makefile for build rules

### Common
* host.h
* host_driver.h
* keyboard.h
* command.h
* keymap.h
* action.h
* keycode.h
* matrix.h
* led.h
* mousekey.h
* report.h
* debug.h
* print.h
* bootloader.h
* sendchar.h
* timer.h
* util.h

### Keyboard Protocols
* lufa/     - LUFA USB stack
* pjrc/     - PJRC USB stack
* vusb/     - Objective Development V-USB
* iwrap/    - Bluetooth HID for Bluegiga iWRAP
* ps2.c     - PS/2 protocol
* adb.c     - Apple Desktop Bus protocol
* m0110.c   - Macintosh 128K/512K/Plus keyboard protocol
* news.c    - Sony NEWS keyboard protocol
* x68k.c    - Sharp X68000 keyboard protocol
* serial_soft.c - Asynchronous Serial protocol implemented by software



Coding Style
-------------
- Doesn't use Tab to indent, use 4-spaces instead.
