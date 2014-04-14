# Build
## 'make clean' needs after changing config.h
To build with new **config.h** you need

    $ make clean

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


# Degug Console
## hid_listen can't find device
When debug console of your device is not ready you will see like this:

    Waiting for device:.........

once the device is pluged in then *hid_listen* finds it you will get this message:

    Waiting for new device:.........................
    Listening:

Check if you can't get this 'Listening:' message:
- build with `CONSOLE_ENABLE=yes` in **Makefile**.

## Can't get message from console
Check:
- connect the device to *hid_listen*. See above.
- push **LShift+RShift+d** to enable debug. See [Magic Commands](https://github.com/tmk/tmk_keyboard#magic-commands).
- set `debug_enable=yes` usually in `matrix_init()` in **matrix.c**.
- try using 'print' function instead of debug print. See **common/print.h**.
- disconnect other devices with console function. See [Issue #97](https://github.com/tmk/tmk_keyboard/issues/97).

***

# Miscellaneous
## NKRO Doesn't work
Build with this option of Makefile

    NKRO_ENABLE = yes

And use `Magic` command **N** to toggle NKRO feature.
At this time NKRO is not used by default even if it is build with `NKRO_ENABLE`, you still need the `Magic`.

To turn on NKRO by default see this fix.
https://github.com/shayneholmes/tmk_keyboard/commit/b8375a0
```
--- a/common/host.c
+++ b/common/host.c
@@ -24,7 +24,7 @@ along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
 
 #ifdef NKRO_ENABLE
-bool keyboard_nkro = false;
+bool keyboard_nkro = true;
 #endif
 
 static host_driver_t *driver;
```

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