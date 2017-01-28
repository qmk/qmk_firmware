# smt's Preonic keymap

This keymap is primarily based on the default Preonic keymap, which in turn is derived from Planck's default.

Notable differences from the default are:

1. **Dvorak by default**

    I happen to type in Dvorak, and prefer that layer to be the default on my keyboard. This is easy enough to switch around with Qwerty, Colemak, or whatever.

2. **Right Shift**

    I use both the left and right shift keys when I type. When I want to modify a key with shift, I hold shift with the hand opposite the one typing the key. In the default keymap, Enter is where shift would be on a standard keyboard layout. Oh, muscle memory.

    Thankfully, QMK supports [mod-tap](https://github.com/qmk/qmk_firmware/wiki#fun-with-modifier-keys) keys, and this allows me to set the Enter key to send a modifier (MOD_LSFT) when held, and KC_ENT when tapped. Awesome!

## Dvorak (default)

```
,-----------------------------------------------------------------------------------.
|   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
|------+------+------+------+------+------+------+------+------+------+------+------|
| Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  |  /   |
|------+------+------+------+------+-------------+------+------+------+------+------|
| Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  -   |
|------+------+------+------+------+------|------+------+------+------+------+------|
| Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
|------+------+------+------+------+------+------+------+------+------+------+------|
| Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
`-----------------------------------------------------------------------------------'
```

## Qwerty (same as default)

```
,-----------------------------------------------------------------------------------.
|   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
|------+------+------+------+------+------+------+------+------+------+------+------|
| Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del  |
|------+------+------+------+------+-------------+------+------+------+------+------|
| Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
|------+------+------+------+------+------|------+------+------+------+------+------|
| Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
|------+------+------+------+------+------+------+------+------+------+------+------|
| Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
`-----------------------------------------------------------------------------------'
```

## Lower

This is where I put the number row, a numpad cluster, function keys, and some light navigation via Home/End/PageUp/PageDn. Like the "Raise" layer, the top row is redundant to help with Planck compatibility.

```
,-----------------------------------------------------------------------------------.
|   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
|------+------+------+------+------+------+------+------+------+------+------+------|
|   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
|------+------+------+------+------+-------------+------+------+------+------+------|
|      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   4  |   5  |   6  | Home |PageUp|
|------+------+------+------+------+------|------+------+------+------+------+------|
|      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |   1  |   2  |   3  | End  |PageDn|
|------+------+------+------+------+------+------+------+------+------+------+------|
|      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
`-----------------------------------------------------------------------------------'
```

## Raise

As a developer, it makes the most sense for me to group all the commonly-used symbols that don't fit on the main layer. In particular, having the dual-column of parens-braces-brackets really helps a lot.

I haven't completely filled this layer, which leaves room for future mappings and macros.

```
,-----------------------------------------------------------------------------------.
|   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
|------+------+------+------+------+-------------+------+------+------+------+------|
|   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
|------+------+------+------+------+-------------+------+------+------+------+------|
|      |      |      |      |      |      |      |   _  |   +  |   {  |   }  |  |   |
|------+------+------+------+------+------|------+------+------+------+------+------|
|      |      |      |      |      |      |      |   -  |   =  |   [  |   ]  |  \   |
|------+------+------+------+------+------+------+------+------+------+------+------|
|      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
`-----------------------------------------------------------------------------------'
```
