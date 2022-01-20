# chriskopher's QMK Config
Currently designed for the use of an ANSI tenkeyless keyboard on Windows 10. Although many of the ideas can be applied agnostically across operating systems.

## Hardware
- [Hasu USB to USB Controller Converter](https://www.1upkeyboards.com/shop/controllers/usb-to-usb-converter/)
    - Limitations include:
        - 6KRO
        - Media/System control keys and <kbd>Fn</kbd> key are not recognized by the converter
        - Max firmware size of 28K and a lot of it is taken up by the USB keyboard support, so not all QMK features can be enabled
        - No mouse or other pointing device support
- A regular ANSI QWERTY USB Type B keyboard

## Layer Overview
### Base Layers
#### 0. [My personal modified QWERTY layout](#chriskopher-qwerty-layout)
This is the default base layer that is used for most of my typing and where the intermediate layers are stacked onto. It is loaded by default on keyboard power up.
- Apply this base layer with <kbd>[Adjust](#adjust-layer)</kbd> + <kbd>c</kbd>, or by powering on the keyboard
- Swapped <kbd>CapsLock</kbd> and <kbd>LCtrl</kbd> for ergonomics with often performed <kbd>LCtrl</kbd> keyboard shortcuts
- Swapped <kbd>\\</kbd> and <kbd>Backspace</kbd> to minimize hand movement, inspired by the [HHKB](https://happyhackingkb.com/) layout
- Overloaded modifier keys, inspired by Steve Losh's [A Modern Space Cadet](https://stevelosh.com/blog/2012/10/a-modern-space-cadet/)
    - Tap <kbd>LShift</kbd> for <kbd>(</kbd>, hold for <kbd>LShift</kbd>
    - Tap <kbd>RShift</kbd> for <kbd>)</kbd>, hold for <kbd>RShift</kbd>
    - Tap <kbd>LCtrl</kbd> for <kbd>Esc</kbd>, hold for <kbd>LCtrl</kbd> (remember that <kbd>LCtrl</kbd> is swapped with <kbd>CapsLock</kbd>)
- Tap Dances that allow different functionality based on the number of key presses within the `TAPPING_TERM` of 200 ms
    - Extended space cadet shifting:
        - Two taps of <kbd>LShift</kbd> sends <kbd>{</kbd>, and three taps send <kbd>[</kbd>
        - Two taps of <kbd>RShift</kbd> sends <kbd>}</kbd>, and three taps send <kbd>]</kbd>
    - One tap of <kbd>;</kbd> will send <kbd>;</kbd>, two taps of <kbd>;</kbd> will send <kbd>:</kbd>
- Combos that allow for different functionality based on custom chorded key presses within the `COMBO_TERM` of 20 ms
    - Press and hold <kbd>s</kbd> and <kbd>d</kbd> to momentarily activate the <kbd>[(S)uper(D)uper](#superduper-layer)</kbd> layer
    - Press and hold <kbd>k</kbd> and <kbd>l</kbd> to momentarily activate <kbd>Meh</kbd> modifier key
        - <kbd>Meh</kbd> key (<kbd>Ctrl</kbd> + <kbd>Shift</kbd> + <kbd>Alt</kbd>) is useful for binding unique hotkeys on the OS that won't collide with or override other existing hotkeys
        - Tap <kbd>CapsLock</kbd> for <kbd>CapsLock</kbd>, hold <kbd>CapsLock</kbd> to momentarily activate <kbd>Meh</kbd> modifier key while held (remember that <kbd>LCtrl</kbd> is swapped with <kbd>CapsLock</kbd>)
- Tap/Hold actions for layer switching
    - Similar to the overloaded modifier keys
    - Tap <kbd>z</kbd> for <kbd>z</kbd>, hold <kbd>z</kbd> to momentarily activate <kbd>[Dev](#dev-layer)</kbd> layer while held
    - Tap <kbd>RGui</kbd> for <kbd>RGui</kbd>, hold <kbd>RGui</kbd> to momentarily activate <kbd>[Adjust](#adjust-layer)</kbd> layer while held

```
,---.   ,---------------. ,---------------. ,---------------. ,-----------.
|Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Pau|
`---'   `---------------' `---------------' `---------------' `-----------'
,-----------------------------------------------------------. ,-----------. ,---------------.
|  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|   \   | |Ins|Hom|PgU| |NmL|  /|  *|  -|
|-----------------------------------------------------------| |-----------| |---------------|
|Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  Bsp| |Del|End|PgD| |  7|  8|  9|   |
|-----------------------------------------------------------| `-----------' |-----------|   |
|Ctl/Esc|  A|  S|  D|  F|  G|  H|  J|  K| L|;/:| ' |  Return|               |  4|  5|  6|  +|
|-----------------------------------------------------------|     ,---.     |---------------|
|Shift/( |Dev/Z| X|  C|  V|  B|  N|  M|  ,|  .|  /|  Shift/)|     | ↑ |     |  1|  2|  3|   |
|-----------------------------------------------------------| ,-----------. |-----------|   |
|Meh/CapsL|Gui|Alt|     Space       |Alt|Adjust/Gui|App| Ctl| | ← | ↓ | → | |      0|  .|Ent|
`-----------------------------------------------------------' `-----------' `---------------'
```

Note: can't use <kbd>Hyper</kbd> key (<kbd>Ctrl</kbd> + <kbd>Shift</kbd> + <kbd>Alt</kbd> + <kbd>Gui</kbd>) instead of <kbd>Meh</kbd> reliably on Windows 10 because pressing <kbd>Hyper</kbd> opens Microsoft Office, <kbd>Hyper</kbd> + <kbd>t</kbd> opens Microsoft Teams, <kbd>Hyper</kbd> + <kbd>d</kbd> opens Microsoft OneDrive, <kbd>Hyper</kbd> + <kbd>y</kbd> Yammer, etc. And I couldn't find a clean way to disable this without needing to modify the host computer.

#### 1. [A regular QWERTY layout](#regular-qwerty-layout)
This layer is for when other people need to type on my keyboard.
- Apply this base layer with <kbd>[Adjust](#adjust-layer)</kbd> + <kbd>q</kbd>
- The only modification is the addition of the tap/hold action for switching back to the <kbd>[Adjust](#adjust-layer)</kbd> layer while held
    - Tap <kbd>RGui</kbd> for <kbd>RGui</kbd>, hold <kbd>RGui</kbd> to momentarily activate <kbd>[Adjust](#adjust-layer)</kbd> layer while held

```
,---.   ,---------------. ,---------------. ,---------------. ,-----------.
|Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Pau|
`---'   `---------------' `---------------' `---------------' `-----------'
,-----------------------------------------------------------. ,-----------. ,---------------.
|  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|    Bsp| |Ins|Hom|PgU| |NmL|  /|  *|  -|
|-----------------------------------------------------------| |-----------| |---------------|
|Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  | |Del|End|PgD| |  7|  8|  9|   |
|-----------------------------------------------------------| `-----------' |-----------|   |
|CapsL |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  Return|               |  4|  5|  6|  +|
|-----------------------------------------------------------|     ,---.     |---------------|
|Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shift     |     | ↑ |     |  1|  2|  3|   |
|-----------------------------------------------------------| ,-----------. |-----------|   |
|Ctl|Gui|Alt|           Space        |Alt|Adjust/Gui|App|Ctl| | ← | ↓ | → | |      0|  .|Ent|
`-----------------------------------------------------------' `-----------' `---------------'
```

### Intermediate Layers
#### 2. [(S)uper(D)uper Mode](#superduper-layer)
Inspired by [narze](https://github.com/qmk/qmk_firmware/tree/master/keyboards/planck/keymaps/narze) via [jasonrudolph](https://github.com/jasonrudolph/keyboard#super-duper-mode). It's designed to help with navigation while keeping you on the home row, or very close to it.

- To activate this layer, press <kbd>s</kbd> + <kbd>d</kbd> simultaneously and hold from the base layer
    - Alternatively, hold <kbd>/</kbd> to activate the layer. This method is slower because the layer toggle uses a `TAPPING_TERM` of 200 ms but <kbd>s</kbd> + <kbd>d</kbd> uses a `COMBO_TERM` of only 20 ms (can be changed within `config.h`).
- Use <kbd>h</kbd> / <kbd>j</kbd> / <kbd>k</kbd> / <kbd>l</kbd>
  for <kbd>←</kbd> / <kbd>↓</kbd> / <kbd>↑</kbd> / <kbd>→</kbd>, respectively
- Use <kbd>a</kbd> for <kbd>Alt</kbd>
- Use <kbd>f</kbd> for <kbd>Backspace</kbd>
- Use <kbd>g</kbd> for <kbd>Ctrl</kbd>
- Use <kbd>Space</kbd> for <kbd>Shift</kbd>
- Use <kbd>;</kbd> for <kbd>Delete</kbd>
- Use <kbd>i</kbd> / <kbd>o</kbd> to move to the previous/next tab
- Use <kbd>u</kbd> / <kbd>p</kbd> to go to the first/last tab (in most apps)
- Use <kbd>/</kbd> to toggle <kbd>[(S)uper(D)uper](#superduper-layer)</kbd> layer

```
,---.   ,---------------. ,---------------. ,---------------. ,-----------.
|   |   |   |   |   |   | |   |   |   |   | |   |   |   |   | |   |   |   |
`---'   `---------------' `---------------' `---------------' `-----------'
,-----------------------------------------------------------. ,-----------. ,---------------.
|   |   |   |   |   |   |   |   |   |   |   |   |   |       | |   |   |   | |   |   |   |   |
|-----------------------------------------------------------| |-----------| |---------------|
|     |   |   |   |   |   |   |1T |T← |T→ |9T |   |    |    | |   |   |   | |   |   |   |   |
|-----------------------------------------------------------| `-----------' |-----------|   |
|      |Alt|[SuperDuper]|Bksp|Ctl| ← | ↓ | ↑ | → |Del|   |  |               |   |   |   |   |
|-----------------------------------------------------------|     ,---.     |---------------|
|        |   |   |   |   |   |   |   |   |   |ToggleSD|     |     |   |     |   |   |   |   |
|-----------------------------------------------------------| ,-----------. |-----------|   |
|   |   |   |             Shift             |   |   |   |   | |   |   |   | |       |   |   |
`-----------------------------------------------------------' `-----------' `---------------'
```

#### 3. [Dev](#dev-layer)
This layer is for easy access to symbols commonly used during development.
- To activate this layer, press and hold <kbd>z</kbd> from the base layer
- Use <kbd>u</kbd> / <kbd>i</kbd> / <kbd>o</kbd> / <kbd>p</kbd>
  for <kbd>-</kbd> / <kbd>+</kbd> / <kbd>(</kbd> / <kbd>)</kbd>, respectively
- Use <kbd>h</kbd> / <kbd>j</kbd> / <kbd>k</kbd> / <kbd>l</kbd> / <kbd>;</kbd>
  for <kbd>_</kbd> / <kbd>[</kbd> / <kbd>]</kbd> / <kbd>{</kbd> / <kbd>}</kbd>, respectively
- Use <kbd>n</kbd> / <kbd>m</kbd> / <kbd>,</kbd> / <kbd>.</kbd> / <kbd>/</kbd>
  for <kbd>=</kbd> / <kbd>|</kbd> / <kbd><</kbd> / <kbd>></kbd> / <kbd>?</kbd>, respectively

```
,---.   ,---------------. ,---------------. ,---------------. ,-----------.
|   |   |   |   |   |   | |   |   |   |   | |   |   |   |   | |   |   |   |
`---'   `---------------' `---------------' `---------------' `-----------'
,-----------------------------------------------------------. ,-----------. ,---------------.
|   |   |   |   |   |   |   |   |   |   |   |   |   |       | |   |   |   | |   |   |   |   |
|-----------------------------------------------------------| |-----------| |---------------|
|     |   |   |   |   |   |   | - | + | ( | ) |   |   |     | |   |   |   | |   |   |   |   |
|-----------------------------------------------------------| `-----------' |-----------|   |
|      |   |   |   |   |   | _ | [ | ] | { | } |   |        |               |   |   |   |   |
|-----------------------------------------------------------|     ,---.     |---------------|
|        |   |   |   |   |   | = | | | < | > | ? |          |     |   |     |   |   |   |   |
|-----------------------------------------------------------| ,-----------. |-----------|   |
|   |   |   |                               |   |   |   |   | |   |   |   | |       |   |   |
`-----------------------------------------------------------' `-----------' `---------------'
```

### Top Layer
#### 4. [Adjust](#adjust-layer)
This layer is applied at the top so that it will override all other layers and as a result it will always be possible to change which base layer is applied as a default. It is also used for media controls.
- To activate this layer, press and hold <kbd>RGui</kbd> from the base layer
- Switch to [chriskopher modified QWERTY layout](#chriskopher-qwerty-layout) with <kbd>c</kbd>
- Switch to [regular QWERTY layout](#regular-qwerty-layout) with <kbd>q</kbd>
- Use <kbd>n</kbd> / <kbd>m</kbd> / <kbd>,</kbd> / <kbd>.</kbd> / <kbd>/</kbd>
  for <kbd>Play/Pause</kbd> / <kbd>Mute</kbd> / <kbd>Volume Down</kbd> / <kbd>Volume Up</kbd> / Toggle <kbd>[(S)uper(D)uper](#superduper-layer)</kbd> layer, respectively
- Use <kbd>Insert</kbd> / <kbd>Home</kbd> / <kbd>Page Up</kbd>
  for <kbd>Play/Pause</kbd> / <kbd>Next Track</kbd> / <kbd>Volume Up</kbd>, respectively
- Use <kbd>Delete</kbd> / <kbd>End</kbd> / <kbd>Page Down</kbd>
for <kbd>Stop</kbd> / <kbd>Previous Track</kbd> / <kbd>Volume Down</kbd>, respectively

```
,---.   ,---------------. ,---------------. ,---------------. ,-----------.
|   |   |   |   |   |   | |   |   |   |   | |   |   |   |   | |   |   |   |
`---'   `---------------' `---------------' `---------------' `-----------'
,-----------------------------------------------------------. ,--------------. ,---------------.
|   |   |   |   |   |   |   |   |   |   |   |   |   |       | |Play|Next|VolU| |   |   |   |   |
|-----------------------------------------------------------| |--------------| |---------------|
|     |QWERTY|   |   |   |   |   |   |   |   |   |   |  |   | |Stop|Prev|VolD| |   |   |   |   |
|-----------------------------------------------------------| `--------------' |-----------|   |
|      |   |   |   |   |   |   |   |   |   |   |   |        |                  |   |   |   |   |
|-----------------------------------------------------------|     ,---.        |---------------|
|        |   |   |CKO|   |   |  |Play|Mute|VolD|VolU| SD|   |     |   |        |   |   |   |   |
|-----------------------------------------------------------| ,-----------.    |-----------|   |
|   |   |   |                               |   |   |   |   | |   |   |   |    |       |   |   |
`-----------------------------------------------------------' `-----------'    `---------------'
```

## Build Instructions
To compile and flash the config onto the USB to USB converter:
```sh
cd /path/to/qmk_firmware
qmk config user.keyboard=converter/usb_usb/hasu
qmk config user.keymap=chriskopher
qmk compile
qmk flash
```

Alternatively:
```sh
cd /path/to/qmk_firmware
qmk compile -kb converter/usb_usb/hasu -km chriskopher
qmk flash -kb converter/usb_usb/hasu -km chriskopher
```

To modify the config:
```sh
cd /path/to/qmk_firmware/keyboards/converter/usb_usb/keymaps/chriskopher
```
and edit `keymap.c`, `config.h`, and `rules.mk`.
