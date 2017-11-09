# ErgoDox EZ Code Friendly Qwerty Layout

- This layout aims to balance muscle memory from a typical QWERTY layout
  with having keys used for software development easily accessible.

- Arrow keys follow VIM convention (the media layer even uses arrow keys for HJKL).

- On the top row only symbols are used (not numbers),
  it's expected the symbol layer's number-pad layout will be used for numbers.

- Symbols match regular QWERTY.
  except for '()' which are grouped with other brackets.
  In their place -/= keys are placed, which almost matches a regular layout.

- Brackets are placed symmetrically along the center edges,
  if using keys from both sides is inconvenient - the symbol layer has macros
  at the same key locations to type matching pairs.

- The extra space-bar on the lower-left looks like it's in an obscure location,
  however using the larger thumb cluster ended up being more of a reach while typing.

- L3 is currently only used if `CFQ_USE_EXPEREMENTAL_LAYER` is defined,
  this is a layer to place extra functionality and test new keys.

## Configuration

Some optional behavior is configurable without editing the code
using `CFQ_` prefixed defines which can be set by passing `EXTRAFLAGS` to make.

- `CFQ_USER_KEY1` (1..7) are used for custom-keys
- `CFQ_USE_MOMENTARY_LAYER_KEYS` is used to prevent layer keys from toggling when tapped.
- `CFQ_USE_SWAP_RIGHT_SPACE_ENTER` swap Enter and Space on the right hand thumb cluster.
  While asymmetric, it makes Enter more easily accessible.
- `CFQ_USE_EXPEREMENTAL_LAYER` defines an extra layer for misc extra keys/macros.
  When set, Caps-Lock is replace by Layer3.
  Currently it's mostly empty.



## Keymap 0: Basic layer

```
Keymap 0: Basic layer
,--------------------------------------------------.           ,--------------------------------------------------.
| Grave  |   !  |   @  |   #  |   $  |   %  |   {  |           |  }   |   ^  |   &  |   *  |   -  |   =  | BSpace |
|--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
| Tab    |   Q  |   W  |   E  |   R  |   T  |   (  |           |  )   |   Y  |   U  |   I  |   O  |   P  |   \    |
|--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
| Esc    |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
|--------+------+------+------+------+------|   [  |           |  ]   |------+------+------+------+------+--------|
| LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
`--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
  | LCtl |Super | Alt  | ~L1  |Space |                                       | Left | Down | Up   |Right | Del  |
  `----------------------------------'                                       `----------------------------------'
                                       ,-------------.       ,-------------.
                                       | Ins  |CapsLk|       | Home | End  |
                                ,------|------|------|       |------+------+------.
                                |      |      | ~L2  |       | PgUp |      |      |
                                |Space |Enter |------|       |------|Enter |Space |
                                |      |      | ~L1  |       | PgDn |      |      |
                                `--------------------'       `--------------------'

Optional overrides: see CFQ_USER_KEY# defines

  -------+------+------+------+------+
  |      |      |      | USR1 |      |
  `----------------------------------'

                                       ,-------------.
                                       | USR2 | USR3 |
                                ,------|------|------|
                                |      |      | USR6 |
                                | USR4 | USR5 |------|
                                |      |      | USR7 |
                                `--------------------'
```

## Keymap 1: Symbol layer

Notes:

- The double bracket keys on this layer press left to position the cursor between them.
- The left thumb cluster is used for macro record/replay.

```
,--------------------------------------------------.           ,--------------------------------------------------.
|        |  F1  |  F2  |  F3  |  F4  |  F5  |  {}  |           |  }{  |  F6  |  F7  |  F8  |  F9  |  F10 |        |
|--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
|        |      |      |      |      |  =>  |  ()  |           |  )(  |  <=  |   7  |   8  |   9  |   \  |   F11  |
|--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
|        |      |      |      |      |  ->  |------|           |------|  <-  |   4  |   5  |   6  |   *  |   F12  |
|--------+------+------+------+------+------|  []  |           |  ][  |------+------+------+------+------+--------|
|        |      |      |      |      |  <>  |      |           |      |  ><  |   1  |   2  |   3  |   -  |        |
`--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
  |      |      |      |      |      |                                       |   0  |      |   .  |   +  |      |
  `----------------------------------'                                       `----------------------------------'
                                       ,-------------.       ,---------------.
                                       |Start1|Start2|       |      |        |
                                ,------|------|------|       |------+--------+------.
                                |      |      | Stop |       |      |        |      |
                                |Play1 |Play2 |------|       |------|        |      |
                                |      |      |      |       |      |        |      |
                                `--------------------'       `----------------------'
```

## Keymap 2: Media and mouse keys

```
,--------------------------------------------------.           ,--------------------------------------------------.
|        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
|--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
|        |      |      | MsUp |      |      |MWhlUp|           |      |      |      |      |      |      |        |
|--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
|        |      |MsLeft|MsDown|MsRght|      |------|           |------| Left | Down | Up   |Right |      |        |
|--------+------+------+------+------+------|MWhlDn|           |      |------+------+------+------+------+--------|
|        |      | Rclk | Mclk | Lclk |      |      |           |      |      |      |      |      |      |        |
`--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
  |      |      |      |      |      |                                       |      |      |      |      |      |
  `----------------------------------'                                       `----------------------------------'
                                       ,-------------.       ,-------------.
                                       | MRwd | MFwd |       | MPrv | MNxt |
                                ,------|------|------|       |------+------+------.
                                |      |      |      |       |VolUp |      |      |
                                |      |      |------|       |------| Mute | Play |
                                |      |      |      |       |VolDn |      |      |
                                `--------------------'       `--------------------'
```

## Changelog

- 2017/11/09
  Use Caps-Lock when `CFQ_USE_EXPEREMENTAL_LAYER` isn't defined.

- 2017/11/07
  Make thumb left thumb cluster completely configurable with defines.
  Add mouse wheel to mouse layer.

- 2017/10/28
  Make more keys user defined on the left thumb cluster.
  Add macro record/replay keys.

- 2017/10/04
  Move Insert key to the left thumb cluster (away from the modifier keys).
  Replace with `USR2` which defaults to `APP`.
