## UNAUSGESCHLAFEN'S QUEFRENCY

This is the keymap that goes with [unausgeschlafen's Quefrency](https://www.reddit.com/r/MechanicalKeyboards/comments/aquefb/my_daily_driver_quefrency/)

If you are using Ardoinos, comment this line in `rules.mk`:
```make
BOOTLOADER = atmel-dfu # comment this line if you use arduinos
```

Although QMK offers one-shot build and flash, I personally build and flash separately (for the Elite C).
I used the QMK default for the Arduino Pro Micros.
However, I do not own them anymore.
Hence, only the instructions for the Elite C are provided.

Build with:
```sh
make keebio/quefrency:unausgeschlafen
```

Flash with:

```sh
sudo dfu-programmer atmega32u4 erase
sudo dfu-programmer atmega32u4 flash keebio_quefrency_rev1_unausgeschlafen.hex
sudo dfu-programmer atmega32u4 reset
```
