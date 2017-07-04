Build Firmware and Program Controller
=====================================

## This guide may be out-dated - use [build_guide.md](build_guide.md) instead

Download and Install
--------------------
### 1. Install Tools

1. **Toolchain** On Windows install [MHV AVR Tools][mhv] for AVR GCC compiler and [Cygwin][cygwin](or [MinGW][mingw]) for shell terminal. On Mac you can use [CrossPack][crosspack]. On Linux you can install AVR GCC (and avr-libc) with your favorite package manager or run the avr_setup.sh script in the root of this repository.

2. **Programmer** On Windows install [Atmel FLIP][flip]. On Mac and Linux install [dfu-programmer][dfu-prog].

3. **Driver** On Windows you start DFU bootloader on the chip first time you will see 'Found New Hardware Wizard' to install driver. If you install device driver properly you can find chip name like 'ATmega32U4' under 'LibUSB-Win32 Devices' tree on 'Device Manager'. If not you shall need to update its driver on 'Device Manager'. You will find the driver in `FLIP` install directory like: C:\Program Files (x86)\Atmel\Flip 3.4.5\usb\. In case of `dfu-programmer` use its driver.

If you use PJRC Teensy you don't need step 2 and 3 above, just get [Teensy loader][teensy-loader].


### 2. Download source
You can find firmware source at github:

- <https://github.com/tmk/tmk_keyboard>

If you are familiar with `Git` tools you are recommended to use it but you can also download zip archive from:

- <https://github.com/tmk/tmk_keyboard/archive/master.zip>


Build firmware
--------------
### 1. Open terminal
Open terminal window to get access to commands. Use Cygwin(or MingGW) `shell terminal` in Windows or `Terminal.app` on Mac OSX. In Windows press `Windows` key and `R` then enter `cmd` in 'Run command' dialog showing up.

### 2. Change directory
Move to project directory in the firmware source.

    cd tmk_keyboard/{'keyboard' or 'converter'}/<project>

### 3. Make
Build firmware using GNU `make` command. You'll see `<project>_<variant>.hex` file in that directory unless something unexpected occurs in build process.


    make -f Makefile.<variant> clean
    make -f Makefile.<variant>




Program Controller
------------------
Now you have **hex** file to program on current directory. This **hex** is only needed to program your controller, other files are used for development and you may leave and forget them.

### 1. Start bootloader
How to program controller depends on controller chip and its board design. To program AVR USB chips you'll need to start it up in bootloader mode. Most of boards with the chip have a push button to let bootloader come up. Consult with your controller board manual.

### 2. Program with DFU bootloader
Stock AVR USB chip including ATmega32U4 has DFU bootloader by factory default. `FLIP` is a DFU programmer on Windows offered by Atmel. Open source command line tool `dfu-programmer` also supports AVR chips, it runs on Linux, Mac OSX and even Windows.

To program AVR chip with DFU bootloader use `FLIP` or `dfu-programmer`.
If you have a proper program command in `Makefile` just type this.

`FLIP` has two version of tool, GUI app and command line program. If you want GUI see tutorial below.
To use command line tool run this command. Note that you need to set PATH variable properly.

    $ make -f Makefile.<variant> flip

Or to program with `dfu-programmer` run:

    $ make -f Makefile.<variant> dfu

#### FLIP GUI tutorial
1. On menu bar click Device -> Select, then. `ATmega32u4`.
2. On menu bar click Settings -> Communication -> USB, then click 'Open' button on 'USB Port Connection' dialog.
At this point you'll see grey-outed widgets on the app get colored and ready.

3. On menu bar click File -> Load HEX File, then select your firmware hex file on File Selector dialog.
4. On 'Operations Flow' panel click 'Run' button to load the firmware binary to the chip. Note that you should keep 'Erase', 'Blank Check', 'Program' and 'Verify' check boxes selected.
5. Re-plug USB cord or click 'Start Application' button to restart your controller.
Done.

See also these instructions if you need.

- <http://code.google.com/p/micropendous/wiki/LoadingFirmwareWithFLIP>
- <http://www.atmel.com/Images/doc7769.pdf>


### 3. Program with Teensy Loader
If you have PJRC Teensy see instruction of `Teensy Loader`.

- <http://www.pjrc.com/teensy/loader.html>

Or use this command if you have command line version of Teensy Loader installed.

    $ make -f Makefile.<variant> teensy


### 4. Program with Other programmer
You may want to use other programmer like `avrdude` with AVRISPmkII, Arduino or USBasp. In that case you can still use make target `program` for build with configuring `PROGRAM_CMD` in Makefile.

    $ make -f Makefile.<variant> program


[cygwin]:       https://www.cygwin.com/
[mingw]:        http://www.mingw.org/
[mhv]:          https://infernoembedded.com/products/avr-tools
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

Set your MCU and its clock in Hz.

    # Boot Section Size in *bytes*
    #   Teensy halfKay   512
    #   Atmel DFU loader 4096
    #   LUFA bootloader  4096
    OPT_DEFS += -DBOOTLOADER_SIZE=4096

If you are using PJRC Teensy use `512` for `BOOTLOADER_SIZE`, otherwise use `4096` unless you are sure.

### 2. Features
Optional. Note that ***comment out*** with `#` to disable them.

    BOOTMAGIC_ENABLE = yes      # Virtual DIP switch configuration(+1000)
    MOUSEKEY_ENABLE = yes       # Mouse keys(+4700)
    EXTRAKEY_ENABLE = yes       # Audio control and System control(+450)
    CONSOLE_ENABLE = yes        # Console for debug(+400)
    COMMAND_ENABLE = yes        # Commands for debug and configuration
    SLEEP_LED_ENABLE = yes      # Breathing sleep LED during USB suspend
    #NKRO_ENABLE = yes          # USB Nkey Rollover - not yet supported in LUFA
    #BACKLIGHT_ENABLE = yes     # Enable keyboard backlight functionality

### 3. Programmer
Optional. Set proper command for your controller, bootloader and programmer. This command can be used with `make program`. Not needed if you use `FLIP`, `dfu-programmer` or `Teensy Loader`.

    # avrdude with AVRISPmkII
    PROGRAM_CMD = avrdude -p $(MCU) -c avrispmkII -P USB -U flash:w:$(TARGET).hex

    # avrdude with USBaspLoader
    PROGRAM_CMD = avrdude -p $(MCU) -c usbasp -U flash:w:$(TARGET).hex

    # avrdude with arduino
    PROGRAM_CMD = avrdude -p $(MCU) -c arduino -P COM1 -b 57600 -U flash:w:$(TARGET).hex



Config.h Options
----------------
### 1. Magic command key combination

    #define IS_COMMAND() (keyboard_report->mods == (MOD_BIT(KB_LSHIFT) | MOD_BIT(KB_RSHIFT)))

### 2. Mechanical Locking Support for CapsLock

    /* Mechanical locking CapsLock support. Use KC_LCAP instead of KC_CAPS in keymap */
    #define CAPSLOCK_LOCKING_ENABLE
    /* Locking CapsLock re-synchronize hack */
    #define CAPSLOCK_LOCKING_RESYNC_ENABLE

### 3. Disable Debug and Print

    /* disable debug print */
    #define NO_DEBUG

    /* disable print */
    #define NO_PRINT

### 4. Disable Action Features

    #define NO_ACTION_LAYER
    #define NO_ACTION_TAPPING
    #define NO_ACTION_ONESHOT
    #define NO_ACTION_MACRO
    #define NO_ACTION_FUNCTION

***TBD***
