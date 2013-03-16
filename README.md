t.m.k. Keyboard Firmware Collection
====================================
This is a keyboard firmware with some features for Atmel AVR controller.

Source code is available here: <http://github.com/tmk/tmk_keyboard>


Features
--------
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


Projects
--------
You can find some keyboard specific projects under `converter` and `keyboard` directory.

### converter
* [ps2_usb](converter/ps2_usb/)             - [PS/2 keyboard to USB][GH_ps2]
* [adb_usb](converter/adb_usb/)             - [ADB keyboard to USB][GH_adb]
* [m0110_usb](converter/m0110_usb)          - [Machintosh 128K/512K/Plus keyboard to USB][GH_m0110]
* [terminal_usb](converter/terminal_usb/)   - [IBM Model M terminal keyboard(PS/2 scancode set3) to USB][GH_terminal]
* [news_usb](converter/news_usb/)           - [Sony NEWS keyboard to USB][GH_news]
* [x68k_usb](converter/x68k_usb/)           - [Sharp X68000 keyboard to USB][GH_x68k]
* [sun_usb](converter/sun_usb/)             - [Sun] to USB(type4, 5 and 3?)
* [pc98_usb](converter/pc98_usb/)           - [PC98] to USB
* [usb_usb](converter/usb_usb/)             - USB to USB(experimental)

### keyboard
* [hhkb](keyboard/hhkb/)                    - [Happy Hacking Keyboard professional][GH_hhkb]
* [macway](keyboard/macway/)                - [Compact keyboard mod][GH_macway]
* [hbkb](keyboard/hbkb/)                    - [Happy Buckling sprint keyboard(IBM Model M mod)][GH_hbkb]
* [IIgs_Standard](keyboard/IIgs/)           - Apple [IIGS] keyboard mod(by JeffreySung)
* [hid_liber](keyboard/hid_liber/)          - [HID liberation controller][HID_liber](by alaricljs)
* [phantom](keyboard/phantom/)              - [Phantom keyboard][PHANTOM] (by Tranquilite)
* [gh60](keyboard/gh60/)                    - [GH60 keyboard][GH60]

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
[HID_liber]:    http://deskthority.net/wiki/HID_Liberation_Device_-_DIY_Instructions
[PHANTOM]:      http://geekhack.org/index.php?topic=26742
[GH60]:         http://geekhack.org/index.php?topic=34959
[PC98]:         http://en.wikipedia.org/wiki/NEC_PC-9801
[Sun]:          http://en.wikipedia.org/wiki/Sun-3
[IIGS]:         http://en.wikipedia.org/wiki/Apple_IIGS



Build & Program
---------------
### Install Tools
First, you need tools to build firmware and program your controller. I assume you are on Windows here.

1. Install [WinAVR][winavr]. This is old but works well for this purpose. `WinAVR` is a tool set to build firmware including C compiler(gcc) and make commands. You can use [CrossPack][crosspack] instead if you are on Mac.

2. Install [Atmel FLIP][flip]. `FLIP` is a tool to program(load) firmware into AVR controller(ATMega32u4) via DFU bootloader. ATMega32u4 has DFU bootloader by factory default. You can use [dfu-programmer][dfu-prog] instead if you are on Mac.

3. Install driver for DFU bootloader. At first time you start DFU bootloader on Chip 'Found New Hardware Wizard' will come up on Windows. If you install device driver properly you can find chip name like 'ATmega32U4' under 'LibUSB-Win32 Devices' tree on 'Device Manager'. If not you shall need to update its driver on 'Device Manager'. You will find the driver in `FLIP` install directory like: C:\Program Files (x86)\Atmel\Flip 3.4.5\usb\. If you use `dfu-programmer` install its driver.

If you use PJRC Teensy you don't need step 2 and 3, just get [Teensy loader][teensy-loader].


### Download source
You can find firmware source at github: https://github.com/tmk/tmk_keyboard

If you are familiar with `Git` tools you are recommended to use it.  
If not you can download zip archive from: https://github.com/tmk/tmk_keyboard/archive/master.zip


### Build firmware
1.  Open terminal window to get access to commands. You can use `cmd` in Windows or `Terminal.app` on Mac OSX. In Windows press `Windows` key and `R` then enter `cmd` in Run command dialog showing up.

2. Move to project directory in the firmware source.

    cd tmk_keyboard/{keyboard or converter}/<project>

