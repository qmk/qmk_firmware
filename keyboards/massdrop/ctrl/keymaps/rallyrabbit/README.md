# Massdrop Ctrl RallyRabbit

This is the keymap and other items tied to the RallyRabbit customizations for the Massdrop CTRL

The main layer is a ~standard ANSI QWERTY layout for Windows.

The Second Layer is modified from the standard QMK and Massdrop CTRL standard layouts.  The
biggest change is the attempt to allow for keycodes of capital and lowercase Á, É, Í, Ó, Ú, and Æ.
The present method is using unicode keycodes by forcing the keyboard into standard Windows unicode
setup.

Additionally, Layer 1 also moves the RGB Mode and Hue keys, as well as a way to enable the bookt load
and USB port on the keyboard.

Additionally this changes much of the RGB setup.
* Removed many of the standard QMK modes
* Added Rainbow Diaganol which is a small tweak of Cool Diaganol of HorrorTroll
* Added Flower Blooming of HorrorTroll
* Added Deep River (unchangeable blue with green saturation that moves)
* Added Deep River Reverse (unchangeable green with blue saturation that moves)

## To Use

Follow the QMK directions isntalling QMK MSYS.
* Download the QMK firmware (this repository)
* config.h in the current directory is used to add to the massdrop/ctrl/config.h or remove things added in that file as it is included after that file.
* rules.mk is used in addition to the massdrop/ctrl/rules.mk and is used to add to or turn off items in the standard rules.mk file
* Build with "qmk compile -kb massdrop/ctrl -km rallyrabbit"

## Layers

### Typing Layer

![Typing Layer](https://imgur.com/9oORY9m)

### "Other" Layer

![Function Layer](https://imgur.com/DVn1ilN)


