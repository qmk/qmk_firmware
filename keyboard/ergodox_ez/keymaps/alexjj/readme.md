Englishman in New York
===========================

:microphone: :tea:

About
------

After using the massdrop configurator to get the basics, I wanted to add a
little extra to my ergodox. Notably the Hyper hotkey, the press and hold,
and a way to have my beloved £ :pound: symbol available. Why not switch to a GB
layout? Well the computers I use are US keymap'd and I can't always change
that. Plus I've got used to 2/@ and 3/# and moving to the ergodox was hard
enough. :sweat_smile:

I started from the default and edited from there as I needed. It's somewhat
similar to a regular layout, particularly R1 and shift/controls. I ended up
with a few keys that were blank, so I'm testing out some shortcuts. Alt+F4 for
quitting things in Windows, is one example, but I felt it was better placed on 
the 1st layer - in case of fat fingers.

Layout
-------

![Layout](rl-layout.jpg "Isn't it lovely")

### Base Layer

```
,--------------------------------------------------.           ,--------------------------------------------------.
|   ESC  |  1!  |  2@  |  3#  |  4$  |  5%  |  6^  |           |  7&  |  8*  |  9(  |  0)  |  -_  |  +=  |  BkSp  |
|--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
| Tab    |   Q  |   W  |   E  |   R  |   T  |  {   |           |   }  |   Y  |   U  |   I  |   O  |   P  |  |\    |
|--------+------+------+------+------+------|  [   |           |   ]  |------+------+------+------+------+--------|
| Win    |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |  :;  |  '"    |
|--------+------+------+------+------+------| Home |           | End  |------+------+------+------+------+--------|
| LShift |Z/Alt |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |//Alt| RShift |
`--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
  |LCtrl |  `~  | Hyper| Left | Right|                                       | Down |  Up  | COPY | PASTE| RCtrl |
  `----------------------------------'                                       `----------------------------------'
                                       ,-------------.       ,-------------.
  Hyper = Ctrl+Super+Alt+Shift         | Alt  |  F5  |       |  F2  | ~L2  |
                                ,------|------|------|       |------+------+------.
                                |      |      | PgUp |       | Ins  |      |      |
                                | Space| BkSp |------|       |------| ~L1  |Enter |
                                |      |      | PgDn |       | Del  |      |      |
                                `--------------------'       `--------------------'
``` 

### Symbol Layer

```
,--------------------------------------------------.           ,--------------------------------------------------.
|        |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |PrintScr|
|--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
|        |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |        |
|--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
|        |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
|--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
|        |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
`--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
  |      |   £  |      |      |      |                                       |      |    . |   0  |   =  |Alt+F4|
  `----------------------------------'                                       `----------------------------------'
             ↑                         ,-------------.       ,-------------.
          THERE!                       |      |      |       |      |      |
                                ,------|------|------|       |------+------+------.
   CAD = Ctrl + Alt + Delete    |      |      |      |       |      |      |      |
                                |      |      |------|       |------|      |      |
                                |      |      |      |       | CAD  |      |      |
                                `--------------------'       `--------------------'
```
### Media Layer

Not touched this, not used either.

```
,--------------------------------------------------.           ,--------------------------------------------------.
| TEENSY |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
|--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
|        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
|--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
|        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
|--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
|        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
`--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
  |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
  `----------------------------------'                                       `----------------------------------'
                                       ,-------------.       ,-------------.
                                       |      |      |       |      |      |
                                ,------|------|------|       |------+------+------.
                                |      |      |      |       |      |      |Brwser|
                                |      |      |------|       |------|      |Back  |
                                |      |      |      |       |      |      |      |
                                `--------------------'       `--------------------'
```

Usage
------

~L1 / L2 will momentarily switch to a layer if held and another key is pressed.
If pressed and released will remain on layer until pressed again.


Changelog
-----------

### [0.1.1] - 2016-03-23

* Changed £ input to a macro


### [0.1.0] - 2016-03-22

After actually using the keyboard, I've made some changes:

* Swapped Enter and Space
* Moved backspace to thumb keys (top right still remains)
* Added Ctrl+Alt+Delete
* Added Teensy Reset on 2nd layer
* Switched Up and Down
* Changed copy/paste to be Ctrl+c and Ctrl+v as KC_COPY/PASTE didn't work (in Windows)
* Moved ~L2 to replace +L1 after learning how the function works (notes above)
* Hopefully fixed GBP symbol (unicode enabled in MakeFile)

### [0.0.1] - 2016-03-21

First version


Issues
-------

Space for feedback and notes for future improvements


