# 60_ansi_arrow Keymap

by [Sendy YK](https://mr.sendyyk.com).

## Default Layer

```c
    /*
     * [_BASE] Default Layer
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
     * │Esc│1  │2  │3  │4  │5  │6  │7  │8  │9  │0  │-  │+  │Bspc   │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
     * │Tab  │Q  │W  │E  │R  │T  │Y  │U  │I  │O  │P  │[  │]  │\    │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │Caps  │A  │S  │D  │F  │G  │H  │J  │K  │L  │;  │'  │Enter   │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┬───┤
     * │Shift   │Z  │X  │C  │V  │B  │N  │M  │,  │.  │Shift │↑  │/  │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬───┼───┼───┤
     * │Ctl │OS  │Alt │Space                   │Alt│Fn │←  │↓  │→  │
     * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┘
     */
```

## Fn Layer

```c
    /*
     * [[_FN]] Fn Layer
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
     * │`  │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│Delete │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
     * │Bri U│   │   │End│Rst│   │   │   │Ins│   │PSc│   │   │Eject│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │Bri D │   │SLc│   │   │   │Hom│   │   │   │   │   │Mute    │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┬───┤
     * │Vol+    │   │   │Cal│   │   │NLc│Mai│   │   │Pause │PgU│MSt│
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬───┼───┼───┤
     * │Vol-│Rwd │FFd │Play/Pause              │   │   │Prv│PgD│Nxt│
     * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┘
     */
```

## Build The Firmware

Make example for keyboard (after setting up your build environment):

    make <keyboard_folder>:default_60_ansi_arrow

More information:
* [Setting Up Your QMK Environment](https://docs.qmk.fm/#/getting_started_build_tools)
* [More Detailed make Instructions](https://docs.qmk.fm/#/getting_started_make_guide)
* [The Complete Newbs Guide To QMK](https://docs.qmk.fm/#/newbs)