3. Build firmware using GNU `make` command. You'll see <project>_<variant>.hex file in that directory unless something unexpected occurs in build process.

    mkae -f Makefile.<variant> clean
    make -f Makefile.<variant>




### Program Controller
Sock AVR USB chip including ATmega32U4 has DFU bootloader by factory default, you can use DFU tools for this purpose. `FLIP` is a DFU tool on Windows offered by Atmel. Open source command line DFU tool `dfu-programmer` also supports AVR chips, which run on Linux, Mac OSX and even Windows. If you have a PJRC Teensy you should use `Teensy Loader`.

#### DFU bootloader
To program AVR chip with DFU bootloader use `FLIP` or `dfu-programmer`.
If you have a proper program command in `Makefile` just type this.

`FLIP` has two version of tool, GUI app and command line program. If you want GUI see tutorial section below.
To use command line tool run this command. Note that you need to set PATH variable properly.

    $ make -f Makefile.<variant> flip

To program with `dfu-programmer` run:

    $ make -f Makefile.<variant> dfu

#### Teensy
If you have PJRC Teensy see instruction of `Teensy Loader` at: <http://www.pjrc.com/teensy/loader.html>
Or use this command if you have command line version of Teensy Loader installed.

    $ make -f Makefile.<variant> teensy


#### Other programmer
You may want to use other you favorite programmer like `avrdude` with AVRISPmkII, Aruduino or USBasp. In that case you can still use make target `program` for build with configuring PROGRAM_CMD in Makefile.

    $ make -f Makefile.<variant> program



#### FLIP GUI tutorial
1. On menu bar click Device -> Select, then. `ATmega32u4`.
2. On menu bar click Settings -> Communication -> USB, then click 'Open' button on 'USB Port Connection' dialog.
At this point you'll see greyouted widgets on the app get colored and ready.

3. On menu bar click File -> Load HEX File, then select your firmware hex file on File Selector dialog.
4. On 'Operations Flow' panel click 'Run' button to load the firmware binary to the chip. Note that you should keep 'Erase', 'Blank Check', 'Program' and 'Verify' check boxes selected.
5. Re-plug USB cord or click 'Start Application' button to restart your controller.
Done.

See also these instaructions if you need.

- <http://code.google.com/p/micropendous/wiki/LoadingFirmwareWithFLIP>
- <http://www.atmel.com/Images/doc7769.pdf>


[winavr]:       http://winavr.sourceforge.net/
[crosspack]:    http://www.obdev.at/products/crosspack/index.html
[flip]:         http://www.atmel.com/tools/FLIP.aspx
[dfu-prog]:     http://dfu-programmer.sourceforge.net/
[teensy-loader]:http://www.pjrc.com/teensy/loader.html



Makefile Options
----------------
### 1. MCU and Frequency.

    MCU = atmega32u4       # Teensy 2.0
    #MCU = at90usb1286      # Teensy++ 2.0
    F_CPU = 16000000

### 2. Features
Note that ***comment out*** to disable them.

    BOOTMAGIC_ENABLE = yes      # Virtual DIP switch configuration(+1000)
    MOUSEKEY_ENABLE = yes       # Mouse keys(+4700)
    EXTRAKEY_ENABLE = yes       # Audio control and System control(+450)
    CONSOLE_ENABLE = yes        # Console for debug(+400)
    SLEEP_LED_ENABLE = yes      # Breathing sleep LED during USB suspend
    #NKRO_ENABLE = yes          # USB Nkey Rollover - not yet supported in LUFA
    #PS2_MOUSE_ENABLE = yes     # PS/2 mouse(TrackPoint) support

### 3. Programmer
Optional. Set proper command for your controller, bootloader and programmer. This command can be used with `make program`.

    # for PJRC Teensy
    PROGRAM_CMD = teensy_loader_cli -mmcu=$(MCU) -w -v $(TARGET).hex

    # for Atmel chip with DFU bootloader
    PROGRAM_CMD = dfu-programmer $(MCU) flash $(TARGET).hex

    # avrdude with other methods
    PROGRAM_CMD = avrdude -p $(MCU) -c avrispmkII -P USB -U flash:w:$(TARGET).hex
    PROGRAM_CMD = avrdude -p $(MCU) -c usbasp -U flash:w:$(TARGET).hex
    PROGRAM_CMD = avrdude -p $(MCU) -c arduino -P COM1 -b 57600 -U flash:w:$(TARGET).hex



