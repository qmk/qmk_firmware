TMK Keyboard Firmware Collection
================================
This is a keyboard firmware with some useful features for Atmel AVR controller.

Source code is available here: <http://github.com/tmk/tmk_keyboard>


Features
--------
These features can be used in your keyboard.

* Multi-layer Keymap  - Multiple keyboard layouts with layer switching
* Mouse key           - Mouse control with keyboard
* System Control Key  - Power Down, Sleep, Wake Up and USB Remote Wake up
* Media Control Key   - Volume Down/Up, Mute, Next/Prev track, Play, Stop and etc
* USB NKRO            - 120 keys(+ 8 modifiers) simultaneously
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


Projects
--------
You can find some keyboard specific projects under `converter` and `keyboard` directory.

### converter
* [ps2_usb](converter/ps2_usb/)             - [PS/2 keyboard to USB][GH_ps2]
* [adb_usb](converter/adb_usb/)             - [ADB keyboard to USB][GH_adb]
* [m0110_usb](converter/m0110_usb)          - [Macintosh 128K/512K/Plus keyboard to USB][GH_m0110]
* [terminal_usb](converter/terminal_usb/)   - [IBM Model M terminal keyboard(PS/2 scancode set3) to USB][GH_terminal]
* [news_usb](converter/news_usb/)           - [Sony NEWS keyboard to USB][GH_news]
* [x68k_usb](converter/x68k_usb/)           - [Sharp X68000 keyboard to USB][GH_x68k]
* [sun_usb](converter/sun_usb/)             - [Sun] to USB(type4, 5 and 3?)
* [pc98_usb](converter/pc98_usb/)           - [PC98] to USB
* [usb_usb](converter/usb_usb/)             - USB to USB(experimental)
* [ascii_usb](converter/ascii_usb/)         - ASCII(Serial console terminal) to USB
* [ibm4704_usb](converter/ibm4704_usb)      - [IBM 4704 keyboard Converter][GH_ibm4704]

### keyboard
* [hhkb](keyboard/hhkb/)                    - [Happy Hacking Keyboard pro][GH_hhkb] **my main board**
* [gh60](keyboard/gh60/)                    - [GH60] DIY 60% keyboard [prototype][GH60_proto] **my second board**
* [hbkb](keyboard/hbkb/)                    - [Happy Buckling spring keyboard][GH_hbkb](IBM Model M 60% mod)
* [hid_liber](keyboard/hid_liber/)          - [HID liberation][HID_liber] controller (by alaricljs)
* [phantom](keyboard/phantom/)              - [Phantom] keyboard (by Tranquilite)
* [IIgs_Standard](keyboard/IIgs/)           - Apple [IIGS] keyboard mod(by JeffreySung)
* [macway](keyboard/macway/)                - [Compact keyboard mod][GH_macway] [retired]
* [KMAC](keyboard/kmac/)                    - Korean custom keyboard
* [Lightsaber](keyboard/lightsaber/)        - Korean custom keyboard

[GH_macway]:    http://geekhack.org/showwiki.php?title=Island:11930
[GH_hhkb]:      http://geekhack.org/showwiki.php?title=Island:12047
[GH_ps2]:       http://geekhack.org/showwiki.php?title=Island:14618
[GH_adb]:       http://geekhack.org/showwiki.php?title=Island:14290
[GH_hhkb_bt]:   http://geekhack.org/showwiki.php?title=Island:20851
[GH_m0110]:     http://geekhack.org/showwiki.php?title=Island:24965
[GH_news]:      http://geekhack.org/showwiki.php?title=Island:25759
[GH_terminal]:  http://geekhack.org/showwiki.php?title=Island:27272
[GH_x68k]:      http://geekhack.org/showwiki.php?title=Island:29060
[GH_hbkb]:      http://geekhack.org/showwiki.php?title=Island:29483
[GH_ibm4704]:   http://geekhack.org/index.php?topic=54706.0
[HID_liber]:    http://deskthority.net/wiki/HID_Liberation_Device_-_DIY_Instructions
[Phantom]:      http://geekhack.org/index.php?topic=26742
[GH60]:         http://geekhack.org/index.php?topic=34959
[GH60_proto]:   http://geekhack.org/index.php?topic=37570.0
[PC98]:         http://en.wikipedia.org/wiki/NEC_PC-9801
[Sun]:          http://en.wikipedia.org/wiki/Sun-3
[IIGS]:         http://en.wikipedia.org/wiki/Apple_IIGS



