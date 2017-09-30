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

- `CFQ_USER_KEY1`, `CFQ_USER_KEY2` are used for custom-keys
  if not set they default to F13, F14.
- `CFQ_USE_MOMENTARY_LAYER_KEYS` is used to prevent layer keys from toggling when tapped.
- `CFQ_USE_EXPEREMENTAL_LAYER` defines an extra layer for misc extra keys/macros.
  Currently it's mostly empty.
- `CFQ_USE_SWAP_RIGHT_SPACE_ENTER` swap Enter and Space on the right hand thumb cluster.
  While asymmetric, it makes Enter more easily accessible.



## Keymap 0: Basic layer

```
,--------------------------------------------------.           ,--------------------------------------------------.
| Grave  |   !  |   @  |   #  |   $  |   %  |   {  |           |  }   |   ^  |   &  |   *  |   -  |   =  | BSpace |
|--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
| Tab    |   Q  |   W  |   E  |   R  |   T  |   (  |           |  )   |   Y  |   U  |   I  |   O  |   P  |   \    |
|--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
| Esc    |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
|--------+------+------+------+------+------|   [  |           |  ]   |------+------+------+------+------+--------|
| LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
`--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
  | LCtl |Super | Alt  | Ins  |Space |                                       | Left | Down | Up   |Right | Del  |
  `----------------------------------'                                       `----------------------------------'
                                       ,-------------.       ,-------------.
                                       | USR2 | ~L3  |       | Home | End  |
                                ,------|------|------|       |------+------+------.
                                |      |      | ~L2  |       | PgUp |      |      |
                                |Space | USR1 |------|       |------|Enter |Space |
                                |      |      | ~L1  |       | PgDn |      |      |
                                `--------------------'       `--------------------'

```

## Keymap 1: Symbol layer

Note the double bracket keys on this layer press left to position the cursor between them.

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
                                       |      |      |       |      |        |
                                ,------|------|------|       |------+--------+------.
                                |      |      |      |       |      |        |      |
                                |      |      |------|       |------|        |      |
                                |      |      |      |       |      |        |      |
                                `--------------------'       `----------------------'
```

## Keymap 2: Media and mouse keys

```
,--------------------------------------------------.           ,--------------------------------------------------.
|        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
|--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
|        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
|--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
|        |      |MsLeft|MsDown|MsRght|      |------|           |------| Left | Down | Up   |Right |      |        |
|--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
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
