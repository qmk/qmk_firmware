# Frequently Asked Questions

## General

### What is QMK?

[QMK](https://github.com/qmk), short for Quantum Mechanical Keyboard, is a group of people building tools for custom keyboards. We started with the [QMK firmware](https://github.com/qmk/qmk_firmware), a heavily modified fork of [TMK](https://github.com/tmk/tmk_keyboard).

### Why the name Quantum?

<!-- FIXME -->

### What Differences Are There Between QMK and TMK?

TMK was originally designed and implemented by [Jun Wako](https://github.com/tmk). QMK started as [Jack Humbert's](https://github.com/jackhumbert) fork of TMK for the Planck. After a while Jack's fork had diverged quite a bit from TMK, and in 2015 Jack decided to rename his fork to QMK.

From a technical standpoint QMK builds upon TMK by adding several new features. Most notably QMK has expanded the number of available keycodes and uses these to implement advanced features like `S()`, `LCTL()`, and `MO()`. You can see a complete list of these keycodes in [Quantum Keycodes](quantum_keycodes.html).

From a project and community management standpoint TMK maintains all the officially supported keyboards by himself, with a bit of community support. Separate community maintained forks exist or can be created for other keyboards. Only a few keymaps are provided by default, so users typically don't share keymaps with each other. QMK encourages sharing of both keyboards and keymaps through a centrally managed repository, accepting all pull requests that follows the quality standards. These are mostly community maintained, but the QMK team also helps when necessary.

Both approaches have their merits and their drawbacks, and code flows freely between TMK and QMK when it makes sense.

# Building

## Windows

### I'm on Windows Vista, 7, or 8, how do I setup my build environment?

Follow the build instructions to [install MHV AVR Tools](https://docs.qmk.fm/build_environment_setup.html#windows-vista-and-later).

### I'm on Windows 10 without the Creators Update. Do I have to install it?

No, but if you don't install the creators update you will not be able to build and flash with a single command. You will be able to build but to flash you will have to use a separate program, such as [QMK Flasher](https://github.com/qmk/qmk_flasher).

# Troubleshooting

## Debug Console
### hid_listen can't recognize device
When debug console of your device is not ready you will see like this:

```
Waiting for device:.........
```

once the device is pluged in then *hid_listen* finds it you will get this message:

```
Waiting for new device:.........................
Listening:
```

If you can't get this 'Listening:' message try building with `CONSOLE_ENABLE=yes` in [Makefile]

You may need privilege to access the device on OS like Linux.
- try `sudo hid_listen`

### Can't get message on console
Check:
- *hid_listen* finds your device. See above.
- Enable debug with pressing **Magic**+d. See [Magic Commands](https://github.com/tmk/tmk_keyboard#magic-commands).
- set `debug_enable=true` usually in `matrix_init()` in **matrix.c**.
- try using 'print' function instead of debug print. See **common/print.h**.
- disconnect other devices with console function. See [Issue #97](https://github.com/tmk/tmk_keyboard/issues/97).

### Linux or UNIX like system requires Super User privilege
Just use 'sudo' to execute *hid_listen* with privilege.
```
$ sudo hid_listen
```

Or add an *udev rule* for TMK devices with placing a file in rules directory. The directory may vary on each system.

File: /etc/udev/rules.d/52-tmk-keyboard.rules(in case of Ubuntu)
```
# tmk keyboard products     https://github.com/tmk/tmk_keyboard
SUBSYSTEMS=="usb", ATTRS{idVendor}=="feed", MODE:="0666"
```

## Software Issues

### NKRO Doesn't work
First you have to compile frimware with this build option `NKRO_ENABLE` in **Makefile**.

Try `Magic` **N** command(`LShift+RShift+N` by default) when **NKRO** still doesn't work. You can use this command to toggle between **NKRO** and **6KRO** mode temporarily. In some situations **NKRO** doesn't work you need to switch to **6KRO** mode, in particular when you are in BIOS.

If your firmeare built with `BOOTMAGIC_ENABLE` you need to turn its switch on by `BootMagic` **N** command(`Space+N` by default). This setting is stored in EEPROM and keeped over power cycles.

https://github.com/tmk/tmk_keyboard#boot-magic-configuration---virtual-dip-switch

### Can't read column of matrix beyond 16
Use `1UL<<16` instead of `1<<16` in `read_cols()` in [matrix.h] when your columns goes beyond 16.

In C `1` means one of [int] type which is [16bit] in case of AVR so you can't shift left more than 15. You will get unexpected zero when you say `1<<16`. You have to use [unsigned long] type with `1UL`.

http://deskthority.net/workshop-f7/rebuilding-and-redesigning-a-classic-thinkpad-keyboard-t6181-60.html#p146279


### Bootloader jump doesn't work
Properly configure bootloader size in **Makefile**. With wrong section size bootloader won't probably start with **Magic command** and **Boot Magic**.
```
# Size of Bootloaders in bytes:
#   Atmel DFU loader(ATmega32U4)   4096
#   Atmel DFU loader(AT90USB128)   8192
#   LUFA bootloader(ATmega32U4)    4096
#   Arduino Caterina(ATmega32U4)   4096
#   USBaspLoader(ATmega***)        2048
#   Teensy   halfKay(ATmega32U4)   512
#   Teensy++ halfKay(AT90USB128)   2048
OPT_DEFS += -DBOOTLOADER_SIZE=4096
```
AVR Boot section size are defined by setting **BOOTSZ** fuse in fact. Consult with your MCU datasheet.
Note that **Word**(2 bytes) size and address are used in datasheet while TMK uses **Byte**.

AVR Boot section is located at end of Flash memory like the followings.
```
byte     Atmel/LUFA(ATMega32u4)          byte     Atmel(AT90SUB1286)
0x0000   +---------------+               0x00000  +---------------+
         |               |                        |               |
         |               |                        |               |
         |  Application  |                        |  Application  |
         |               |                        |               |
         =               =                        =               =
         |               | 32KB-4KB               |               | 128KB-8KB
0x6000   +---------------+               0x1E000  +---------------+
         |  Bootloader   | 4KB                    |  Bootloader   | 8KB
0x7FFF   +---------------+               0x1FFFF  +---------------+


byte     Teensy(ATMega32u4)              byte     Teensy++(AT90SUB1286)
0x0000   +---------------+               0x00000  +---------------+
         |               |                        |               |
         |               |                        |               |
         |  Application  |                        |  Application  |
         |               |                        |               |
         =               =                        =               =
         |               | 32KB-512B              |               | 128KB-2KB
0x7E00   +---------------+               0x1FC00  +---------------+
         |  Bootloader   | 512B                   |  Bootloader   | 2KB
0x7FFF   +---------------+               0x1FFFF  +---------------+
```

And see this discussion for further reference.
https://github.com/tmk/tmk_keyboard/issues/179


### Special Extra key doesn't work(System, Audio control keys)
You need to define `EXTRAKEY_ENABLE` in `rules.mk` to use them in QMK.

```
EXTRAKEY_ENABLE = yes          # Audio control and System control
```

### Wakeup from sleep doesn't work

In Windows check `Allow this device to wake the computer` setting in Power **Management property** tab of **Device Manager**. Also check BIOS setting.

Pressing any key during sleep should wake host.

## Hardware Issues

### TrackPoint needs reset circuit(PS/2 mouse support)
Without reset circuit you will have inconsistent reuslt due to improper initialize of the hardware. See circuit schematic of TPM754.

- http://geekhack.org/index.php?topic=50176.msg1127447#msg1127447
- http://www.mikrocontroller.net/attachment/52583/tpm754.pdf

### Using Arduino?

**Note that Arduino pin naming is different from actual chip.** For example, Arduino pin `D0` is not `PD0`. Check circuit with its schematics yourself.

- http://arduino.cc/en/uploads/Main/arduino-leonardo-schematic_3b.pdf
- http://arduino.cc/en/uploads/Main/arduino-micro-schematic.pdf

Arduino leonardo and micro have **ATMega32U4** and can be used for TMK, though Arduino bootloader may be a problem.

### Using PF4-7 pins of USB AVR?
You need to set JTD bit of MCUCR yourself to use PF4-7 as GPIO. Those pins are configured to serve JTAG function by default. MCUs like ATMega*U* or AT90USB* are affeteced with this.

If you are using Teensy this isn't needed. Teensy is shipped with JTAGEN fuse bit unprogrammed to disable the function.

See this code.
```
    // JTAG disable for PORT F. write JTD bit twice within four cycles.
    MCUCR |= (1<<JTD);
    MCUCR |= (1<<JTD);
```
https://github.com/tmk/tmk_keyboard/blob/master/keyboard/hbkb/matrix.c#L67

And read **26.5.1 MCU Control Register – MCUCR** of ATMega32U4 datasheet.


### Program Arduino Micro/Leonardo
Push reset button and then run command like this within 8 seconds.

```
avrdude -patmega32u4 -cavr109 -b57600 -Uflash:w:adb_usb.hex -P/dev/ttyACM0
```

Device name will vary depending on your system.

http://arduino.cc/en/Main/ArduinoBoardMicro
https://geekhack.org/index.php?topic=14290.msg1563867#msg1563867

### Problem on BIOS(UEFI)/Resume(Sleep&Wake)/Power cycles
Some people reported their keyboard stops working on BIOS and/or after resume(power cycles).

As of now root of its cause is not clear but some build options seem to be related. In Makefile try to disable those options like `CONSOLE_ENABLE`, `NKRO_ENABLE`, `SLEEP_LED_ENABLE` and/or others.

https://github.com/tmk/tmk_keyboard/issues/266
https://geekhack.org/index.php?topic=41989.msg1967778#msg1967778

## Flashing Problems

### Can't use dfu-programmer or QMK Flasher to flash on Windows

Windows requires a driver to support the keyboard in DFU mode. You can use [QMK Driver Installer](https://github.com/qmk/qmk_driver_installer/releases) to install the necessary drivers.
