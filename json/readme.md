Copyright (C) 2021 @filterpaper

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

# QMK Configurator layout files

Custom layout files for the QMK Configurator
[https://config.qmk.fm/#/](https://config.qmk.fm/#/)

## keymap.c update shortcuts
```
qmk json2c ~/qmk_firmware/json/corne.json > ~/qmk_firmware/keyboards/crkbd/keymaps/filterpaper/keymap.c
qmk json2c ~/qmk_firmware/json/bm40.json > ~/qmk_firmware/keyboards/bm40hsrgb/keymaps/filterpaper/keymap.c
qmk json2c ~/qmk_firmware/json/planck_mit.json > ~/qmk_firmware/keyboards/planck/keymaps/filterpaper/keymap.c
qmk json2c ~/qmk_firmware/json/d65-cole.json > ~/qmk_firmware/keyboards/kbdfans/kbd67/mkiirgb/keymaps/filterpaper/keymap.c
qmk json2c ~/qmk_firmware/json/mark65.json > ~/qmk_firmware/keyboards/boardsource/the_mark/keymaps/filterpaper/keymap.c
```

# Git cheatsheet
https://docs.qmk.fm/#/newbs_git_using_your_master_branch

## Setup QMK repository as upstream
One time setup of the original repository as a remote "upstream":
`git remote add upstream https://github.com/qmk/qmk_firmware.git`

## Sync upstream to own fork
```
git fetch upstream
git checkout master
git merge upstream/master
git push origin master
```

## Commit new changes
```
git commit -a -m ""
git push
```
