# ErgoDox EZ Utilities

## compile_keymap.py

The Python script in this directory, by [mbarkhau](https://github.com/mbarkhau) allows you to write out a basic ErgoDox EZ keymap using Markdown notation, and then transpile it to C, which you can then compile. It's experimental, but if you're not comfortable using C, it's a nice option.

## keymap_beautifier.py

This Python 3 script, by [Tsan-Kuang Lee](https://github.com/tsankuanglee) takes the keymap.c downloaded from [ErgoDox EZ Configurator](https://configure.ergodox-ez.com/) and beautifies it for easier customization, allowing one to quickly draft a layout to build upon.

For example, the original `keymap.c` looks like

```
[0] = KEYMAP(KC_EQUAL,KC_1,KC_2,KC_3,KC_4,KC_5,KC_LEFT,KC_DELETE,KC_Q,KC_W,KC_E,KC_R,KC_T,TG(1),KC_BSPACE,KC_A,KC_S,KC_D,KC_F,KC_G,KC_LSHIFT,CTL_T(KC_Z),KC_X,KC_C,KC_V,KC_B,ALL_T(KC_NO),LT(1,KC_GRAVE),KC_QUOTE,LALT(KC_LSHIFT),KC_LEFT,KC_RIGHT,ALT_T(KC_APPLICATION),KC_LGUI,KC_HOME,KC_SPACE,KC_BSPACE,KC_END,KC_RIGHT,KC_6,KC_7,KC_8,KC_9,KC_0,KC_MINUS,TG(1),KC_Y,KC_U,KC_I,KC_O,KC_P,KC_BSLASH,KC_H,KC_J,KC_K,KC_L,LT(2,KC_SCOLON),GUI_T(KC_QUOTE),MEH_T(KC_NO),KC_N,KC_M,KC_COMMA,KC_DOT,RCTL_T(KC_SLASH),KC_RSHIFT,KC_UP,KC_DOWN,KC_LBRACKET,KC_RBRACKET,MO(1),KC_LALT,CTL_T(KC_ESCAPE),KC_PGUP,KC_PGDOWN,KC_TAB,KC_ENTER)
```

The beautifier parses it and outputs:

```
[0] = LAYOUT_ergodox(
    // left hand
    KC_EQUAL, KC_1, KC_2, KC_3, KC_4, KC_5, KC_LEFT,
    KC_DELETE, KC_Q, KC_W, KC_E, KC_R, KC_T, TG(1),
    KC_BSPACE, KC_A, KC_S, KC_D, KC_F, KC_G,
    KC_LSHIFT, CTL_T(KC_Z), KC_X, KC_C, KC_V, KC_B, ALL_T(KC_NO),
     LT(1,KC_GRAVE), KC_QUOTE, LALT(KC_LSHIFT), KC_LEFT, KC_RIGHT,

    // left thumb
        ALT_T(KC_APPLICATION), KC_LGUI,
            KC_HOME,
        KC_SPACE, KC_BSPACE, KC_END,

    // right hand
    KC_RIGHT, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS,
    TG(1), KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLASH,
    KC_H, KC_J, KC_K, KC_L, LT(2,KC_SCOLON), GUI_T(KC_QUOTE),
    MEH_T(KC_NO), KC_N, KC_M, KC_COMMA, KC_DOT, RCTL_T(KC_SLASH), KC_RSHIFT,
     KC_UP, KC_DOWN, KC_LBRACKET, KC_RBRACKET, MO(1),

    // right thumb
    KC_LALT, CTL_T(KC_ESCAPE),
    KC_PGUP,
    KC_PGDOWN, KC_TAB, KC_ENTER
)
```
