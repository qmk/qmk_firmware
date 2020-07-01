# Ivan's Ergodox Config


## Details about the layout

- Shift and Cmd are One Shot Modifiers, so tapping them once will apply them to the next key. When tapped twice they will lock, until tapped again to clear.
- When switching to other layers, any stuck modifiers are cleared in order to avoid unintended key combos
- There are a few leader key combinations. Right now, `KC_LEAD` + `s` will open my wiki homepage.
- All transparent keys have been replaced with noops to avoid layer bleeding.

## Initial Setup

### QMK

```
brew tap osx-cross/avr
brew tap PX4/homebrew-px4
brew update
brew install avr-gcc
brew install dfu-programmer
brew install gcc-arm-none-eabi
brew install avrdude

git clone https://github.com/qmk/qmk_firmware.git
git clone https://github.com/issmirnov/ergodox-layout.git \
            layouts/community/ergodox/ismirnov
```

### Teensy utils

Download and add both of these to $PATH

- [hid_listen](https://www.pjrc.com/teensy/hid_listen.html)
- [teensy loader cli](https://www.pjrc.com/teensy/loader_cli.html)

## Flashing

```
make ergodox_ez:ismirnov
teensy_loader_cli -mmcu=atmega32u4 -w -v ergodox_ez_ismirnov.hex

# or just
make ergodox_ez:ismirnov:flash
```

## Gotchas

- If you get error: `dyld: Library not loaded: /usr/local/opt/isl/lib/libisl.15.dylib` then do `brew reinstall avr-gcc`
- If `hid_listen` just prints out a ton of dots, update makefile with `CONSOLE_ENABLE = yes`
