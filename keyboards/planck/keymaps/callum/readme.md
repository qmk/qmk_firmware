# callum’s planck layout

This is a layout for the grid planck, built with a few ideals in mind:

- Minimal response times should be maintained. i.e. keys that react differently depending on whether they are tapped or held, keys that react differently if they are double tapped, etc. should be avoided — they inevitably send their keycode later than a normal key, interrupting the immediate feedback from the screen. Therefore we restrict ourselves to chording.
- The hands should never need to leave the home position. The usual culprit for this is the arrow cluster, so the arrow cluster should be as close to home as possible.
- There should be two of every modifier (one on each side), otherwise certain long key combinations become hard to make.
- Backspace should be in the “capslock position” in the colemak tradition.
- The keyboard should be usable on any operating system without software changes. For me this means being able to swap the `GUI` key and `Ctrl` key in firmware so that `Cmd-z,x,c,v,…` becomes `Ctrl-z,x,c,v,…` when swapping from macOS to Windows.

We have four layers. A `BASE` layer (which is either `BASE Mac` or `BASE Windows`), in colemak; a `MOVE` layer, with an arrow cluster etc, a `SYMB` layer, with numbers and symbols; and a `FUNC` layer, with function keys and media keys.

## The `BASE` layer
For Mac
```
,-----------------------------------------------------------------------------------.
| Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  |  -   |
|------+------+------+------+------+-------------+------+------+------+------+------|
| Bksp |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
|------+------+------+------+------+------|------+------+------+------+------+------|
| Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  | Shift|
|------+------+------+------+------+------+------+------+------+------+------+------|
| Func | Ctrl |  Alt |  Cmd | Symb | Enter| Space| Move |  Cmd |  Alt | Ctrl | Caps |
`-----------------------------------------------------------------------------------'
```
 
For Windows
```
 ,-----------------------------------------------------------------------------------.
| Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  |  -   |
|------+------+------+------+-------+-------------+------+------+------+------+------|
| Bksp |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
|------+------+------+------+------+------|------+------+------+------+------+------|
| Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  | Shift|
|------+------+------+------+------+------+------+------+------+------+------+------|
| Func |  Win |  Alt | Ctrl | Symb | Enter| Space| Move | Ctrl |  Alt |  Win | Caps |
`-----------------------------------------------------------------------------------'
```

One of the two above layers is set as the default layer at any one time; see `FUNC`. The basic layout is [colemak](https://colemak.com). `Esc` and `Del` are conspicuously absent but are especially easy to reach from either of the other main layers (see below). The `backspace` location is standard colemak. The `Caps` key is still on the `BASE` layer but only because I  don’t really use the bottom corners so there’s nothing else I would rather put there. Having `Enter` on a thumb means I can still have `quote` immediately to the right of `O`, something that would have annoyed me endlessly otherwise. `minus` is in the upper right because I had an extra space and it’s probably my next most used key that didn’t yet have a home.

The `MOVE` and `SYMB` layers are reached by holding down the `Move` and `Symb` keys respectively. The `FUNC` layer is reached by holding down both the `Move` and `Symb` keys simultaneously, *or* by holding down the `fn` key. The intended use is that whenever both hands are on the keyboard, the former method is used, and the latter is only used when, for example, reaching over to the keyboard with one hand to access the media controls.

## The `MOVE` layer
```
,-----------------------------------------------------------------------------------.
|  Esc |      | Home |  Up  |  End |      |      | Home |  Up  |  End |      |  Esc |
|------+------+------+------+------+-------------+------+------+------+------+------|
|  Del |      | Left | Down | Right|      |      | Left | Down | Right|      |  Del |
|------+------+------+------+------+------|------+------+------+------+------+------|
|      |      |      | Pg Up| Pg Dn|      |      | Pg Dn| Pg Up|      |      |      |
|------+------+------+------+------+------+------+------+------+------+------+------|
|      |      |      |      |      |      |      |      |      |      |      |      |
`-----------------------------------------------------------------------------------'
```

This is fairly self explanatory. I almost exclusively use the right hand cluster so that movement is a one handed affair, but the left hand cluster is there if it’s needed.

On *macOS* I recommend using [Karabiner](https://pqrs.org/osx/karabiner/) and ticking *Use PC Style Home/End #2* and *Use PC Style PageUp/PageDown* so that `Home` and `End` jump you to the beginning and end of the line respectively and so that `Pg Up` and `Pg Dn` move the cursor instead of just scrolling.

None of the modifiers are overwritten so that `shift-alt-arrows` etc work as expected.

## The `SYMB` layer
```
,-----------------------------------------------------------------------------------.
|  Esc |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  Esc |
|-----------------------------------------------------------------------------------|
|  Del |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |  Del |
|------+------+------+------+------+-------------+------+------+------+------+------|
|      |   ~  |   `  |   +  |   =  |   |  |   \  |   [  |   ]  |   {  |   }  |      |
|------+------+------+------+------+------+------+------+------+------+------+------|
|      |      |      |      |      |      |      |      |      |      |      |      |
`-----------------------------------------------------------------------------------'
```

The symbol layer has all the numbers and their usual corresponding symbols in the first two rows, with the symbols on the home row since I use them more frequently than the numbers. The third row contains all the remaining symbols, arranged roughly so that the most used symbols are accessible with the strongest fingers.

`Esc` and `Del` are repeated here since I wanted to be able to reach either, one handed, with either hand.

Again none of the modifiers are overwritten so that shortcuts involving numbers or symbols work as expected.

## The `FUNC` layer
```
,-----------------------------------------------------------------------------------.
|  F12 |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
|-----------------------------------------------------------------------------------|
|      | Play | Prev | Next |  BL+ |      |      | Lock |      |      |  Mac |      |
|------+------+------+------+------+------|------+------+------+------+------+------|
|      | Mute | Vol- | Vol+ |  BL- |      |      | Close|      |      |  Win |      |
|------+------+------+------+------+------+------+------+------+------+------+------|
|      |      |      |      |      |      |      |      |      |      |      | Reset|
`-----------------------------------------------------------------------------------'
```

`BL+` and `BL-` are short for *backlight up* and *backlight down*, and in firmware are actually `KC_PAUS` and `KC_SLCK` respectively, since *macOS* interprets these as the backlight keys. `Lock` is currently a macro hard coded to turn off the screen on *macOS*. (By activating the shortcut `shift-ctrl-power`.) `Close` sends `alt-f4` to make that shortcut easier to reach. `Mac` and `Win` set the default layer to the Mac and Windows `BASE` layers respecitevly.

## Other changes from the default
I have LEDs and sound disabled, simply because I have no need of them.
