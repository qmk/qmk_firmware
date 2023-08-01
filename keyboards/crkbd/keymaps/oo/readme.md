# Build instructions

```zsh
# if this is a fresh install of QMK, don't forget to run setup
# or you might be missing necessary tools and libraries!
# https://docs.qmk.fm/#/newbs_getting_started
$ qmk setup

# using json via the configurator can be easier than starting from scratch
# but you will need to go back and make the formatting readable for future edits
$ qmk json2c -o keymap.c keymap.json

# compile; use appropriate tool for your microcontroller
$ qmk compile -kb crkbd/rev1/common -km oo

# flash; each side has to be done separately
$ qmk flash -kb crkbd/rev1/common -km oo

```
