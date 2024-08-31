# Miscellaneous FAQ

## How do I test my keyboard? {#testing}

Testing your keyboard is usually pretty straightforward. Press every single key and make sure it sends the keys you expect. You can use [QMK Configurator](https://config.qmk.fm/#/test/)'s test mode to check your keyboard, even if it doesn't run QMK.

## Safety Considerations

You probably don't want to "brick" your keyboard, making it impossible
to rewrite firmware onto it.  Here are some of the parameters to show
what things are (and likely aren't) too risky.

- If your keyboard map does not include QK_BOOT, then, to get into DFU
  mode, you will need to press the reset button on the PCB, which
  requires unscrewing the bottom.
- Messing with tmk_core / common files might make the keyboard
  inoperable
- Too large a .hex file is trouble; `make dfu` will erase the block,
  test the size (oops, wrong order!), which errors out, failing to
  flash the keyboard, leaving it in DFU mode.
  - To this end, note that the maximum .hex file size on e.g. Planck
    is 7000h (28672 decimal)

```
Linking: .build/planck_rev4_cbbrowne.elf                                                            [OK]
Creating load file for Flash: .build/planck_rev4_cbbrowne.hex                                       [OK]

Size after:
   text    data     bss     dec     hex filename
      0   22396       0   22396    577c planck_rev4_cbbrowne.hex
```

  - The above file is of size 22396/577ch, which is less than
    28672/7000h
  - As long as you have a suitable alternative .hex file around, you
    can retry, loading that one
  - Some of the options you might specify in your keyboard's Makefile
    consume extra memory; watch out for BOOTMAGIC_ENABLE,
    MOUSEKEY_ENABLE, EXTRAKEY_ENABLE, CONSOLE_ENABLE
- DFU tools do /not/ allow you to write into the bootloader (unless
  you throw in an extra fruit salad of options), so there is little risk
  there.
- EEPROM has around a 100000 (100k) write cycle.  You shouldn't rewrite
  the firmware repeatedly and continually; that'll burn the EEPROM
  eventually.

## NKRO Doesn't work
First you have to compile firmware with the build option `NKRO_ENABLE` in **Makefile**.

Try `Magic` **N** command(`LShift+RShift+N` by default) when **NKRO** still doesn't work. You can use this command to toggle between **NKRO** and **6KRO** mode temporarily. In some situations **NKRO** doesn't work and you will need to switch to **6KRO** mode, in particular when you are in BIOS.


## TrackPoint Needs Reset Circuit (PS/2 Mouse Support)
Without reset circuit you will have inconsistent result due to improper initialization of the hardware. See circuit schematic of TPM754:

- https://geekhack.org/index.php?topic=50176.msg1127447#msg1127447
- https://www.mikrocontroller.net/attachment/52583/tpm754.pdf


## Can't Read Column of Matrix Beyond 16
Use `1UL<<16` instead of `1<<16` in `read_cols()` in [matrix.h] when your columns goes beyond 16.

In C `1` means one of [int] type which is [16 bit] in case of AVR, so you can't shift left more than 15. Thus, calculating `1<<16` will unexpectedly equal zero. To work around this, you have to use [unsigned long] type with `1UL`.

https://deskthority.net/workshop-f7/rebuilding-and-redesigning-a-classic-thinkpad-keyboard-t6181-60.html#p146279

## Special Extra Key Doesn't Work (System, Audio Control Keys)
You need to define `EXTRAKEY_ENABLE` in `rules.mk` to use them in QMK.

```
EXTRAKEY_ENABLE = yes          # Audio control and System control
```

## Wake from Sleep Doesn't Work

In Windows check `Allow this device to wake the computer` setting in **Power Management** property tab of **Device Manager**. Also check your BIOS settings. Pressing any key during sleep should wake host.

## Using Arduino?

**Note that Arduino pin naming is different from actual chip.** For example, Arduino pin `D0` is not `PD0`. Check circuit with its schematics yourself.

- https://arduino.cc/en/uploads/Main/arduino-leonardo-schematic_3b.pdf
- https://arduino.cc/en/uploads/Main/arduino-micro-schematic.pdf

Arduino Leonardo and micro have **ATMega32U4** and can be used for TMK, though Arduino bootloader may be a problem.

## Enabling JTAG

By default, the JTAG debugging interface is disabled as soon as the keyboard starts up. JTAG-capable MCUs come from the factory with the `JTAGEN` fuse set, and it takes over certain pins of the MCU that the board may be using for the switch matrix, LEDs, etc.

If you would like to keep JTAG enabled, just add the following to your `config.h`:

```c
#define NO_JTAG_DISABLE
```

## USB 3 Compatibility
Some problems can be fixed by switching from a USB 3.x port to a USB 2.0 port.


## Mac Compatibility
### OS X 10.11 and Hub
See here: https://geekhack.org/index.php?topic=14290.msg1884034#msg1884034


## Problem in BIOS (UEFI) Setup/Resume (Sleep & Wake)/Power Cycles
Some people reported their keyboard stops working in BIOS and/or after resume(power cycles).

As of now the root cause is not clear, but some build options seem to be related. In Makefile, try to disable options like `CONSOLE_ENABLE`, `NKRO_ENABLE`, `SLEEP_LED_ENABLE` and/or others.

More info:
- https://github.com/tmk/tmk_keyboard/issues/266
- https://geekhack.org/index.php?topic=41989.msg1967778#msg1967778
