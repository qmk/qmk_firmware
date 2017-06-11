# ErgoDox Familiar Layout
Familiar layout for those who regularly switch back and forth from ErgoDox to regular QWERTY.

[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](../../../../license_GPLv3.md../../../../license_GPLv3.md) [![standard-readme compliant](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg)](https://github.com/RichardLitt/standard-readme)

## Table of Contents

- [Background](#background)
- [Install](#install)
- [Usage](#usage)
    - [Layers](#layers)
- [Contribute](#contribute)
    - [Issues](#issues)
- [License](#license)

## Background

This layout is built to be as familiar as possible for users coming directly from a default (QWERTY US) keyboard, while gaining as much advantage as possible from the ErgoDox and QMK featureset. I use an ErgoDoxEZ at home, but I don't have a regular office (CS grad student) so I regularly use either my laptop or a default-setup lab computer; I context switch daily so this layout is meant to reduce the mental overhead as much as possible.

The default ErgoDoxEZ layout is probably more optimized as a solo daily driver - as are a lot of the others available keymaps. The focus of this layout is to get as much from the 'Dox as possible without overly disrupting long-established muscle memory.

Key features of the familiar layout:
1. QWERTY default layout.
1. International symbols layer, mapped in the US-International layout default positions, through [UCIS](https://github.com/qmk/qmk_firmware/wiki/Unicode-and-additional-language-support#ucis_enable).
1. Numpad layer on right hand.
1. Thumb cluster holds spacebar, ALT, and access to secondary layers.
1. Function-layer arrow keys in both the first-person-shooter (actually ESDF instead of WASD) and vim (HJKL) locations.

## Install

If you are on Windows or Mac, choose the proper line in [`keymap.c`](keymap.c) for [unicode/international character support](https://github.com/qmk/qmk_firmware/wiki/Unicode-and-additional-language-support#ucis_enable) (starts at line 235).
```c
void matrix_init_user(void) {
    set_unicode_input_mode(UC_LNX); // Linux
    //set_unicode_input_mode(UC_OSX); // Mac OSX
    //set_unicode_input_mode(UC_WIN); // Windows (with registry key, see wiki)
    //set_unicode_input_mode(UC_WINC); // Windows (with WinCompose, see wiki)
};
```

For instructions on building and installing this keymap, [go to the wiki](https://github.com/qmk/qmk_firmware/tree/master/keyboards/ergodox#build-dependencies). Below is the command for me; it may be different for you.
```sh
$ make ergodox-ez-familiar-teensy
```

## Usage

[![Familiar Layout](https://i.imgur.com/jflmkBb.png)](http://www.keyboard-layout-editor.com/#/gists/13508a9f99cff381d58b7be6f7dcc644)

### Layers
1. Base Layer: QWERTY, with arrow keys at bottom right.
1. UCIS Layer: US-International symbols layer, plus —. Accessed by toggling the `INTL` layer using the UCIS key (bottom of left thumb cluster).
1. UCIS-Shifted Layer: Making shift work for UCIS characters. An ugly workaround. Any ideas? Accessed through holding shift while the UCIS layer is active (toggles the `INSF` layer).
1. Numpad Layer: Right hand number pad. Accessed by toggling the `NUMP` layer using the NPAD key (bottom of right thumb cluster).
1. Function Layer: F1-F12, arrows on ESDF and HJKL, media player controls. Accessed by holding either FN key (center key of each thumb cluster), which toggles the `ARRW` layer. I know, I need to work on my naming conventions.

## Contribute

[Contributor Covenant](http://contributor-covenant.org/)

I'm terrible at this; I have no background in human-computer interaction, kinesiology, or keyboard-ology. Please send comments/issues/pull requests/angry tweets/etc. If you think there is a better way to take advantage of the ErgoDox/QMK comination without straying far from 84/101-key QWERTY, I want to know it.

### Issues
1. The top two keys of the right thumb cluster are currently unused. I wanted them for screen brightness, but I haven't found a solution I like.
1. The `'`, `"`, `[`, and `]` keys are terrible to access; I want to put them somewhere else but I haven't figured out where.
1. The `INSF` layer is an ugly workaround. I should write a function for doing different things in the `INTL` layer depending on whether SHIFT is being held. Or something. Ideas?

## License
QMK is licensed ([mostly](https://github.com/qmk/qmk_firmware/issues/1038)) under the [GPLv2](blob/master/license_GPLv2.md). Accordingly, to whatever extent applicable, this keymap is licensed under the [GPLv3](../../../../license_GPLv3.md).
