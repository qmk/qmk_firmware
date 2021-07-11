# plattfot's keymap for [Kyria](https://github.com/splitkb/kyria)

![Keyboard](https://i.imgur.com/mcefoHnh.jpg)

Designed to be ease of use when programming, typing in both English
and Swedish and navigating around in a tiling window manager, in my
case [sway](https://swaywm.org/). Uses the two rotary encoders (lower
left/right thumb row) as two palm buttons.

This keymap avoids [Mod-tap](https://docs.qmk.fm/#/mod_tap) as they do
not work for me. [Kyria](https://github.com/splitkb/kyria) has enough
thumb keys to make it work without them.

The symbols are split into two layers, one for each hand. Then the
layers are activated by the opposite thumb. Found that having all
symbols on one layer then have one thumb activate them made it awkward
to press keys with the index finger on the same hand.

Custom feature I call the close tap (Clotap) key, I based on a code
snippet from a
[reddit post](https://www.reddit.com/r/olkb/comments/citkbx/double_key_press_modifier_qmkwould_work_like/ev9cue8).
When pressed, it will insert the closing equivivalent key and press
`←` (left arrow). For example tapping Clotap then press `(` will
result in the keypresses `()←`, if pressing `"` will result in `""←`,
if pressing `)` will result in `)←(`. Really nice to have when
programming, it is editor agnostic and saves me two keypresses (need
to press NAV+j for `←`). It also removes the need for having specific
macros for these as I had before.


# Base Layer: Default
```
//  ,-------------------------------------------.                              ,-------------------------------------------.
//  |  Esc   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  Del   |
//  |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  |  Tab   |   A  |   S  |  D   |   F  |   G  |                              |   H  |   J  |   K  |   L  |   ;  |   '    |
//  |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  | LShift |   Z  |   X  |   C  |   V  |   B  | Lead | RAISE|  | LOWER|BSpace|   N  |   M  |   ,  |   .  |   /  | RShift |
//  `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//                         | MPlay| GUI  | LCtrl| Space| LALT |  | RCtrl| Enter| NAV  | RALT |Scroll|
//                         |      |      |      |      |      |  |      |      |      |      | Lock |
//                         `----------------------------------'  `----------------------------------'
```

Setup for using the
[EurKey](https://eurkey.steffen.bruentjen.eu/layout.html) layout. As
it's annoying to have to toggle us and swedish layout which shifts
symbols around.

AltGr is used to access the extra keys in the
[EurKey](https://eurkey.steffen.bruentjen.eu/layout.html) layout.

## Notable features on this layer

Left rotary encoder
- Press: play/pause
- Rotate: Volume control

Right rotary encoder
- Press: Scroll lock
- Rotate: Page up/Page down. Used mouse scrolling at first. But
          scrolling only works in the window where the mouse pointer
          is. Which kind of defeated the purpose of having the scroll
          on the keyboard, as I still needed to move my hand to the
          mouse and then I could just use the scroll on the mouse.

[Leader key](https://docs.qmk.fm/#/feature_leader_key) is mainly used
for jumping between workspaces. Otherwise I would need to use both
hands everytime I need to switch. With the leader key I can jump
between 1-5 with just the left hand.

# Lower Layer: Left symbols/Right function keys
```
//  ,-------------------------------------------.                              ,-------------------------------------------.
//  |        |  !   |  @   |  #   |  $   |  %   |                              |  F6  |  F7  |  F8  |  F9  | F10  |        |
//  |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  |        |  |   |  _   |  \   |  -   |  +   |                              | F12  |      |      |      |      |        |
//  |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  |        |  °   |  :   |  (   |  )   |  ×   |      |ADJUST|  |      |      |CLOTAP|      |      |      |      |        |
//  `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//                         |      |      |      |      |      |  |      |      |      |      |      |
//                         |      |      |      |      |      |  |      |      |      |      |      |
//                         `----------------------------------'  `----------------------------------'
```

Symbols for the left hand, function keys for the right hand.

I had the function keys at the bottom on the navigation layer. But it
was annoying when typing version strings. Hitting f1-5+f11 involved
both hands. And it turned out that my keybinding for closing a window
(Super+Shift+c) and rebooting my machine (Super+Shift+f3) ended up on
the same physical keys.

Splitting them up like this allows me to hit all the function keys
with just one hand and I wont accidentally reboot my machine when
trying to close a window.

## Notable features on this layer

Left rotary encoder
- Rotate: Skip next/previous song

Clotap on the right hand.

Has two Eurkey specific symbols `°` and `×` on the left hand.

# Raise Layer: Left function/Right symbols + state keys
```
//  ,-------------------------------------------.                              ,-------------------------------------------.
//  |        |  F1  |  F2  |  F3  |  F4  |  F5  |                              |   ^  |  &   |  *   |  ~   |  ?   |        |
//  |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  |        |      |      |      |      | F11  |                              |   =  |  {   |  }   |  [   |  ]   |   `    |
//  |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  |        |      |      |      |      |CLOTAP|      |      |  |ADJUST|      |   …  |  "   |  <   |  >   |  /   |CapsLock|
//  `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//                         | Mute |      |      |      |      |  |      |      |      |      |Insert|
//                         |      |      |      |      |      |  |      |      |      |      |      |
//                         `----------------------------------'  `----------------------------------'
```

Function keys for the left hand, symbols for the right hand. 

This layer also includes caps lock and insert.

## Notable features on this layer

Left rotary encoder
- Press: mute

Right rotary encoder
- Press: Toggle insert mode
- Rotate: Scrolling between workspaces in `sway`.

Clotap on the left hand.

# Navigation Layer: Number keys, navigation
```
 //
 // ,-------------------------------------------.                              ,-------------------------------------------.
 // |        |   1  |  2   |  3   |  4   |  5   |                              |  6   |  7   |  8   |  9   |  0   |        |
 // |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 // |        |      |      |      |      |      |                              |      | Left | Up   | Down | Right|        |
 // |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 // |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 // `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 //                        |      |      |      |      |      |  |      |      |      |      |      |
 //                        |      |      |      |      |      |  |      |      |      |      |      |
 //                        `----------------------------------'  `----------------------------------'
```

Access to the number and the arrow keys. Got use to the number row
after using [ErgoDox](https://www.ergodox.io/) keyboards for a few
years. Do not feel I need a numpad layer, which seems to be quite
common with small keyboards like this.

# Adjust Layer: RGB
```
 //
 // ,-------------------------------------------.                              ,-------------------------------------------.
 // |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 // |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 // |        | TOG  | SAI  | HUI  | VAI  | MOD  |                              |      |      |      |      |      |        |
 // |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 // |        |      | SAD  | HUD  | VAD  | RMOD |      |      |  |      |      |      |      |      |      |      |        |
 // `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 //                        |      |      |      |      |      |  |      |      |      |      |      |
 //                        |      |      |      |      |      |  |      |      |      |      |      |
 //                        `----------------------------------'  `----------------------------------'
```

Right now it only contains adjustment to the underglow. Activated by
holding down `RAISE` and `LOWER` at the same time.
