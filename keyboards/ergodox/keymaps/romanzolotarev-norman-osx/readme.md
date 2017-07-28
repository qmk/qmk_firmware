# Roman's Layout

There is only one layer, and it is  based on [Norman
layout](https://normanlayout.info/).

Looking for multiple-layer layouts?

- [Symbols, arrows, plover, HJKL
  arrows](../romanzolotarev-norman-plover-osx-hjkl/)
- [Same with IJKL arrows](../romanzolotarev-norman-plover-osx/)

[![keyboard-layout](https://i.imgur.com/U14664K.png)](http://www.keyboard-layout-editor.com/#/gists/9e89d54f1ea6eeeb7dab1b2d19d28195)

## How to use Vim key

It is `CTL_T(KC_ESC)` and it works this way:

- Tap `CTRL/ESC` to send `ESC`.
- Hold `CTRL/ESC` to use as `CTRL`.

## How to activate N-rollover

- Hold left `SHIFT` and right `SHIFT` and then tap `N`.

## How to make and flash on OS X

First you need to install few brew packages.

```bash
brew tap osx-cross/avr
brew install dfu-programmer avr-libc teensy_loader_cli
```

Then you can clone this repository, make and flash your ErgoDox.

```bash
git clone https://github.com/romanzolotarev/qmk_firmware
cd qmk_firmware/keyboards/ergodox
# Optionally tweak ./keymaps/romanzolotarev-norman-osx/keymap.c
SLEEP_LED_ENABLED=no KEYMAP=romanzolotarev-norman-osx make teensy
```
