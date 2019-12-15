# datagrok's QMK user-space code

## cdeq "comma dot exclamation question"

This is a hack to place `question mark` on `shift-comma` and `exclamation mark` on `shift-period`.

When using an operating system configured for a US/qwerty layout this replaces the angle brackets `<` `>` with `?` `!`. This helps on small keyboards to keep symbols for prose co-located in one layer, and symbols for programming in another.

It's a "hack" because the "proper" way to accomplish this would be to edit the operating system's keymap.

### setup

in your `keymap.c`:

    #include "feature_cdeq.h"

    bool process_record_user(uint16_t keycode, keyrecord_t *record) {
        return process_record_cdeq(keycode, record);
    }
    
in your `rules.mk`,

    SRC += feature_cdeq.c

### examples

- atreus:datagrok
- bm43a:datagrok
- mitosis:datagrok

## base layer selector

Defines a keycode `KF_LAYO` to rotate between available default layers.

`Shift`+`KF_LAYO` makes the currently selected one persistent across reboots.

This is useful if you'd like your keyboard to support and toggle between QWERTY, Dvorak, Colemak, Workman, and other layouts while keeping a common arrangement of modifier and function keys.

Since toggling layouts seems like something one does infrequently, I wanted to be able to operate this feature with a single key, instead of one for each layer like planck:default or bootmagic.

### setup

in your `keymap.c`:

    #define KF_LAYO SAFE_RANGE
    #include "feature_default_layers_selector.h"
    const uint8_t highest_base_layer = 4;

    bool process_record_user(uint16_t keycode, keyrecord_t *record) {
      return \
        process_record_save_default_layer(keycode, record) && \
        process_record_select_default_layer(keycode, record);
    }
    
in your `rules.mk`,

    SRC += feature_default_layers_selector.c

### examples

- atreus:datagrok
- bm43a:datagrok
- mitosis:datagrok
