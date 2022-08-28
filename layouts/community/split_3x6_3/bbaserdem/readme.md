This folder contains my [split\_3x6\_3](../../../default/split_3x6_3) board layouts
Check out the [user readme](../../../../users/bbaserdem/readme.md) for more info.

# Crkbd

Using [this](https://github.com/ItsWaffIe/waffle_corne) Proton-C compatible PCB.

Applying the similar keymap to [@waffle](https://github.com/ItsWaffIe/waffle_corne);
using their `crkbd:rev1:arm` build.

## Build

Build commands;

* For ARM: `CFLAGS="-Wno-error=deprecated" qmk flash -kb crkdb/rev1 -km bbaserdem -bl dfu-util-split-{left,right}`
