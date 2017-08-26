# Introduction

## Motivation
I created this keymap in an attempt to optimize my typing experience in text editors (vim and emacs) and the command-line.

More specifically, I wanted to have each modifier key controlled by the thumbs, the most powerful of the digits (I think). This cured me of emacs pinky, which had surprisingly grown quite quickly over the first two weeks of using emacs & emacs-like commands on the command-line.

## Changes
There are some miscellaneous changes that I kind of forgot I made, such as moving the tilde key, but you can check out the visual layouts below, which I **have** kept up to date.
### Modifier Keys
The biggest changes from the ergodox ez default keymap are the modifiers on the thumb cluster. You must hold each key down for a certain amount of time (forgot where this is specified) in order for the modifier key to activate.

### Layers
* an arrow layer (ARRW) has been created because the default arrow keys suck. Beware, these do use vim bindings because they're the best.
* the keys in the media layer have been moved around for a better experience (imo), especially with respect to the mouse
* the three layers (SYMB, MDIA, and ARRW) now have their own dedicated keys accessible by the thumbs in the basic layer
* caps lock has been put in place of the right-side `L1` toggle key because there was really no need to have two keys to toggle one layer, and caps lock is useful when writing queries
** unfortunatley, caps lock is not indicated by an LED, so be careful. I use caps lock just like I do insert in vim; for a short burst of text. I always turn off caps lock when I change my focus

### Removal Of Keys
I also removed a bunch of unnecessary keys that I wasn't going to use anyway. You'll see such keys are blank in the basic layer. I will probably add some more keys in place of these, but I'm fine for now; I just didn't want the distraction of extra keys I barely use.

## Caveats
### Thumb Cluster Range
I've heard many complaints about the thumb clusters. I agree that the three outter keys are almost impossible to reach. I am going to try to build [Matt Adereth's keyboard](https://github.com/adereth/dactyl-keyboard), which looks to have a better layout. However, I am able to comfortably use the three modifier keys mainly because:
* I use DCS keycaps with SA Row 3 keycaps where the Alt keys are
* I have relatively large hands (I guarantee you there's no problem - I guarantee you)

### Dangerous positioning
I think it's quite dangerous to put something like control on the same key as enter. Alas, this is a risk I'm willing to accept, and so should you if you decide to use this keymap. I tend to avoid putting myself in situtations in which disaster could occur with one fell swoop of a keypress.

# Keymap
## Keymap 0: Basic layer
```
,--------------------------------------------------. ,--------------------------------------------------.
|   =    |   1  |   2  |   3  |   4  |   5  |      | |      |   6  |   7  |   8  |   9  |   0  |   -    |
|--------+------+------+------+------+-------------| |------+------+------+------+------+------+--------|
| Tab    |   Q  |   W  |   E  |   R  |   T  |  L1  | | CAPS |   Y  |   U  |   I  |   O  |   P  |   \    |
|--------+------+------+------+------+------|      | |      |------+------+------+------+------+--------|
|  ESC   |   A  |   S  |   D  |   F  |   G  |------| |------|   H  |   J  |   K  |   L  |   ;  |   '    |
|--------+------+------+------+------+------| Hyper| | Meh  |------+------+------+------+------+--------|
| LShift |   Z  |   X  |   C  |   V  |   B  |      | |      |   N  |   M  |   ,  |   .  |   /  | RShift |
`--------+------+------+------+------+-------------' `-------------+------+------+------+------+--------'
  |      |  Grv |      |*SYMB*|*ARRW*|                             |*MDIA*|*SYMB*|   [  |  ]   |      |
  `----------------------------------'                             `----------------------------------'
                                   ,-------------.     ,-------------.
                                   |      |      |     |      |      |
                            ,------|------|------|     |------+--------+------.
                            |      |      |      |     |      |        |      |
                            | Space| Bksp |------|     |------|  Tab   |Enter |
                            | ctrl | gui  | Alt  |     | Alt  |  gui   | ctrl |
                            `--------------------'     `----------------------'

```

## Keymap 1: Symbol Layer
The only change here is the *dot* (`.`) character moving from next to `0` next to `+` in order to move the layer keys in the correct position
```
  ,--------------------------------------------------.           ,--------------------------------------------------.
  |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
  |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
  |        |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
  |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
  |        |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |   .    |
  |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
  |        |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
  `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
    |      |      |      |      |      |                                       |      |      |   0  |   =  |      |
    `----------------------------------'                                       `----------------------------------'
                                         ,-------------.       ,-------------.
                                         |      |      |       |      |      |
                                  ,------|------|------|       |------+------+------.
                                  |      |      |      |       |      |      |      |
                                  |      |      |------|       |------|      |      |
                                  |      |      |      |       |      |      |      |
                                  `--------------------'       `--------------------'
```

## Keymap 2: Arrow Layer
```
  ,--------------------------------------------------.           ,--------------------------------------------------.
  |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
  |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
  |        |      |      |      |      |      |      |           |      |      |PGDOWN| PGUP |      |      |        |
  |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
  |        |      |      |      |      |      |------|           |------| LEFT | DOWN |  UP  |RIGHT |      |        |
  |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
  |        |      |      |      |      |      |      |           |      |      | HOME | END  |      |      |        |
  `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
    |      |      |      |      |      |                                       |      |      |      |      |      |
    `----------------------------------'                                       `----------------------------------'
                                         ,-------------.       ,-------------.
                                         |      |      |       |      |      |
                                  ,------|------|------|       |------+------+------.
                                  |      |      |      |       |      |      |      |
                                  |      |      |------|       |------|      |      |
                                  |      |      |      |       |      |      |      |
                                  `--------------------'       `--------------------'
```

## Keymap 3: Media and mouse keys
``` 
  ,--------------------------------------------------.           ,--------------------------------------------------.
  |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
  |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
  |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
  |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
  |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      | Lclk | Rclk |      |      |        |
  |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
  |        |      |Mute  |VolDn | VolUp|      |      |           |      |      |      |      |      |      |        |
  `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
    |      |      | Prev | Play | Next |                                       |      |      |      |      |      |
    `----------------------------------'                                       `----------------------------------'
                                         ,-------------.       ,-------------.
                                         |      |      |       |      |      |
                                  ,------|------|------|       |------+------+------.
                                  |Brwser|      |      |       |      |      |      |
                                  |Back  |      |------|       |------|      |      |
                                  |      |      |      |       |      |      |      |
                                  `--------------------'       `--------------------'
```
