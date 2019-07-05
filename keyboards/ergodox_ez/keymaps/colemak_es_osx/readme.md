# ErgoDox EZ Spanish Colemak configuration

## Description

A Colemak keymap adapted for Spanish.

### Base Layer - Spanish Colemak

The Base Layer is a Colemak keymap with an additional "&ntilde;" next to the "y" key. The arrow cluster has a proper T inverted shape.

It includes almost all Spanish Symbols from a normal 100% keyboard thanks to the use of tap keys


| Pressed | Tap | Shift | Alt |   
|---|---|---|---|
|Left Ctrl|PgDn|||
|Left Alt|`|ˆ|[|
|Left Cmd|+|*|]|
|Right Cmd|´|¨|{|
|Right Alt|ç|Ç|}|

For example, if you want to type ```[]```, you keep pressing the "Left Alt" (To modify) and tap "Right Alt" and "Right Cmd" to send "[" and "]"

### Qwerty Layer

A Qwerty layer for gaming and maybe some VIM commands. It just modifies the few keys that are different between Colemak and Qwerty and keep all the others keys

### Fn Layer

A layer to change the number row including "º" and "¡" for "Fn1" to "Fn12". The rest is just the same as the Base layer

### Mouse and media controls

Mouse movement on the left hand, wheel and buttons on the right hand. "Play/Pause", "Rewind", "Forward" in the Left inner column. "Volume Up", "Volume Down" and "Mute" in the Right inner column

### Numpad

A complete numpad in the right hand, plus and Arrow cluster on the left hand

### IDEA (JetBrains IDEs)

A momentary layer for IDEA shortcuts that require more than two fingers or any Fn key

## How to build it

If you already have all the dependencies (Check QMK's documentation), you can run the command:

```bash
make ergodox_ez:colemak_es_osx
```

On MacOS, if you're using MacPorts you can install the following dependencies:

```bash
port install avr-binutils
port install avr-gcc
port install avr-libc
```

This isn't an exhaustive list and maybe there other dependencies that are technically necessary 

## Changelog

* Jul 2019:
    * Initial version for the new QMK version

![](https://imgur.com/AyWNGlL.png)