# PolyKybd

Project progress is documented on https://ko-fi.com/polykb

Development version of PolyKybd, which uses OLED displays in its keycaps.
Hardware info at https://github.com/thpoll83/PolyKeyboard/tree/master/poly_kb_atom

Keyboard Maintainer: thpoll83
Hardware Supported: RP2040 (STM32F407 not maintained any more)

# Build Notes

## Keyboard Variants

- ~~`deprecated/4x2` and `deprecated4x5` were the first dev boards running QMK, these folders are not maintained and also will not compile.~~
- `wave` was the first version of the 72-key split keyboard and is kept as a reference.
- `split72` is the current hardware (HW rev2 and up) iteration of `wave` with slight differences. Only `split72` is actively developed.

### Code generation

Please be aware that the code makes use of cog to generate some code parts. You can find cog here:

[https://github.com/nedbat/cog](https://github.com/nedbat/cog)

Please run `run_cog.sh` in the keymap folder of your choice.

## Clean

`make clean`
or
`rm -rf .build`

## Build

`make handwired/polykybd/split72:default`
`qmk compile -kb handwired/polykybd/split72 -km default`

### Flash split setup via EE Hands

`make handwired/polykybd/split72:default:uf2-split-right`
`make handwired/polykybd/split72:default:uf2-split-left`

## After merging master into branch update dependencies with

`make git-submodule`

### Init submodules

`git submodule update --init --recursive`

### Updates tags to display the right verion

`git fetch --tags upstream`

## Check image size

`size .build//handwired_polykybd_split72_rp2040pico_default.elf -B`

### Copy image to RPI

`cp .build/handwired_polykybd_split72_rp2040pico_default.uf2 /media/$USER/RPI-RP2/`

## Get console output

`qmk console`

# General

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
