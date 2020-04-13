# Adding RGB Underglow to the KC60

![Image of KC60 with RGB Underglow](https://i.imgur.com/LpUkVqG.jpg)

The KC60 has breakout pins to which one may wire a strip of WS2812-compatible LEDs.

By default, the source is set up for 16 LEDs on the F5 breakout pin. See [included image](https://i.imgur.com/TcKL2Sn.jpg) for wiring reference. If you attach a different number of LEDs, configure your source for the correct number of LEDs by adding a `config.h` file alongside your `keymap.c` file, with the following contents:

```c
#pragma once

#undef RGBLED_NUM
#define RGBLED_NUM <number of leds>
```

To enable RGB Underglow, simply add a `rules.mk` file containing `RGBLIGHT_ENABLE = yes` alongside your `keymap.c` file, and compile as normal:

```shell
make kc60:<keymap>
```

The [ws2812 keymap](keymaps/ws2812/) may be copied and used as a starting point.

RGB Underglow is a fairly large feature, and your firmware may be too large to be flashed with it enabled. Adding `CONSOLE_ENABLE = no` or `COMMAND_ENABLE = no` to your `rules.mk` file will reduce the size of the firmware greatly, and if you don't use either feature, is very low impact change.


## Reference Images

![Wiring Reference](https://i.imgur.com/TcKL2Sn.jpg)
![RGB Strip turned on](https://i.imgur.com/21POu4l.jpg)
![RGB Strip turned off](https://i.imgur.com/vAOLYNV.jpg)
