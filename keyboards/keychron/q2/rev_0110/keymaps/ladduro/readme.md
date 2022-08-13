# Ladduro keymap for Keychron Q2 (ANSI rev_0110) v1.01

This keymap ports Q1 logic (by gtg465x) for RGB caps lock indicator and layer RBG assigned key.

## Features:
- On macOS, F3 opens Mission Control and F4 opens Launchpad without needing to configure shortcuts in System Preferences
- RGB lighting turns off when the computer sleeps
- Caps Lock and alpha keys turn red to indicate when Caps Lock is on
- When the Fn layer is active, RGB lighting turns off for keys that are not assigned

Make example for this keyboard (after setting up your build environment):

    make keychron/q2/rev_0110:ladduro

Flashing example for this keyboard:

    make keychron/q2/rev_0110:ladduro:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Changelog

### 14/03/2021 - 1.

- Initial release

### 02/04/2021 - 1.01

- Remove via enable from rules.mk as it breaks the layout for some reason
