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

## Git cheatsheet
### Syncing with upstream
1. One time setup original as remote "upstream"
`git remote add upstream https://github.com/qmk/qmk_firmware.git`
1. Fetch updated original as "upstream"
`git fetch upstream`
1. Make sure git is on forked master branch
`git checkout master`
1. Rebase master to merge with remote upstream
`git merge upstream/master`
1. Push master changes back to own fork
`git push -f origin master`

### Commit new changes
```
git commit -a -m ""
git push
```
