# The multifunc encoder keymap for tsubasa
![keymap](https://github.com/kuriatsu/TSUBASA/blob/main/image/tsubasa_multifunc_encoder_keymap.png)

## Features
* Shift + BS = Delete
* Rotary encoder with multiple functions. (Change mode by pushing the encoder. LCD icon to indicate the current mode!) You can add/delete the function in `keymap.c`
    1. PGUP/DOWN
    2. Scroll
    3. Volume up/down
    4. Screen brightness

## Build and Flash
```bash
qmk compile -kb handwired/tsubasa -km multifunc_encoder
```

Flashing example for this keyboard:

```bash
qmk flash -kb handwired/tsubasa -km multifunc_encoder
```
