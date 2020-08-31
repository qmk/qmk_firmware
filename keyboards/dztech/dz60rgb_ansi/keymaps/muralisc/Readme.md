### ansi vim

Keymap for dz60rgb terminal users

### Philosophy

Touch typing largely relies on muscle memory and hence
maintaining a uniform position of keys across devices helps a lot.

The below keymap attempts to maintain a uniform keymap across Linux and Mac.

Avoiding the use of `KC_GESC` as the intention is to use the same layer for mac and linux.
`KC_GESC` causes `` CMD+` `` to be send which has a default mapping

Using `A` for `Home`
Using `E` for `End`
Using `F` for `PgDN`
Using `B` for `PgUP`

Dedicated Layer for arrow keys and Num keys and `Ins`, `Home` and `PgUp`.

### Flashing

Set keyboard to Reset mode and 

```
make dztech/dz60rgb:ansi_vim:dfu-util
```

If build errors occurs try

```
CFLAGS="-Wno-error=deprecated" make dztech/dz60rgb:ansi_vim:dfu-util
```
