TheAmarin's Neo2-based Layout
================================

This layout is based on [Neo2](https://www.neo-layout.org/), an ergonomic keyboard layout optimized for coding and German language.
**neo2marin** tries to squeeze Neo2 onto the Planck keyboard.

Neo2 already uses several layers with multiple modifiers, so we don't have to invent new layers.
A major difficulty is the missing 'hashtag' key which is usually left to the 'return' key on German QWERTZ keyboards.

Another astonishing thing might be that `return`/`enter` needs a modifier (`MOD4`+`P`).

This layout makes heavy use of the split `space` key, as its left part becomes the quite important `MOD4` modifier.


## The Neo2 Main Layer

```
|----+----+----+----+----+----|    |----+----+----+----+----+------|
|TAB | X  | V  | L  | C  | W  |    | K  | H  | G  | F  | Q  | SS   |
|----+----+----+----+----+----|    |----+----+----+----+----+------|
|MOD3| U  | I  | A  | E  | O  |    | S  | N  | R  | T  | D  |Y/MOD3|
|----+----+----+----+----+----|    |----+----+----+----+----+------|
|LSFT| Ü  | Ö  | Ä  | P  | Z  |    | B  | M  | ,  | .  | J  |RSFT  |
|----+----+----+----+----+----|    |----+----+----+----+----+------|
|LCTL|LGUI|LALT|SWAP|MOD5|MOD4|    |SPC |SWAP|MOD5|APP |RALT|RCTL  |
|----+----+----+----+----+----|    |----+----+----+----+----+------|
```

Unfortunately, `y` and `MOD3` (switch to layer 3) need to share a single key.
This works for me most of the time but I am happy [to learn about your solution](https://github.com/theamarin/qmk_firmware/issues)!


## The QWERTZ fallback layer

I nearly never use this layer, so there may be room for optimization.

```
|----+----+----+----+----+----|    |----+----+----+----+----+------|
|TAB | Q  | W  | E  | R  | T  |    | Z  | U  | I  | O  | P  | Ü    |
|----+----+----+----+----+----|    |----+----+----+----+----+------|
|CAPS| A  | S  | D  | F  | G  |    | H  | J  | K  | L  | Ö  |Ä/MOD3|
|----+----+----+----+----+----|    |----+----+----+----+----+------|
|LSFT| Y  | X  | C  | V  | B  |    | N  | M  | ,  | .  | SS |RSFT  |
|----+----+----+----+----+----|    |----+----+----+----+----+------|
|LCTL|LGUI|LALT|SWAP|MOD5|MOD4|    |SPC |SWAP|RALT|APP |RALT|RCTL  |
|----+----+----+----+----+----|    |----+----+----+----+----+------|
```

The German `ß` has moved right to the `.` key, and we have to reuse `Ä` for `MOD3` again.


## MOD3: The Coding Layer

This is definitively the coolest part of Neo2, having most of the coding-related symbols right on your home row!
Of course, this is the only way to do it on Planck.

```
|----+----+----+----+----+----|    |----+----+----+----+----+----|
|'   | €  | _  | [  | ]  | ^  |    | !  | <  | >  | =  | &  | `  |
|----+----+----+----+----+----|    |----+----+----+----+----+----|
|MOD3, \  | /  | {  | }  | *  |    | ?  | (  | )  | -  | :  | @  |
|----+----+----+----+----+----|    |----+----+----+----+----+----|
|LSFT, #  | $  | |  | ~  | '  |    | +  | %  | "  | '  | ;  |RSFT|
|----+----+----+----+----+----|    |----+----+----+----+----+----|
|LCTL|LGUI|LALT|SWAP|MOD5|MOD4|    |SPC |SWAP|MOD5|APP |RALT|RCTL|
|----+----+----+----+----+----|    |----+----+----+----+----+----|
```

Because `y` and `MOD3` have to share a key, we need two variants of the MOD3 layer (as can be seen in the keymap).



## MOD4: The Movements Layer

```
|----+----+----+----+----+----|    |----+----+----+----+----+----|
|    |PGUP|BSPC| UP |DEL |PGDN|    |    | 7  | 8  | 9  | +  | -  |
|----+----+----+----+----+----|    |----+----+----+----+----+----|
|    |HOME|LEFT|DOWN|RGHT|END |    |    | 4  | 5  | 6  | ,  | .  |
|----+----+----+----+----+----|    |----+----+----+----+----+----|
|    |ESC |TAB |INS |ENTR|    |    | 0  | 1  | 2  | 3  | ;  |    |
|----+----+----+----+----+----|    |----+----+----+----+----+----|
|    |    |    |    |    |    |    |    | 0  |    |    |    |    |
|----+----+----+----+----+----|    |----+----+----+----+----+----|
```
  
  
## MOD5: The Fun(ctions) Layer

```
|----+----+----+----+----+----|    |----+----+----+----+----+----|
|    |AUD1|VOLD|MAXM|VOLU|    |    |M1R | F7 | F8 | F9 |F12 |PSCR|
|----+----+----+----+----+----|    |----+----+----+----+----+----|
|    |MSTP|MPRV|MPLY|MNXT|NEO2|    |M1S | F4 | F5 | F6 |F11 |BRK |
|----+----+----+----+----+----|    |----+----+----+----+----+----|
|    |AUD0|TAB |INS |ENTR|QWERTZ   |M1P | F1 | F2 | F3 |F10 |    |
|----+----+----+----+----+----|    |----+----+----+----+----+----|
|    |    |    |    |    |    |    |    |    |    |    |    |    |
|----+----+----+----+----+----|    |----+----+----+----+----+----|
```
  

Have fun!

[Your feedback is appreciated](https://github.com/theamarin/qmk_firmware/issues)!
