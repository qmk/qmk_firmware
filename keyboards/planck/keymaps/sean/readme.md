# Sean Hunter's Planck Layout

## Main layout

Inspired by my old typematrix dvorak keyboard, with escape, tab, enter and
backspace in the middle.  

```
 ,-----------------------------------------------------------------------------------.
 |   "  |   ,  |   .  |   P  |   Y  |   /  |   =  |   F  |   G  |   C  |   R  |   L  |
 |------+------+------+------+------+------+------+------+------+------+------+------|
 |   A  |   O  |   E  |   U  |   I  | ESC  | BSPC |   D  |   H  |   T  |   N  |   S  |
 |------+------+------+------+------+------+------+------+------+------+------+------|
 |   ;  |   Q  |   J  |   K  |   X  | TAB  | ENT  |   B  |   M  |   W  |   V  |   Z  |
 |------+------+------+------+------+------+------+------+------+------+------+------|
 | Sft  | Ctl  | Alt  | Gui  |Lower |    Space    |Raise |   <  |   v  |   ^  |   >  |
 `-----------------------------------------------------------------------------------'
 ```

## Lower

With Lower, the numbers are on the home row.  Brackets and braces are down the
centre of the keyboard when holding lower, and most other special characters,
can be found on the row below home.  One row up are the main function keys.
The arrow keys become `Home`, `End` and `Page Up` and `Page Down`.

 ```
 ,-----------------------------------------------------------------------------------.
 | F1   |  F2  |  F3  |  F4  |  F5  |  {   |  }   |  F6  |  F7  |  F8  |  F9  | F10  | 
 |------+------+------+------+------+-------------+------+------+------+------+------|
 |  1   |   2  |   3  |   4  |   5  |  [   |  ]   |   6  |   7  |   8  |   9  |  0   |
 |------+------+------+------+------+------|------+------+------+------+------+------|
 |   ~  |   |  |   `  |   -  |   _  | INS  | DEL  |   (  |   )  |   +  |   =  |  \   |
 |------+------+------+------+------+------+------+------+------+------+------+------|
 | Sft  | Ctl  | Alt  | Gui  |Lower |             |Raise | Home | PgDn | PgUp | End  |
 `-----------------------------------------------------------------------------------'
```

## Raise

With Raise, the middle row functions as though we are holding shift and typing
numbers.  This makes it a little easier than trying to hold lower and shift at
the same time.  The row below home is a set of keys mapped from `Gui-1` to
`Gui-0`.  I use these to change virtual desktops on [i3](https://i3wm.org/).  I
also include 'right' versions of the modifier keys on here.


 ```
 ,-----------------------------------------------------------------------------------.
 | F11  |  F12 |  F13 |  F14 |  F15 |      |      |  F16 |  F17 |  F18 |  F19 | F20  | 
 |------+------+------+------+------+-------------+------+------+------+------+------|
 |  !   |   @  |   #  |   $  |   %  |Sleep | Wake |   ^  |   &  |   *  |   (  |  )   |
 |------+------+------+------+------+-------------+------+------+------+------+------|
 | GUI1 | GUI2 | GUI3 | GUI4 | GUI5 |      |      | GUI6 | GUI7 | GUI8 | GUI9 |GUI10 |
 |------+------+------+------+------+------+------+------+------+------+------+------|
 | Sft  | Ctl  | Alt  | Gui  |Lower |             |Raise | Gui  | Alt  | Ctl  | Sft  |
 `-----------------------------------------------------------------------------------'

```

## Adjust

Raise and lower at the same time give an adjustment layer, which allows
changing to the numpad and movement layer, and adjusting the backlights
(assuming you have them - I don't yet).  I have also added various media keys
and the all-important `Reset` key for programming the keyboard.  I've got the
ability to swap `Alt` and `Gui` in hardware and three special keys set up for
[hammerspoon]( http://www.hammerspoon.org/) on mac.  If I ever start using this
keyboard seriously on mac again (I'm using it mainly on Windows and Linux atm)
I'll write a special Mac mode and redo all my hammerspoon config to be more
like i3 on Linux.

```
 Adjust (Lower + Raise)
 ,-----------------------------------------------------------------------------------.
 |      | Reset|      |      |      |AGnorm|AGswap|      |      |HRevl |HReset|HMenu |
 |------+------+------+------+------+-------------+------+------+------+------+------|
 | PWR  | EJCT | CUT  | COPY |PASTE |PrScr |SysReq| CAPS | <<   |  >>  | Mute | Stop |
 |------+------+------+------+------+------|------+------+------+------+------+------|
 |DVORAK|NUMPAD| MVMT | SDRK |      |      |      |      | Next | Vol- | Vol+ | Play |
 |------+------+------+------+------+------+------+------+------+------+------+------|
 |Brite |BToggl|      |      |             |      |      | Gui  | Alt  | Ctl  | Sft  |
 `-----------------------------------------------------------------------------------'
```

## Numpad                                                                                                             

I have added a numpad, although this is a little annoying at the moment as you
have to first press `NumLock` to use.  I guess I could make a macro so as soon as
you go into numpad mode it turns `NumLock` on.

```
 ,-----------------------------------------------------------------------------------.
 |      |      |      |      |      |      |      |NumLck|   7  |   8  |   9  |   /  |
 |------+------+------+------+------+------+------+------+------+------+------+------|
 |      |      |      |      |      |      |      |Enter |   4  |   5  |   6  |   *  |
 |------+------+------+------+------+------+------+------+------+------+------+------|
 |DVORAK|NUMPAD| MVMT | SDRK |      |      |      |      |   3  |   2  |   1  |   -  |
 |------+------+------+------+------+-------------+------+------+------+------+------|
 |      |      |      |      |      |             |      |      |   0  |   .  |   +  |
 `-----------------------------------------------------------------------------------'
```

## Movement

I have added a movement layer but at present I seldom use it.

```
 ,-----------------------------------------------------------------------------------.
 |MsBut2|MsWhDn|MsWhUp|MsBut1|MsBut3|      |      |      | Home | PgDn | PgUp |  End |
 +------+------+------+------+------+------+------+------+------+------+------+------+
 |Ms Lft|Ms Dn |Ms Up |Ms Rht|      |      |      |      | Left | Down |  Up  | Right|
 |------+------+------+------+------+------+------+------+------+------+------+------|
 |DVORAK|NUMPAD| MVMT | SDRK |      |      |      |      |      |      |      |      |
 |------+------+------+------+------+-------------+------+------+------+------+------|
 | Sft  | Ctl  | Alt  | Gui  |      |             |      | Gui  | Alt  | Ctl  | Sft  |
 `-----------------------------------------------------------------------------------'
```

## Software Dvorak mode

I have implemented a version of the main, lower and raise maps that works if
the computer itself is in dvorak mode at the os level.  This allows me to work
well on my laptop when I have to take it with me (eg to go to a meeting) and
don't want the keyboard with me.  I simply set it in dvorak mode in the os and
then put the keyboard into this mode.

## TODO

1. Actually learn to use the media keys
