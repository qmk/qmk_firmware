# PolyKeyboard

Project progress is documented on https://ko-fi.com/polykb

Development version of PolyKeyboard (Atom), which uses one OLED display per keycap.
Hardware info at https://github.com/thpoll83/PolyKeyboard/tree/master/poly_kb_atom

Keyboard Maintainer: thpoll83  
Hardware Supported: STM32F407 (not maintained), RP2040
Hardware Availability:
 - https://www.raspberrypi.com/products/raspberry-pi-pico/
 - https://stm32-base.org/boards/STM32F407VGT6-STM32F4XX-M.html

# Build Notes

## Clean

$ make clean
or
$ rm -rf .build

## Build

$ make handwired/polykb/wave:default
$ qmk compile -kb handwired/polykb/wave -km default

### Flash split setup via EE Hands

make handwired/polykb/wave:default:uf2-split-right
make handwired/polykb/wave:default:uf2-split-left

## After merging master into branch update dependencies with

$ make git-submodule

### Init submodules

$ git submodule update --init --recursive

## Check image size

$ size .build//handwired_polykb_wave_rp2040pico_default.elf -B

### Copy image to RPI

$ cp .build/handwired_polykb_wave_rp2040pico_default.uf2 /media/$USER/RPI-RP2/

## Get debug output

$ qmk console

# General



See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
