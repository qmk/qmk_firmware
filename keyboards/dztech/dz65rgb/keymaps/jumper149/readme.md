# jumper149's DZ65RGB v2

## build

```
~/.local/bin/qmk compile
```

## flash

```
dfu-programmer atmega32u4 erase
dfu-programmer atmega32u4 flash dztech_dz65rgb_v2_jumper149.hex
dfu-programmer atmega32u4 reset

```
