# Kyria's lw Keymap

Custom keymap for the [kyria keyboard](https://blog.splitkb.com/blog/introducing-the-kyria). It is intended to be used with an *English (US, intl. with dead keys)* keyboard layout (includes the `keymap_us_international.h` header). 

This layout is mainly designed for every day writing in either English, French or German and programming. 

The layout implements all accents and symbols (leveraging dead keys) found on a **swiss** keyboard. It uses Unicode for special characters. It makes use of the [Linux built-in IBus Unicode input](https://docs.qmk.fm/#/feature_unicode?id=input-modes) and relies on [WinCompose](https://github.com/samhocevar/wincompose) for Windows. 

## Build this keymap
```bash
qmk compile -kb splitkb/kyria/rev1 -km lw
```

## Flash this keymap

> **Note**: this was tested for an Elite-C microcontroller. 

First, check that the bootloader is visible. For instance:
```bash
$ lsusb
...
Bus 001 Device 034: ID 03eb:2ff4 Atmel Corp. atmega32u4 DFU bootloader
...
```
If the bootloader is not visible, press the reset button of the microcontroller. The bootloader should become visible when running the `lsusb` command again. 

The microcontroller can now be flashed: 
```bash
qmk flash -kb splitkb/kyria/rev1 -km lw
```
> **Note**: if there is any issue, run `qmk doctor` to see whether the qmk configuration is valid. 

## Implemented keymaps
The default keymap contains 5 layers which allows it to include all keys found on an ANSI layout TKL keyboard plus media keys.
Hardware features of the Kyria such as OLEDs, rotary encoders and underglow are also supported.

The five different layers are the following:
1. Base layer (QWERTZ)
2. Symbols/Numbers layer
3. Navigation layer

### Base layer
This layer is activated by default. 

```
/*
 * 0. Base Layer: QWERTZ
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Esc   |   Q  |   W  |   E  |   R  |   T  |                              |   Z  |   U  |   I  |   O  |   P  |  Del   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  Tab   |   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ' "  | BkSpace|
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Y  |   X  |   C  |   V  |   B  | \ |  |  ` ~ |  |  (   |   )  |   N  |   M  | ,  < | . >  | ;  : | CpLock |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |LCtrl | LGUI | LAlt | Space| MO(1)|  | MO(2)| Enter| - _  |  !   | / ?  |
 *                        |      |      |      |      |      |  |      |/shift|      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
```

Hold down the `Enter` key to make it a shift. This compensates for the poor placement of the dedicated `LShift` key. 

### Symbol layer
This layer is activated when holding `MO(1)`.

```
/*
 * 1. Sym Layer: Numbers and symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |   F1   |  F2  |  F3  |  F4  | LAlt | PASTE|                              |   ,  |  7   |  8   |  9   |  *   |  /     |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |   F5   |  F6  |  F7  |  F8  |  @   | COPY |                              |   .  |  6   |  7   |  8   |  =   |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |   F9   |  F10 |  F11 |  F12 |  &   |  CUT | UNDO | FIND |  |   [  |  ]   |   0  |  1   |  2   |  3   |  +   |   -    |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |  $   |  #   |  %   |      | MO(1)|  | MO(2)|      |  \ | |  {   |   }  |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
```

### Navigation layer
This layer is activated when holding `MO(2)`.

```
/*
 * 2. Nav Layer: Media, navigation, accents
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        | Brt+ | Next | Fwd  | Play | Vol+ |                              | Home | PgUp |  Up  | PgDn |      | Del    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | Brt- | Prev | Bckw | Stop | Vol- |                              |  End | Left | Down | Right|ScrLck| BkSpace|
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |  ´   |  `   |  ^   |  ¨   | Mute |      |UC_Nxt|  |RShift| Menu | PrtSc| ç/Ç  | § °  |      | SAVE | Insert |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |LCtrl | LGUI | LAlt |      | MO(1)|  | MO(2)| UNDO |  CUT | COPY | PASTE|
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
```

The key `UC_NEXT` allows to switch between Linux and Windows unicode. Note however that [WinCompose](https://github.com/samhocevar/wincompose) must be installed on Windows (simply download and install the latest release and it will run). 