License
-------
**GPLv2** or later. Some protocol files are under **Modified BSD License**.
LUFA, PJRC and V-USB stack have their own license respectively.



Build Firmware and Program Controller
-------------------------------------
See [doc/build.md](doc/build.md).



Change your keymap
------------------
See [doc/keymap.md](doc/keymap.md).



Magic Commands
--------------
To see help press `Magic` + `H`.

 `Magic` key bind may be `LShift` + `RShift` in many project, but `Power` key on ADB converter. `Magic` keybind can be vary on each project, check `config.h` in project directory.

Following commands can be also executed with `Magic` + key. In console mode `Magic` keybind is not needed.

    ----- Command Help -----
    c:      enter console mode
    d:      toggle debug enable
    x:      toggle matrix debug
    k:      toggle keyboard debug
    m:      toggle mouse debug
    v:      print device version & info
    t:      print timer count
    s:      print status
    e:	    print eeprom config
    n:	    toggle NKRO
    0/F10:  switch to Layer0
    1/F1:   switch to Layer1
    2/F2:   switch to Layer2
    3/F3:   switch to Layer3
    4/F4:   switch to Layer4
    PScr:   power down/remote wake-up
    Caps:   Lock Keyboard(Child Proof)
    Paus:   jump to bootloader

**TBD**

### Boot Magic Configuration - Virtual DIP Switch
Boot Magic are executed during boot up time. Press Magic key below then plug in keyboard cable.
Note that you must use keys of **Layer 0** as Magic keys. These settings are stored in EEPROM so that retain your configure over power cycles.

To avoid configuring accidentally additive salt key `KC_SPACE` also needs to be pressed along with the following configuration keys. The salt key is configurable in `config.h`. See [common/bootmagic.h](common/bootmagic.h).

#### General
- Skip reading EEPROM to start with default configuration(`ESC`)
- Clear configuration stored in EEPROM to reset configuration(`Backspace`)

#### Bootloader
- Kick up Bootloader(`B`)

#### Debug
- Debug enable(`D`)
- Debug matrix enable(`D`+`X`)
- Debug keyboard enable(`D`+`K`)
- Debug mouse enable(`D`+`M`)

#### Keymap
- Swap Control and CapsLock(`Left Control`)
- Change CapsLock to Control(`Caps Lock`)
- Swap LeftAlt and Gui(`Left Alt`)
- Swap RightAlt and Gui(`Right Alt`)
- Disable Gui(`Left Gui`)
- Swap Grave and Escape(`Grave`)
- Swap BackSlash and BackSpace(`Back Slash`)

#### Default Layer
- Set Default Layer to 0(`0`)
- Set Default Layer to 1(`1`)
- Set Default Layer to 2(`2`)
- Set Default Layer to 3(`3`)
- Set Default Layer to 4(`4`)
- Set Default Layer to 5(`5`)
- Set Default Layer to 6(`6`)
- Set Default Layer to 7(`7`)

#### Caution
Unintentional use of this feature will cause user confusion.

TODO: Magic key combination to avoid unintentional press during plug in

**TBD**


Mechanical Locking support
--------------------------
This feature makes it possible for you to use mechanical switch for `CapsLock`, `NumLock` or `ScrollLock`. To enable this feature define these macros in `config.h` and use `KC_LCAP`, `KC_LNUM` or `KC_LSCR` in keymap for locking key instead of normal `KC_CAPS`, `KC_NLCK` or `KC_SLCK`. Resync option tries to keep lock switch state consistent with keyboard LED state.
 
    #define LOCKING_SUPPORT_ENABLE
    #define LOCKING_RESYNC_ENABLE


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
* keyboard/     - keyboard projects
* converter/    - protocol converter projects
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



Other Keyboard Firmware Projects
------------------
See [doc/other_projects.md](doc/other_projects.md).
