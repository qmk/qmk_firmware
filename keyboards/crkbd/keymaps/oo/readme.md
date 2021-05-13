# Build instructions

```zsh
# using json via the configurator can be eaiser than starting from scratch
$ qmk json2c -o keymap.c keymap.json

# compile; use appropriate tool for your microcontroller
$ qmk compile -kb crkbd/rev1/common -km oo

# flash; each side has to be done separately
$ qmk flash -kb crkbd/rev1/common -km oo

```
