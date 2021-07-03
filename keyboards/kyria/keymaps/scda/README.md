# scda

opinionated german OSX layout for the Kyria

## special behaviour

These are some reminders or rules that are the result of interesting behaviour I observed along the way of developing this layout:

-   `LT(_LAYER_NAME, KC_XY)` will break the json import in the configurator after `c2json` export, so this has to be manually edited after export
-   do not use home-row mods on the symbols layer as this will destroy some shifted keycodes (like `~` or `/` that are on the mod-tap keys).
    -   reason: shifted keys cannot be sent by mod-tap or layer-tap keys
        -   [article](https://thomasbaart.nl/2018/12/09/qmk-basics-tap-and-hold-actions/)
        -   [docs](https://docs.qmk.fm/#/keycodes_us_ansi_shifted)
-   scrolling keys are reversed from their intended usage - seems like macOS applies natural scrolling here as well
-   the slave display can apparently not easily display the current layer etc. (even with `SPLIT_MODS_ENABLE`)
