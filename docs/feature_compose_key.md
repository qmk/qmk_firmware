# The Compose Key: Mnemonic shortcuts for your favorite strings

On many Linux systems, the Compose key lets you create shortcuts for interesting Unicode characters and strings. For example, to enter the Greek letter θ on a keyboard that doesn't support it, you might press `<COMPOSE> <g> <t> <h>`.

The Compose Key processor lets you do the same thing directly on your keyboard, so it'll work on your choice of OS.

# Setting up the Compose Key processor

1. Choose a key to use for your Compose Key. (Mod-Tap keys are not currently supported.) Assign it the keycode `COMPOSE`.
2. Include `COMPOSE_ENABLE = yes` in your `rules.mk`. To enable support for non-ANSI characters, include `UNICODE_ENABLE = yes` as well, and follow the [Unicode feature docs](feature_unicode.md) to set it up for your OS.
3. Define your compose sequences in `keyboard_post_init_user` by calling `declare_compose_seq`. For example:
    ```c
void keyboard_post_init_user(void) {
    declare_compose_seq((uint64_t[]){KC_G, KC_T, KC_H}, 3, "θ");
    declare_compose_seq((uint64_t[]){KC_G, KC_B}, 2, "β");
    declare_compose_seq((uint64_t[]){KC_S, KC_H, KC_R, KC_U, KC_G}, 5, "¯\\_(ツ)_/¯");
}
```
    defines three sequences: `COMPOSE-G-T-H` to type `θ`, `COMPOSE-G-B` to type `β`, and `COMPOSE-S-H-R-U-G` to type `¯\_(ツ)_/¯`.

You can define as many sequences as you want, subject to firmware size restrictions. The author found that adding the Compose Key and Unicode modules added about 1.3KB and each rule added about 150B.