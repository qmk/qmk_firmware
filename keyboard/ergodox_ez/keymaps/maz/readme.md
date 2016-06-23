# Introduction

## Motivation
I created this keymap in an attempt to optimize my typing experience in text editors and the command-line.

More specifically, I wanted to have each modifier key controlled by the thumbs, the most powerful of the digits (I think). This cured me of emacs pinky, which had surprisingly grown quite quickly over the first two weeks of using emacs & emacs-like commands on the command-line.

## Changes
The biggest changes from the ergodox ez default keymap are the modifiers on the thumb cluster. You must hold each key down for a certain amount of time (forgot where this is specified) in order for the modifier key to activate.

## Caveats
### Thumb Cluster Range
I've heard many complaints about the thumb clusters. I agree that the three outter keys are almost impossible to reach. I am going to try to build [Matt Adereth's keyboard](https://github.com/adereth/dactyl-keyboard), which looks to have a better layout. However, I am able to comfortably use the three modifier keys mainly because:
* I use DCS keycaps with SA Row 3 keycaps where the Alt keys are
* I have relatively large hands (I guarantee you there's no problem - I guarantee you)

### Dangerous positioning
I think it's quite dangerous to put something like control on the same key as enter. Alas, this is a risk I'm willing to accept, and so should you if you decide to use this keymap. I tend to avoid putting myself in situtation in which disaster could occur with one fell swoop of a keypress.

# Keymap
## Keymap 0: Basic layer
```
 ,--------------------------------------------------.           ,--------------------------------------------------.
 |   =    |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   -    |
 |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 | Tab    |   Q  |   W  |   E  |   R  |   T  |  L1  |           |  L1  |   Y  |   U  |   I  |   O  |   P  |   \    |
 |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 |esc/ctrl|   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |; / L2|'/ ctrl |
 |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 | LShift |Z/Ctrl|   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |//Ctrl| RShift |
 `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'        
   |Grv/L1|  '"  |AltShf| Left | Right|                                       |  Up  | Down |   [  |   ]  | ~L1  |
   `----------------------------------'                                       `----------------------------------'
                                        ,-------------.       ,-------------.
                                        | App  | LGui |       | Alt  |Ctrl/Esc|
                                 ,------|------|------|       |------+--------+------.
                                 |      |      | Home |       | PgUp |        |      |
                                 | Space| Bksp |------|       |------|  Tab   |Enter |
                                 |[ctrl]| [gui]|[Alt] |       |[Alt] | [gui]  |[ctrl]|
                                 `--------------------'       `----------------------'

```

## Keymap 1: Symbol Layer
```
  ,--------------------------------------------------.           ,--------------------------------------------------.
  |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
  |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
  |        |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
  |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
  |        |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
  |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
  |        |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
  `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
    |      |      |      |      |      |                                       |      |    . |   0  |   =  |      |
    `----------------------------------'                                       `----------------------------------'
                                         ,-------------.       ,-------------.
                                         |      |      |       |      |      |
                                  ,------|------|------|       |------+------+------.
                                  |      |      |      |       |      |      |      |
                                  |      |      |------|       |------|      |      |
                                  |      |      |      |       |      |      |      |
                                  `--------------------'       `--------------------'
```

## Keymap 2: Media and mouse keys
``` 
  ,--------------------------------------------------.           ,--------------------------------------------------.
  |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
  |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
  |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
  |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
  |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      | Lclk | Rclk |      |      |  Play  |
  |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
  |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
  `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
    |      |      |      |      |      |                                       |VolUp |VolDn | Mute |      |      |
    `----------------------------------'                                       `----------------------------------'
                                         ,-------------.       ,-------------.
                                         |      |      |       |      |      |
                                  ,------|------|------|       |------+------+------.
                                  |      |      |      |       |      |      |Brwser|
                                  |      |      |------|       |------|      |Back  |
                                  |      |      |      |       |      |      |      |
                                  `--------------------'       `--------------------'
```

# ErgoDox EZ Default Configuration

As of Feb 2, 2016, the default ErgoDox EZ keymap is:

![Default](default_highres.png)
