# ErgoDox EZ Code Friendly Qwerty Layout

- This layout aims to balance muscle memory from a typical QWERTY layout
  with having keys used for software development easily accessible.

  The this layout is a normalized qwerty,
  with some configurable keys left thumb cluster so you can use it more as needed.

- Arrow keys follow VIM convention.

- On the top row only symbols are used (not numbers),
  it's expected the symbol layer's number-pad layout will be used for numbers.

- Symbols match regular QWERTY.
  except for '()' which are grouped with other brackets.
  In their place -/= keys are placed, which almost matches a regular layout.

- Brackets are placed symmetrically along the center edges,
  if using keys from both sides is inconvenient - the symbol layer has macros
  at the same key locations to type matching pairs.

- The space-bar on the lower-left looks like it's in an obscure location,
  however using the larger thumb cluster
  ended up being more of a reach while typing.

## Configuration

Some optional behavior is configurable without editing the code
using `CFQ_` prefixed defines which can be set by passing `EXTRAFLAGS` to make.

- `CFQ_USER_KEY0`
  (0..8) are used for custom-keys
- `CFQ_USE_MOMENTARY_LAYER_KEYS`
  is used to prevent layer keys from toggling when tapped.
- `CFQ_USE_SHIFT_QUOTES`
  an optional handy shortcut for writing quotes that inserts the
  cursor between the quotation marks.

  Holding LShift, then RShift types: "" (then presses left).

  Holding RShift, then LShift types: '' (then presses left).

- `CFQ_WORD_[A-Z]`
  defines can bind a key to an entire user defined word.

- `CFQ_USE_80_KEYS`
  enables 80 key layout, none of the extra keys are bound,
  they need to be set with defines: `CFQ_USER_K80_L0K0` .. `CFQ_USER_K80_L3K4`.
  Where `L#` is the layer and `K#` is the key.


## Keymap 0: Basic layer

```
.--------------------------------------------------.  .--------------------------------------------------.
| Grave  |   !  |   @  |   #  |   $  |   %  |   {  |  |  }   |   ^  |   &  |   *  |   -  |   =  | BSpace |
|--------+------+------+------+------+------+------|  |------+------+------+------+------+------+--------|
| Tab    |   Q  |   W  |   E  |   R  |   T  |   (  |  |  )   |   Y  |   U  |   I  |   O  |   P  |   \    |
|--------+------+------+------+------+------|      |  |      |------+------+------+------+------+--------|
| Esc    |   A  |   S  |   D  |   F  |   G  |------|  |------|   H  |   J  |   K  |   L  |   ;  |   '    |
|--------+------+------+------+------+------|   [  |  |  ]   |------+------+------+------+------+--------|
| LShift |   Z  |   X  |   C  |   V  |   B  |      |  |      |   N  |   M  |   ,  |   .  |   /  | RShift |
'--------+------+------+------+------+-------------'  '-------------+------+------+------+------+--------'
  | LCtl |Super | Alt  | App  | Menu |                              | Left | Down | Up   |Right | Del  |
  '----------------------------------'                              '----------------------------------'
                                     .-------------.  .-------------.
                                     |BSpace| Del  |  | Home | End  |
                              .------+------+------|  |------+------+------.
                              |      |      |CapsLk|  | PgUp |      |      |
                              |Space | ~L1  |------|  |------| ~L2  |Enter |
                              |      |      |Insert|  | PgDn |      |      |
                              '--------------------'  '--------------------'

Optional overrides: see CFQ_USER_KEY# defines.

.--------------------------------------------------.  .--------------------------------------------------.
|        |      |      |      |      |      |      |  |      |      |      |      |      |      | USR9   |
|--------+------+------+------+------+------+------|  |------+------+------+------+------+------+--------|
|        |      |      |      |      |      |      |  |      |      |      |      |      |      |        |
|--------+------+------+------+------+------|      |  |      |------+------+------+------+------+--------|
|        |      |      |      |      |      |------|  |------|      |      |      |      |      |        |
|--------+------+------+------+------+------|      |  |      |------+------+------+------+------+--------|
|        |      |      |      |      |      |      |  |      |      |      |      |      |      |        |
'--------+------+------+------+------+-------------'  '-------------+------+------+------+------+--------'
  |      |      |      | USR0 | USR1 |                              |      |      |      |      | USR8 |
  '----------------------------------'                              '----------------------------------'
                                     .-------------.  .-------------.
                                     | USR2 | USR3 |  |      |      |
                              .------+------+------|  |------+------+------.
                              |      |      | USR6 |  |      |      |      |
                              | USR4 | USR5 |------|  |------|      |      |
                              |      |      | USR7 |  |      |      |      |
                              '--------------------'  '--------------------'
```

## Keymap 1: KeyPad, Bracket Pairs & Macro Record

Notes:

- The double bracket keys on this layer press left to position the cursor between them.
- The left thumb cluster is used for macro record/replay.

