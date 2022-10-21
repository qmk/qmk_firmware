# jtojnar’s keymap for Kinesis Advantage2

## Keymap

This is based on the `default` layout, with a few modifications to better match my usage patterns.

### Default layer (QWERTY)

```
,-------------------------------------------------------------------------------------------------------------------.
| Esc    |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F8  |  F9  |  F10 |  F12 | PSCR | SCRL | PAUS |  FN0 |  BOOT  |
|--------+------+------+------+------+------+---------------------------+------+------+------+------+------+--------|
| =+     |  1!  |  2@  |  3#  |  4$  |  5%  |                           |  6^  |  7&  |  8*  |  9(  |  0)  | -_     |
|--------+------+------+------+------+------|                           +------+------+------+------+------+--------|
| Tab    |   Q  |   W  |   E  |   R  |   T  |                           |  Y   |  U   |  I   |  O   |  P   | \|     |
|--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
| Caps   |   A  |   S  |   D  |   F  |   G  |                           |  H   |  J   |  K   |  L   |  ;:  | '"     |
|--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
| Shift  |   Z  |   X  |   C  |   V  |   B  |                           |  N   |  M   |  ,.  |  .>  |  /?  | Shift  |
`--------+------+------+------+------+-------                           `------+------+------+------+------+--------'
         |  `~  | INS  | Left | Right|                                         |  Up  | Down |  [{  |  ]}  |
         `---------------------------'                                         `---------------------------'
                                       ,-------------.         ,-------------.
                                       | Ctrl | Alt  |         | Gui  |Alt Gr|
                                ,------|------|------|         |------+------+------.
                                |      |      | Home |         | PgUp |      |      |
                                | BkSp |  Del |------|         |------|Return| Space|
                                |      |      | End  |         | PgDn |      |      |
                                `--------------------'         `--------------------'
```

#### Changes compared to `default`

- Right <kbd>Super</kbd> in the right thumb cluster was changed to left <kbd>Super</kbd>, to allow opening Activities view in GNOME Shell.
- Right <kbd>Control</kbd> was replaced with <kbd>Alt Gr</kbd> to enable third and fourth key layers, useful to access English layout symbols on layouts for European languages.

## Setting up

Run

```
qmk config user.keyboard=kinesis/kint41
qmk config user.keymap=jtojnar
```

## Flashing keyboard

Run

```
nix-shell -I 'nixpkgs=channel:nixos-unstable' -p qmk --run 'qmk flash'
```

Then, after being asked, press <kbd>progm</kbd> key.
