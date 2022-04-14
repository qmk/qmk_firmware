(https://raw.githubusercontent.com/khoang65/qmk_firmware/master/keyboards/omkbd/ergodash/rev1/keymaps/khoang65/keyboard-layout-editor/khoang_BASE-FN-VIM.png)
# khoang65's omkbd/ergodash/rev1 ANSI QWERTY Layout

- [LAYERS](#LAYERS)
- [LEADER KEY BINDINGS:](#LEADER-KEY-BINDINGS)
- [FLASH INSTRUCTIONS](#FLASH-INSTRUCTIONS)

## Overview
#### Easy access VIM-styled layer
- Arrow access on right hand via thumb layer toggle
#### Dual function Capslock key
- Single tap to trigger the Leader Key
- Double tap to toggle Capslock ON/OFF
#### Useful Leader Key bindings and Macros
- Encase cursor with various symbols i.e. (), [], {}, "", etc., outside of your IDE

## LAYERS

## LEADER Key Bindings
### Legend:

| Acronym | Description |
| :--- | :--- |
| LDR | Leader Key |
| SFT | Shift key |
| CTL | Control key |
| ▌ | Text cursor position |
### Cursor Wrapping Macros
| Output | Sequence | Description |
| :--- | :--- | :--- |
| `(`▌`)` | `LDR  ` | Will wrap cursor between a set of parenthesis |
| `[`▌`]` | `LDR  ` | Will wrap cursor between a set of square brackets |
| `{`▌`}` | `LDR  ` | Will wrap cursor between a set of curly braces |
| `"`▌`"` | `LDR  ` | Will wrap cursor between a set of double quotes |
| `'`▌`'` | `LDR  ` | Will wrap cursor between a set of single quotes |
| `<`▌`>` | `LDR  ` | Will wrap cursor between a set of angle brackets |
| ` `\`▌ ` `  ` | `LDR  ` | Will wrap cursor between a set of grave symbols |
| `*`▌`*` | `LDR  ` | Will wrap cursor between a set of asterisks |
| `/`▌`/` | `LDR  ` | Will wrap cursor between a set of forward slashes |
| `@`▌`@` | `LDR  ` | Will wrap cursor between a set of at symbols |
| `%`▌`%` | `LDR  ` | Will wrap cursor between a set of percent symbols |


## FLASH INSTRUCTIONS
1. Build the firmware
   > qmk compile
   - Approx. firmware size: 21682/28672 (75%, 6990 bytes free)
2. Flash firmware
   - Open QMK Toolbox App
   - Browse for *.hex file
   - Unplug TRRS connector, and plug in one half of keyboard via USB
   - Check QMK Toolbox: *** DFU device connected.
   - Hit flash button
   - Repeat for second half of keyboard
   - Unplug USB, connect two halves with the TRRS cable, and reconnect to computer