# TypeMatrix™ 2030 inspired layout

This is a [TypeMatrix™ 2030](http://typematrix.com/2030/features.php) inspired layout for the ErgoDox EZ. The _TypeMatrix_ is a nice small ergonomic keyboard with a matrix layout, and it provides several nice features like `enter`, `backspace` and `delete` at the center, bigger `shift` keys and international `cut`, `copy` and `paste` keys.

The idea in this ErgoDox layout is to make it is as close as possible to the TM2030, such that it would be easy to switch between the TM and the ErgoDox. No _fancy_ features have been implemented, as this is intended to be a base for further customization if desired. Some keys have been duplicated in order to accomodate for most people.

Most of the TM2030 features are supported except
* automatic window switching (alt-tab key, at the left of the space key)
* show desktop key (at the right of the space key)
* 102/106 modes

Dvorak mode is even supported by pressing [`Magic`](/docs/feature_bootmagic.md)+`1` (`Magic` is by default `LShift`+`RShift`)

Some keys had to be moved around to fit into the ErgoDox, especially the `F1`-`F12` keys and the arrow keys.

## Base Layer
This is the default layer, close to the TM with the following differences:

 - Top row (with the `F`-keys) and rightmost column (with application shortcuts) are removed, the corresponding keys are displaced elsewhere.
 - Bottom-left keys are reorganized on a single row as: `Ctrl`, `fn`, `Gui`, `Play`, `App`/`Alt`.
 - `shuffle` and `desktop` are not supported.
 - `right-shift` is moved on `'`, `\` and on the right thumb (the latter is actually the only _true_ `right-shift`, and must be used in the `Magic` key combination).
 - `right-ctrl` is moved on `End`.
 - `]` is moved in place of the dash (`-`).
 - Dash (`-`) and `=` are moved on bottom right row.
 - Arrows and `PgUp`/`PgDn` are moved on the thumbs.

```
,--------------------------------------------------.           ,--------------------------------------------------.
|   `    |   1  |   2  |   3  |   4  |   5  | Del  |           | Del  |   6  |   7  |   8  |   9  |   0  |   ]    |
|--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
| Tab    |   Q  |   W  |   E  |   R  |   T  |Backsp|           |Backsp|   Y  |   U  |   I  |   O  |   P  |   [    |
|--------+------+------+------+------+------|ace   |           |ace   |------+------+------+------+------+--------|
| LShift |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  | '/Shift|
|--------+------+------+------+------+------|Enter |           |Enter |------+------+------+------+------+--------|
| LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | \/Shift|
`--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
  |LCtrl |  fn  | LGui | Play |App/Alt|                                      | RAlt |   -  | Home |   =  |End/Ctl|
  `-----------------------------------'                                      `-----------------------------------'
                                      ,--------------.       ,-------------.
                                      |Esc/Alt| num  |       | Left |Right |
                               ,------+-------+------|       |------+------+------.
                               |      |       | PgUp |       |  Up  |      |      |
                               |Space |LShift |------|       |------|RShift|Space |
                               |      |       | PgDn |       | Down |      |      |
                               `---------------------'       `--------------------'
