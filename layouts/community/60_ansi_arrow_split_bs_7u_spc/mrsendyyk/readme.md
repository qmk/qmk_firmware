# 60 ANSI Arrow Split Backspace & 7U Space Keymap

With RGB Lighting/LED/Underglow as Caps Lock, Num Lock, Scroll Lock, and Layer Indicator by [Sendy YK](https://mr.sendyyk.com).

## Base Layer

```c
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Esc│1  │2  │3  │4  │5  │6  │7  │8  │9  │0  │-  │+  │\  │Del│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
     * │Tab  │Q  │W  │E  │R  │T  │Y  │U  │I  │O  │P  │[  │]  │Bspc │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │Caps  │A  │S  │D  │F  │G  │H  │J  │K  │L  │;  │'  │Return  │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┬───┤
     * │Shift   │Z  │X  │C  │V  │B  │N  │M  │,  │.  │Shift │↑  │/  │
     * ├─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴──┬───┼───┼───┤
     * │Ctrl │OS │Alt  │Space                      │Fn │←  │↓  │→  │
     * └─────┴───┴─────┴───────────────────────────┴───┴───┴───┴───┘
     */
```

## Fn Layer

```c
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │`  │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│   │Ejc│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
     * │     │   │   │End│RGB│   │   │   │Ins│   │PSc│   │   │Mute │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │      │   │SLc│   │   │   │Hm │   │   │   │   │   │Pause   │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┬───┤
     * │Vol +   │   │   │Cal│   │BLT│NLc│Ml │   │   │      │PgU│MSt│
     * ├─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴──┬───┼───┼───┤
     * │Vol -│Rwd│FFd  │Play                       │   │Prv│PgD│Nxt│
     * └─────┴───┴─────┴───────────────────────────┴───┴───┴───┴───┘
     */
```

## Reset Layer

```c
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
     * │     │   │   │   │Rst│   │   │   │   │   │   │   │   │     │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │      │   │   │   │   │   │   │   │   │   │   │   │        │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┬───┤
     * │        │   │   │   │   │   │   │   │   │   │      │   │   │
     * ├─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴──┬───┼───┼───┤
     * │     │   │     │                           │   │   │   │   │
     * └─────┴───┴─────┴───────────────────────────┴───┴───┴───┴───┘
     */
```

## RGB Lighting/LED/Underglow as Caps Lock, Num Lock, Scroll Lock, and Layer Indicator

### Caps Lock & Layer Indicator

Set in `led_set_user` function.

### Num Lock & Scroll Lock Indicator

Set in `update_led` function.

## Build The Firmware

Make example for keyboard (after setting up your build environment):

    make <keyboard_folder>:mrsendyyk FORCE_LAYOUT=60_ansi_arrow_split_bs_7u_spc

More information:
* [Setting Up Your QMK Environment](https://docs.qmk.fm/#/getting_started_build_tools)
* [More Detailed make Instructions](https://docs.qmk.fm/#/getting_started_make_guide)
* [The Complete Newbs Guide To QMK](https://docs.qmk.fm/#/newbs)
