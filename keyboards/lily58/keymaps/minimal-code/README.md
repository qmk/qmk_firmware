# Lily58 Minimal Code Friendly Layout

- This layout aims to balance muscle memory from a typical QWERTY layout
  while having all the keys used for software development at the first layer only.
- The [debounce algorithm](https://docs.qmk.fm/#/feature_debounce_type?id=types-of-debounce-algorithms) is set to
Assymetric Eager per Key with 5 ms debounce time
- Features only one extra toggled layer with F keys, arrows and media keys
- Arrow and media keys follow VIM convention.
- The OLED screen shows the current layer and the keymap name in both screens
- The keylogger functionality has been disabled for security reasons

## Base Layer

```
  ,-----------------------------------------.                    ,-----------------------------------------.
  |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |BackSP|
  |------+------+------+------+------+------|                    |------+------+------+------+------+------|
  | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  \   |
  |------+------+------+------+------+------|                    |------+------+------+------+------+------|
  | Esc  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |   '  |
  |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
  |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |Delete|
  `-----------------------------------------/       /     \      \-----------------------------------------'
                    | LCtl | LGUI | LAlt | /Space  /       \Enter \  |LOWER |  _   |  =   |
                    |      |      |      |/       /         \      \ |      |      |      |
                    `----------------------------'           '------''--------------------'
```

## Lower Layer

```
 ,-----------------------------------------.                    ,-----------------------------------------.
 |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 |      |      |      |      |      |      |-------.    ,-------| Left | Down |  Up  | Right|      |      |
 |------+------+------+------+------+------|       |    | Play  |------+------+------+------+------+------|
 |      |      |      |      |      |      |-------|    |-------| Prev | VolDn| VolUp| Next |      |      |
 `-----------------------------------------/       /     \      \-----------------------------------------'
                   |      |      |      | /       /       \      \  |      |      |      |
                   |      |      |      |/       /         \      \ |      |      |      |
                   `----------------------------'           '------''--------------------'
```