```

### Layer Switching
- Use `num` to toggle the Numeric Layer.
- Hold `fn` to temporarily activate the Numeric & Fn Layers.

As on the original TM 2030, when `num` layer is activated, holding `fn` disables it but enables the other `fn` keys.

## Dvorak Layer
Same as Layer 0 but with _Dvorak_ layout, to use with QWERTY OS layout.

Enable Dvorak layout with [`Magic`](/TMK_readme.md#magic-commands)+`1` (`LShift`+`RShift`+`1`), disable with `Magic`-`0`.

The middle (green) led indicates when the Dvorak layer is activated.

    ,--------------------------------------------------.           ,--------------------------------------------------.
    |   `    |   1  |   2  |   3  |   4  |   5  | Del  |           | Del  |   6  |   7  |   8  |   9  |   0  |   =    |
    |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
    | Tab    |   '  |   ,  |   .  |   P  |   Y  |Backsp|           |Backsp|   F  |   G  |   C  |   R  |   L  |   /    |
    |--------+------+------+------+------+------|ace   |           |ace   |------+------+------+------+------+--------|
    | LShift |   A  |   O  |   E  |   U  |   I  |------|           |------|   D  |   H  |   T  |   N  |   S  | -/Shift|
    |--------+------+------+------+------+------|Enter |           |Enter |------+------+------+------+------+--------|
    | LShift |   ;  |   Q  |   J  |   K  |   X  |      |           |      |   B  |   M  |   W  |   V  |   Z  | \/Shift|
    `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
      |LCtrl |  fn  | LGui | Play |App/Alt|                                      | RAlt |   [  | Home |   ]  |End/Ctl|
      `-----------------------------------'                                      `-----------------------------------'
                                          ,--------------.       ,-------------.
                                          |Esc/Alt| num  |       | Left |Right |
                                   ,------+-------+------|       |------+------+------.
                                   |      |       | PgUp |       |  Up  |      |      |
                                   |Space |LShift |------|       |------|RShift|Space |
                                   |      |       | PgDn |       | Down |      |      |
                                   `---------------------'       `--------------------'

## Numeric Layer
Numeric layer close to the TM when toggling `num`, with the following differences:

- Numpad is displaced by 1 to the top left.
- Arrows are displaced by 1 to the left.
- Provides access to `F1`-`F12`, `caps-lock` and `num-lock`.

The numeric layer is indicated with the left (red) led. Caps-lock is indicated with the right (blue) led.

    ,--------------------------------------------------.           ,--------------------------------------------------.
    |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |      |      |  Tab |   /  |   *  |   -    |
    |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
    |        |  F6  |  F7  |  F8  |  F9  |  F10 |      |           |      |      | Home |   7  |   8  |   9  |   +    |
    |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
    |        |  F11 |  F12 |      |      |      |------|           |------|  Up  | End  |   4  |   5  |   6  |   +    |
    |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
    |        |      |      |      |      |      |      |           | Left | Down | Right|   1  |   2  |   3  |KpEnter |
    `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
      |      |      |      |      |      |                                       |      |   0  |  00  |   .  |Etr/Ctl|
      `----------------------------------'                                       `-----------------------------------'
                                           ,-------------.       ,-------------.
                                           |      |      |       |n.lock|c.lock|
                                    ,------|------|------|       |------+------+------.
                                    |      |      |      |       |      |      |      |
                                    |      |      |------|       |------|      |      |
                                    |      |      |      |       |      |      |      |
                                    `--------------------'       `--------------------'

## Fn Layer
Activated simultaneously with the Numeric layer when holding the `fn` key. As on the TM, it provides access to the following features:
- `cut`, `copy` and `paste`
- `volume up`, `volume down` and `mute` — as opposed to the TM, these are only on left hand
- `previous track` and `next track`
- `calculator`, `mail` and `browser home`
- `insert`, `power`, `sleep`, `wake`, `print screen`, `scroll-lock` and `pause`

Note: the `eject` key does not work due to jackhumbert/qmk_firmware#82

    ,--------------------------------------------------.           ,--------------------------------------------------.
    |        |      |      |      |      |      |Insert|           |Insert|Eject |Power |Sleep | Wake |PrtScr|ScrollLk|
    |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
    |        |      |      |      |      |      |VolUp |           |      |      |      |      |      |      | Pause  |
    |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
    |        |      |      | Calc | Mail |Browsr|------|           |------|      |      |      |      |      |        |
    |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
    |        |      | cut  | copy |paste | Mute |VolDn |           |      |      |      |      |      |      |        |
    `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
      |      |      |      |      |      |                                       |      |      |      |      |      |
      `----------------------------------'                                       `----------------------------------'
                                           ,-------------.       ,-------------.
                                           |      |      |       |      |      |
                                    ,------|------|------|       |------+------+------.
                                    |      |      |      |       | Next |      |      |
                                    | Mute |      |------|       |------|      |      |
                                    |      |      |      |       | Prev |      |      |
                                    `--------------------'       `--------------------'
