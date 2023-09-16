Richard Dawe's keymap for ANSI HS60 V2. VIA support disabled.
=============================================================

This layout is based on the [KBParadise V60 Type-R](https://www.kbparadise.com/store/products/v60-black), with its HHKB-like cursor keys.

I did not like how the V60 Type-R put all its features onto one layer. It's too easy to e.g.: change the RGB backlighting with a typo. For this reason, I split the layers out:

 * Layer 1 (FN): navigation and F-keys;
 * Layer 2 (hold space): further navigation like PgUp/PgDn;
 * Layer 3 (hold escape): boot loader mode, RGB effects, media keys.

```
qmk compile -kb hs60/v2/ansi -km richdawe
qmk flash -kb hs60/v2/ansi -km richdawe
```