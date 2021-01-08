# QMK Configurator layout files

Custom layout files for the QMK Configurator
[https://config.qmk.fm/#/](https://config.qmk.fm/#/)

## Updating files
```
qmk json2c ~/qmk_firmware/json/corne.json > ~/qmk_firmware/keyboards/crkbd/keymaps/filterpaper/keymap.c
qmk json2c ~/qmk_firmware/json/bm40.json > ~/qmk_firmware/keyboards/bm40hsrgb/keymaps/filterpaper/keymap.c
qmk json2c ~/qmk_firmware/json/planck_mit.json > ~/qmk_firmware/keyboards/planck/keymaps/filterpaper/keymap.c
qmk json2c ~/qmk_firmware/json/d65-cole.json > ~/qmk_firmware/keyboards/kbdfans/kbd67/mkiirgb/keymaps/filterpaper/keymap.c
qmk json2c ~/qmk_firmware/json/mark65.json > ~/qmk_firmware/keyboards/boardsource/the_mark/keymaps/filterpaper/keymap.c
```

## Compile commands
```
qmk compile -kb crkbd/rev1/common -km filterpaper
qmk compile -kb bm40hsrgb -km filterpaper
qmk compile -kb planck/rev6 -km filterpaper
qmk compile -kb kbdfans/kbd67/mkiirgb/v2 -km filterpaper
qmk compile -kb the_mark -km filterpaper
```

## Split keyboard
Flash left and ride side recognition for EE_HANDS
```
make crkbd/rev1/common:filterpaper:dfu-split-left
make crkbd/rev1/common:filterpaper:dfu-split-right
```
