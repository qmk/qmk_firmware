# narze's layout

## Notes
- SuperDuper mode for Ergodox is still under development, since combo keys does not work very well on Ergodox firmware.
  Now it is using multiple layers as a workaround. Actual implementation using combos are on my Planck layout.

## Key features
- Qwerty + [Colemak](https://colemak.com) layouts, and you can type Qwerty on software-level Colemak as well. Very useful for gaming or when your friend wanna type something but don't use Colemak.
- [(S)uper (D)uper Mode](/users/narze/readme.md)
- Mouse keys with Z

## Build instructions
If your environment is ready to build with `make`, don't use docker since it takes 5m+ to compile.
Use the instructions in Ergodox Infinity's readme.

#### Left side (Docker)
```
cd /path/to/qmk_firmware
util/docker_build.sh ergodox_infinity:narze
avr-objcopy -Iihex -Obinary .build/ergodox_infinity_narze.hex .build/ergodox_infinity_narze_left.bin
dfu-util --device 1c11:b007 -D .build/ergodox_infinity_narze_left.bin
```

#### Right side (Docker)
You have to override `usb_args` in order to pass `MASTER=right` to docker using provided build script.
```
cd /path/to/qmk_firmware
usb_args="-e MASTER=right" util/docker_build.sh ergodox_infinity:narze
avr-objcopy -Iihex -Obinary .build/ergodox_infinity_narze.hex .build/ergodox_infinity_narze_right.bin
dfu-util --device 1c11:b007 -D .build/ergodox_infinity_narze_right.bin
```