```
.--------------------------------------------------.  .--------------------------------------------------.
|        |      |      |      |      |      |  {}  |  |  }{  |      |NumLck|   /  |   *  |   -  |        |
|--------+------+------+------+------+------+------|  |------+------+------+------+------+------+--------|
|        |      |      |      |      |  =>  |  ()  |  |  )(  |  <=  |   7  |   8  |   9  |   +  |        |
|--------+------+------+------+------+------|      |  |      |------+------+------+------+------+--------|
|        |      |      |      |      |  ->  |------|  |------|  <-  |   4  |   5  |   6  |   +  |        |
|--------+------+------+------+------+------|  []  |  |  ][  |------+------+------+------+------+--------|
|        |      |      |      |      |  <>  |      |  |      |  ><  |   1  |   2  |   3  | Enter|        |
'--------+------+------+------+------+-------------'  '-------------+------+------+------+------+--------'
  |      |      |      |      |      |                              |   0  |      |   .  | Enter|      |
  '----------------------------------'                              '----------------------------------'
                                     .-------------.  .-------------.
                                     |Start1|Start2|  |      |      |
                              .------+------+------|  |------+------+------.
                              |      |      |Play1 |  |      |      |      |
                              | Stop |      |------|  |------|      |      |
                              |      |      |Play2 |  |      |      |      |
                              '--------------------'  '--------------------'
```

## Keymap 2: F-Keys, Media & Mouse Keys

```
.--------------------------------------------------.  .--------------------------------------------------.
|        |      |      |      |      |      |      |  | Mute |      |  F10 |  F11 |  F12 |      |        |
|--------+------+------+------+------+------+------|  |------+------+------+------+------+------+--------|
|        |      |      | MsUp |      |      |MWhlUp|  |VolUp |      |  F7  |  F8  |  F9  |      |        |
|--------+------+------+------+------+------|      |  |      |------+------+------+------+------+--------|
|        |      |MsLeft|MsDown|MsRght|      |------|  |------|      |  F4  |  F5  |  F6  |      |        |
|--------+------+------+------+------+------|MWhlDn|  |VolDn |------+------+------+------+------+--------|
|        |      | Rclk | Mclk | Lclk |      |      |  |      |      |  F1  |  F2  |  F3  |      |        |
'--------+------+------+------+------+-------------'  '-------------+------+------+------+------+--------'
  |      |      |      |      |      |                              |      |      |      |      |      |
  '----------------------------------'                              '----------------------------------'
                                     .-------------.  .-------------.
                                     |      |      |  | MRwd | MFwd |
                              .------+------+------|  |------+------+------.
                              |      |      |      |  | MPrv |      |      |
                              |      |      |------|  |------|      | Play |
                              |      |      |      |  | MNxt |      |      |
                              '--------------------'  '--------------------'
```

## Keymap 3: User Defined Words & Numbers

Activate by holding L1 & L2.

This is for assigning whole words to single keys.
You can define the arguments (which must be quoted) using: `CFQ_WORD_[A-Z]`
eg: `-DCFQ_WORD_E=\"my@email.com\"`

Notes:

- Numbers are included on this layer since some applications differentiate
  between numbers top row and keypad.

```
.--------------------------------------------------.  .--------------------------------------------------.
|        |   1  |   2  |   3  |   4  |   5  |      |  |      |   6  |   7  |   8  |   9  |   0  |        |
|--------+------+------+------+------+------+------|  |------+------+------+------+------+------+--------|
|        |   Q  |   W  |   E  |   R  |   T  |      |  |      |   Y  |   U  |   I  |   O  |   P  |        |
|--------+------+------+------+------+------|      |  |      |------+------+------+------+------+--------|
|        |   A  |   S  |   D  |   F  |   G  |------|  |------|   H  |   J  |   K  |   L  |      |        |
|--------+------+------+------+------+------|      |  |      |------+------+------+------+------+--------|
|        |   Z  |   X  |   C  |   V  |   B  |      |  |      |   N  |   M  |      |      |      |        |
'--------+------+------+------+------+-------------'  '-------------+------+------+------+------+--------'
  |      |      |      |      |      |                              |      |      |      |      |      |
  '----------------------------------'                              '----------------------------------'
                                     .-------------.  .-------------.
                                     |      |      |  |      |      |
                              .------+------+------|  |------+------+------.
                              |      |      |      |  |      |      |      |
                              |      |      |------|  |------|      |      |
                              |      |      |      |  |      |      |      |
                              '--------------------'  '--------------------'
```

## Changelog

- 2019/11/20
  Move space to thumb cluster
  Make L1 and L2 symmetrical.
  Activate L3 by holding L1 & L2.
  Add App & Menu keys.

- 2018/10/19
  Move F-Keys to key-pad like layout.

- 2018/05/29
  Add number keys for cases when keypad numbers are handled differently.

- 2018/05/19
  Move all media keys to right thumb cluster
  (matching page up/down, home/end locations).

- 2018/04/14
  Add `CFQ_USE_80_KEYS` to optionally support an 80 key layout.

- 2018/03/08
  Add `CFQ_USE_SHIFT_QUOTES` option.
  Add `CFQ_USER_KEY8` key.

  When holding shift `CFQ_WORD_[A-Z]` use title caps.

- 2018/03/06
  Add layer for user defined words (replaces `CFQ_USE_EXPEREMENTAL_LAYER`).

  Minor changes to thumb cluster.

  Move backspace to left thumb, optionally remap the top right backspace.

  Make keypad layout match a typical numpad.

  Move F-Keys to layer 3.

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