Config.h Options
----------------
### 1. USB vendor/product ID and device description
    #define VENDOR_ID       0xFEED
    #define PRODUCT_ID      0xBEEF
    /* device description */
    #define MANUFACTURER    t.m.k.
    #define PRODUCT         Macway mod
    #define DESCRIPTION     t.m.k. keyboard firmware for Macway mod

### 2. Keyboard matrix configuration
    #define MATRIX_ROWS 8
    #define MATRIX_COLS 8
    #define MATRIX_HAS_GHOST

### 3. Mouse keys

### 4. PS/2 mouse

### 5. COMMAND key combination

    #define IS_COMMAND() (keyboard_report->mods == (MOD_BIT(KB_LSHIFT) | MOD_BIT(KB_RSHIFT))) 


Change your keymap
------------------
[keymap.md](doc/keymap.md)




Debuging
--------
Use PJRC's `hid_listen` to see debug messages. You can use the tool for debug even if firmware use LUFA stack.

You will see output from firmware like this.

    r/c 01234567
    00: 00000000
    01: 00000000
    02: 00000000
    03: 00000000
    04: 00000000
    05: 00000000
    06: 00000000
    07: 00000000

    ---- action_exec: start -----
    EVENT: 0307u(22511)
    Tapping: Tap release(2)
    ACTION: ACT_LAYER[5:2C]
    LAYER_PRESSED: Tap: unregister_code
    TAPPING_KEY=0307u(22511):2
    processed: 0307u(22511):2

    Tapping: End(Timeout after releasing last tap): FFFFu(22715)
    TAPPING_KEY=0000u(0):0




Magic Comannds
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
    p:      toggle print enable
    v:      print device version & info
    t:      print timer count
    s:      print status
    0/F10:  switch to Layer0
    1/F1:   switch to Layer1
    2/F2:   switch to Layer2
    3/F3:   switch to Layer3
    4/F4:   switch to Layer4
    PScr:   power down/remote wake-up
    Caps:   Lock Keyboard(Child Proof)
    Paus:   jump to bootloader

**TBD**

### Conguration with Boot Magic
Boot Magic are executed during boot up time. Press Magic key below then pulgin keyboard cable.
These settings are stored in EEPROM.

- Clear configuration stored in EEPROM(`Backspace`)
- Kick up Bootloader(`B`)
- Debug enable(`D`)
- Swap Control and CapsLock(`Left Control`)
- Change CapsLock to Control(`Casp Lock`)
- Swap LeftAlt and Gui(`Left Alt`)
- Swap RightAlt and Gui(`Right Alt`)
- Disable Gui(`Left Gui`)
- Swap Grave and Escape(`Grave`)
- Swap BackSlash and BackSpace(`Back Slash`)

**TBD**


Mechanical Locking support for CapsLock
---------------------------------------
To enable this feature define these two macros in `config.h` and use `KC_LCAP` for locking CapsLock in keymap instead of normal `KC_CAPS`. Resync option tries to keep lock switch state consistent with keyboard LED state.
 
    #define CAPSLOCK_LOCKING_ENABLE
    #define CAPSLOCK_LOCKING_RESYNC_ENABLE


Start Your Own Project
-----------------------
**TBD**



Files & Directories
-------------------
### Top
* common/       - common codes
* protocol/     - keyboard protocol support
* keyboard/     - keyboard projects
* converter/    - protocol converter projects
* doc/          - documents
* common.mk     - Makefile for common
* protoco.mk    - Makefile for protocol
* rules.mk      - Makefile for build rules

### Common
* action.[ch]
* action_macro.[ch]
* bootloader.[ch]
* command.[ch]
* controller_teensy.h
* debug.[ch]
* host.[ch]
* host_driver.h
* keyboard.[ch]
* keycode.h
* keymap.[ch]
* led.h
* matrix.h
* mousekey.[ch]
* print.[ch]
* report.h
* sendchar.h
* sendchar_null.c
* sendchar_uart.c
* timer.[ch]
* uart.[ch]
* util.[ch]

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



License
-------
Under `GPL` 2 or later. Some protocol files are under `Modified BSD License`.
LUFA, PJRC and V-USB stack have their own license respectively.
