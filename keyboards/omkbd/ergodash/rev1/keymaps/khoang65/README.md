![khoang65 Layout Image - MAIN](https://raw.githubusercontent.com/khoang65/qmk_firmware/master/keyboards/omkbd/ergodash/rev1/keymaps/khoang65/keyboard-layout-editor/khoang_BASE-FN-VIM.png)
# khoang65's omkbd/ergodash/rev1 ANSI QWERTY Layout

- [LAYERS](#LAYERS)
- [LEADER KEY BINDINGS](#LEADER-KEY-BINDINGS)
- [PRICE BREAKDOWN](#PRICE-BREAKDOWN)
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
### Layer 0: BASE
[img]
### Layer 1: Function
[img]
### Layer 2: VIM
[img]
### Layer 3: Numpad
[img]
### Layer 4: Adjust
[img]

## LEADER Key Bindings
### Legend:

| Acronym | Description |
| :--- | :--- |
| LDR | Leader Key |
| SFT | Shift key |
| CTL | Control key |
| ⬜️ | Text cursor position |
```
,-----------------------------------------------------------.          
|         |         | 2=> @   |         |         | 5=> %   |---------.
|---------+---------+---------+---------+---------+---------| [=> [   |
|         |         |         | E=> *   |         |         |---------|   
|---------+---------+---------+---------+---------+---------| F4=> '  |    
|         | A=> "   | S=> <   | D=> {   | F=> (   | G=> `   |---------|    
|---------+---------+---------+---------+---------+---------|         |    
|         |         |         |         | /       |         |---------'   
|---------+---------+---------+-----------------------------'            
|         |         |         ||         |                              
`-----------------------------'`---------'        ,-------------------. 
                                                  |         |         |
                                                  |         |         |
                                        ,---------|         |         |
                                        |         |         |         |
                                        `-----------------------------'
```

### Cursor Wrapping Macros
| Output | Sequence | Description |
| :--- | :--- | :--- |
| `(`⬜️`)` | `LDR F ` | Will wrap cursor between a set of parenthesis |
| `[`⬜️`]` | `LDR [ ` | Will wrap cursor between a set of square brackets |
| `{`⬜️`}` | `LDR D ` | Will wrap cursor between a set of curly braces |
| `"`⬜️`"` | `LDR A ` | Will wrap cursor between a set of double quotes |
| `'`⬜️`'` | `LDR F4 ` | Will wrap cursor between a set of single quotes |
| `<`⬜️`>` | `LDR S ` | Will wrap cursor between a set of angle brackets |
| ` `\`⬜️ ` `  ` | `LDR G ` | Will wrap cursor between a set of grave symbols |
| `*`⬜️`*` | `LDR E ` | Will wrap cursor between a set of asterisks |
| `/`⬜️`/` | `LDR V ` | Will wrap cursor between a set of forward slashes |
| `@`⬜️`@` | `LDR 2 ` | Will wrap cursor between a set of at symbols |
| `%`⬜️`%` | `LDR 5 ` | Will wrap cursor between a set of percent symbols |

## PRICE BREAKDOWN
-

## FLASH INSTRUCTIONS
1. Build the firmware
   > qmk compile
   - Approx. firmware size: 21686/28672 (75%, 6990 bytes free)
2. Flash firmware
   - Open QMK Toolbox App
   - Browse for *.hex file
   - Unplug TRRS connector, and plug in one half of keyboard via USB
   - Check QMK Toolbox: *** DFU device connected.
   - Hit flash button
   - Repeat for second half of keyboard
   - Unplug USB, connect two halves with the TRRS cable, and reconnect to computer