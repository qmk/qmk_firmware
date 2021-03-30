# smt's Planck keymap

This keymap is primarily based on the default Planck keymap.

Notable differences from the default are:

- **[Mod-Tap](https://github.com/jackhumbert/qmk_firmware/wiki#fun-with-modifier-keys) keys**

    - `Esc/Ctrl`

        I am experimenting with using Left Shift as a mod-tap key for Escape, similar to how I use the Enter key. It's set up like this on my Minivan, so in the interest of consistency...

    - `Enter/Shift`

        I use both the left and right shift keys when I type. When I want to modify a key with shift, I hold shift with the hand opposite the one typing the key. In the default keymap, Enter is where shift would be on a standard keyboard layout. Oh, muscle memory.

    - `Tab/Hyper` (Super+Ctrl+Shift+Alt)

        It's great to be able to use Tab as a custom modifier key. I tend to use [Hyper](http://brettterpstra.com/2012/12/08/a-useful-caps-lock-key/) commands for various OS-specific operations depending on what machine I'm working on.

    - `Backtick/Meh` (Ctrl+Shift+Alt)

        Why use backtick in the lower left corner? I use it as my tmux prefix key, so I need to type it more frequently than most people. Putting it on the base layer works well for me. The "Meh" mapping is just a less-cool "Hyper"; the same, just without Super.

- **Swapped responsibilities of "lower" and "raise" layers**

    I prefer to use symbols via the "raise" layer, and numbers via the "lower" layer.

- **Removed Plover layer**

    I don't intend to use stenography anytime soon, so Plover just didn't have a place in my keymap.


## Qwerty

```
,-----------------------------------------------------------------------------------.
| Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
|------+------+------+------+------+-------------+------+------+------+------+------|
| Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
|------+------+------+------+------+------|------+------+------+------+------+------|
| Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
|------+------+------+------+------+------+------+------+------+------+------+------|
|   `  | Ctrl | Alt  | GUI  |Lower |Space |Space |Raise | Left | Down |  Up  |Right |
`-----------------------------------------------------------------------------------'
```

## Colemak

```
,-----------------------------------------------------------------------------------.
| Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
|------+------+------+------+------+-------------+------+------+------+------+------|
| Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
|------+------+------+------+------+------|------+------+------+------+------+------|
| Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
|------+------+------+------+------+------+------+------+------+------+------+------|
|   `  | Ctrl | Alt  | GUI  |Lower |Space |Space |Raise | Left | Down |  Up  |Right |
`-----------------------------------------------------------------------------------'
```

## Dvorak

```
,-----------------------------------------------------------------------------------.
| Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
|------+------+------+------+------+-------------+------+------+------+------+------|
| Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  -   |
|------+------+------+------+------+------|------+------+------+------+------+------|
| Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
|------+------+------+------+------+------+------+------+------+------+------+------|
|   `  | Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
`-----------------------------------------------------------------------------------'
```

## Lower

This is where I put the number row, a numpad cluster, function keys, and media controls.

```
,-----------------------------------------------------------------------------------.
|   0  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
|------+------+------+------+------+-------------+------+------+------+------+------|
|   $  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   4  |   5  |   6  |      |      |
|------+------+------+------+------+------|------+------+------+------+------+------|
|      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |   1  |   2  |   3  |      |      |
|------+------+------+------+------+------+------+------+------+------+------+------|
|      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
`-----------------------------------------------------------------------------------'
```

## Raise

As a developer, it makes the most sense for me to group all the commonly-used symbols that don't fit on the main layer. In particular, having the dual-column of parens-braces-brackets really helps a lot. I've also added cursorkeys to correspond to the arrows.

I haven't completely filled this layer, which leaves room for future mappings and macros.

```
,-----------------------------------------------------------------------------------.
|   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
|------+------+------+------+------+-------------+------+------+------+------+------|
|      |      |      |      |      |      |   _  |   ?  |   +  |   {  |   }  |  |   |
|------+------+------+------+------+------|------+------+------+------+------+------|
|      |      |      |      |      |      |   -  |   /  |   =  |   [  |   ]  |  \   |
|------+------+------+------+------+------+------+------+------+------+------+------|
|      |      |      |      |      |      |      |      | Home |PageDn|PageUp| End  |
`-----------------------------------------------------------------------------------'
```

## Adjust (Lower + Raise)

Utility layer. This is where I'd switch between Qwerty and Dvorak, ~~fool around with~~ adjust the audio/music settings, or put the Planck into bootloader mode.

```
,-----------------------------------------------------------------------------------.
|      | Reset|      |      |      |      |      |      |      |      |      | Reset|
|------+------+------+------+------+-------------+------+------+------+------+------|
|      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|      |      |
|------+------+------+------+------+------|------+------+------+------+------+------|
|      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
|------+------+------+------+------+------+------+------+------+------+------+------|
|      |      |      |      |      |             |      |      |      |      |      |
`-----------------------------------------------------------------------------------'
```
