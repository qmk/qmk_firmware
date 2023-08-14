# ScottoKeebs

Applies to layouts:

-   LAYOUT_ortho_4x10
-   LAYOUT_split_3x5_2
-   LAYOUT_split_3x5_3

### QWERTY

By default the keymap will use Colemak, to compile in QWERTY, append the `KEYMAP=QWERTY` environment variable.

```
qmk compile -kb <keyboardName> -km scottokeebs -e KEYMAP=QWERTY
```

Example for [Scotto34](/keyboards/scottokeebs/scotto34):

```
qmk compile -kb scottokeebs/scotto34 -km scottokeebs -e KEYMAP=QWERTY
```
