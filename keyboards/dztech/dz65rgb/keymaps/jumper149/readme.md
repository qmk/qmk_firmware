# jumper149's DZ65RGB v2

Run commands in the root directory of this repository.

```
./bin/qmk compile && sudo dfu-programmer atmega32u4 erase && sudo dfu-programmer atmega32u4 flash ./dztech_dz65rgb_v2_jumper149.hex && sudo dfu-programmer atmega32u4 reset
```

## build

```
./bin/qmk compile
```

## flash

Use `qmk flash` or if it is broken (unknown reason) you can try this workaround.
I personally had some problems on ArchLinux, that I didn't debug any further though.

```
sudo dfu-programmer atmega32u4 erase
sudo dfu-programmer atmega32u4 flash ./dztech_dz65rgb_v2_jumper149.hex
sudo dfu-programmer atmega32u4 reset
```
