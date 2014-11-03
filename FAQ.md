# Documents You Need To Read
Read these yet?
 
1. First **README** under top directory : https://github.com/tmk/tmk_keyboard/blob/master/README.md
2. For **Build**: https://github.com/tmk/tmk_keyboard/blob/master/doc/build.md
3. And **README** under each project(keyboard/converter) directory

Note that you should read two **README**.


# Build
## How to Build
See this first!
https://github.com/tmk/tmk_keyboard/blob/master/doc/build.md

In short,

    $ make clean
    $ make [KEYMAP=...]


## Do 'make clean' before 'make'
You'll need `make clean` after you edit **config.h** or change options like `KEYMAP`.

Frist remove all files made in previous build,

    $ make clean

then build new frimware. 

    $ make [KEYMAP=...]

Also you can always try `make clean` when you get other strange result during build.


## WINAVR is obsolete
It is no longer recommended and may cause some problem.
See [Issue #99](https://github.com/tmk/tmk_keyboard/issues/99).

## USB stack: LUFA or PJRC?
Use **LUFA**.

**PJRC** stack won't be supported actively anymore. There is no reason to hesitate to use LUFA except for binary size(about 1KB lager?). But **PJRC** is still very useful for debug and development purpose.
See also [Issue #50](https://github.com/tmk/tmk_keyboard/issues/50) and [Issue #58](https://github.com/tmk/tmk_keyboard/issues/58).


## Edit configuration but not change
Try these.
### 1. make clean
This will be needed when you edit **config.h**.

### 2. Remove Drivers from Device Manager(Windows)
Windows only. Linux, OSX and other OS's doesn't require this. It looks like Windows keeps using driver installed when device was connected first time even after the device changes its configuration. To load proper drivers for new configuration you need to remove existent drivers from **Drvice Manager**.

You will need this after editing `CONSOLE_ENABLE`, `NKRO_ENABLE`, `EXTRAKEY_ENABLE` or `MOUSEKEY_ENABLE` option in **Makefile**.


# Keymap
## Power key doesn't work
Use `KC_PWR` instead of `KC_POWER` or vice versa.
- `KC_PWR` works with Windows and Linux, not with OSX.
- `KC_POWER` works with OSX and Linux, not with Windows.

http://geekhack.org/index.php?topic=14290.msg1327264#msg1327264

## Oneshot modifier
Solves my personal 'the' problem. I often got 'the' or 'THe' wrongly instead of 'The'.  Oneshot Shift mitgates this for me.
https://github.com/tmk/tmk_keyboard/issues/67

## Modifier/Layer stuck
Modifier keys or layers can be stuck unless layer switching is configured properly.
For Modifier keys and layer actions you have to place `KC_TRANS` on same position of destination layer to  unregister the modifier key or return to previous layer on release event.

https://github.com/tmk/tmk_keyboard/blob/master/doc/keymap.md#31-momentary-switching
http://geekhack.org/index.php?topic=57008.msg1492604#msg1492604


# Degug Console
## hid_listen can't find device
When debug console of your device is not ready you will see like this:

    Waiting for device:.........

once the device is pluged in then *hid_listen* finds it you will get this message:

    Waiting for new device:.........................
    Listening:

Check if you can't get this 'Listening:' message:
- build with `CONSOLE_ENABLE=yes` in **Makefile**.

## Can't get message on console
Check:
- connect the device to *hid_listen*. See above.
- push **LShift+RShift+d** to enable debug. See [Magic Commands](https://github.com/tmk/tmk_keyboard#magic-commands).
- set `debug_enable=yes` usually in `matrix_init()` in **matrix.c**.
- try using 'print' function instead of debug print. See **common/print.h**.
- disconnect other devices with console function. See [Issue #97](https://github.com/tmk/tmk_keyboard/issues/97).

## Linux or UNIX like system requires Super User privilege
Just use 'sudo' to execute 'hid_listen' with privilege.
```
$ sudo hid_listen
```

Or add an *udev rule* for TMK devices with placing a file in rules directory. The directory may vary on each system.

File: /etc/udev/rules.d/52-tmk-keyboard.rules(in case of Ubuntu)
```
# tmk keyboard products     https://github.com/tmk/tmk_keyboard
SUBSYSTEMS=="usb", ATTRS{idVendor}=="feed", MODE:="0666"
```

***

# Miscellaneous
## NKRO Doesn't work
1. Build with this option of Makefile

    NKRO_ENABLE = yes

2. After boot keyboard may be in **boot mode**(6KRO), you will need to replug keyboard to enable NKRO.

3. Or use `Magic` **N** command to toggle NKRO function.(`LShift+RShift+N` by default)



## TrackPoint needs reset circuit(PS/2 mouse support)
Without reset circuit you will have inconsistent reuslt due to improper initialize of the hardware. See circuit schematic of TPM754.

- http://geekhack.org/index.php?topic=50176.msg1127447#msg1127447
- http://www.mikrocontroller.net/attachment/52583/tpm754.pdf


## Can't read comlumn of matrix beyond 16 
Use `1UL<<16` intead of `1<<16` in `read_cols()` in **matrix.h** when your columns goes beyond 16.

In C `1` means one of **int** type which is **16bit** in case of AVR so you can't shift left more than 15. You will get unexpected zero when you say `1<<16`. You have to use **unsigned long** type with `1UL`.

http://deskthority.net/workshop-f7/rebuilding-and-redesigning-a-classic-thinkpad-keyboard-t6181-60.html#p146279



## Pull-up Resistor
In some case converters needed to have pull-up resistors to work correctly. Place the resistor between VCC and signal line in parallel.

For example:
```
Keyboard       Conveter
               ,------.
5V------+------|VCC   |
        |      |      |
        R      |      |
        |      |      |
Signal--+------|PD0   |
               |      |
GND------------|GND   |
               `------'
R: 1K Ohm resistor
```

https://github.com/tmk/tmk_keyboard/issues/71


## Arduino Micro's pin naming is confusing
Note that Arduino Micro PCB marking is different from real AVR port name. D0 of Arduino Micro is not PD0, PD0 is D3. Check schematic yourself.
http://arduino.cc/en/uploads/Main/arduino-micro-schematic.pdf



## Bootloader jump doesn't work
Properly configure boot section size in Makefile. With wrong section size bootloader won't probably start with **Magic command** and **Boot Magic**.
- https://github.com/tmk/tmk_keyboard#magic-commands
- https://github.com/tmk/tmk_keyboard#bootloader

```
# Boot Section Size in *bytes*
#   Teensy halfKay   512
#   Teensy++ halfKay 1024
#   Atmel DFU loader 4096       (TMK Alt Controller)
#   LUFA bootloader  4096
#   USBaspLoader     2048
OPT_DEFS += -DBOOTLOADER_SIZE=4096
```
http://geekhack.org/index.php?topic=12047.msg1292018#msg1292018


## Special Extra key doesn't work(System, Audio control keys)
You need to define `EXTRAKEY_ENABLE` in **makefile** to use them in TMK.
```
EXTRAKEY_ENABLE = yes          # Audio control and System control
```
http://deskthority.net/workshop-f7/tmk-keyboard-firmware-collection-t4478-60.html#p157919


## Wakeup from sleep doesn't work
In Windows check `Allow this device to wake the computer` setting in Power **Management property** tab of **Device Manager**. Also check BIOS setting.

Pressing any key during sleep should wake host.


## Using Arduino?
**Note that Arduino pin naming is different from actual chip.** For example, Arduino pin `D0` is not `PD0`. Check circuit with its schematics yourself.

- http://arduino.cc/en/uploads/Main/arduino-leonardo-schematic_3b.pdf
- http://arduino.cc/en/uploads/Main/arduino-micro-schematic.pdf

Arduino leonardo and micro have **ATMega32U4** and can be used for TMK, though Arduino bootloader may be a problem.


## Using PF4-7 pins of USB AVR?
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