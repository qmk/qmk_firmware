# Lets Split

Check out [user readme](../../../../users/bbaserdem/README.md) for more info.
This is still a WIP, but the firmware should be fine.

Builds fine as of 2019-12-17

# Setup

I am planning on I2C, using Proton C's (or ProMicro's).

# Caterina

The default bootloader for ProMicro.

For flashing the EEPROM with the side information, flash the following.
```
avrdude -p atmega32u4 -P "$(ls /dev/ttyACM*)" -c avr109 -U eeprom:w:"./quantum/split_common/eeprom-lefthand.eep"
avrdude -p atmega32u4 -P "$(ls /dev/ttyACM*)" -c avr109 -U eeprom:w:"./quantum/split_common/eeprom-righthand.eep"
```

Afterwards, the following command should work just fine for flashing.

```
make lets_split/rev2:bbaserdem:avrdude
```

If it does not flash, the hex files can be flashed by the following command.

For the left half, after plugging in and resetting; (from repo main directory)
```
sudo avrdude -p atmega32u4 -P "$(ls /dev/ttyACM*)" -c avr109 -D -U flash:w:"./lets_split_rev2_bbaserdem.hex"
```

# QMK-DFU

Drashna has [a conversion guide](https://www.reddit.com/r/olkb/comments/8sxgzb/replace_pro_micro_bootloader_with_qmk_dfu/)
I will outline the steps below.

Put the following code in `config.h` (Omitting ESC cause my keymap has RESET)

```
#define QMK_LED B0
#define QMK_SPEAKER C6
```

And to `rules.mk`

```
BOOTLOADER = qmk-dfu
```

Compile the firmware using the `:production` target, yielding a `_production.hex`
Then the ISP flasher can be used. This is the following for the SparkFun official;

```
avrdude -c usbtiny -p m32u4 -P usb -U flash:w:"<HEX_HERE>":a -U lfuse:w:0x5E:m -U hfuse:w:0xD9:m -U efuse:w:0xC3:m -U lock:w:0x3F:m
```

# Proton C

Referring to [the documentation](https://docs.qmk.fm/#/proton_c_conversion)
it should be straightforward to do it.
The command is

```
make lots_split/rev2:bbaserdem:dfu CTPC=yes
```

NEED TO ADD EEPROM FLASHING HALVES HERE
