# grid 650

[grid 650]( (https://www.gridishere.com/work/grid650)) is a 65% custom mechanical keyboard. 



### Compile

You will need to manually copy the [modified BLE driver](https://drive.google.com/file/d/1IBksQkk_YI8ERxd1O2vNbvkEjU2pdw5E/view?usp=share_link) to your QMK_firmware folder.

Make example for this keyboard.

BLE firmware 

    make grid/grid_650:default

Wired firmware

```
make grid/grid_650:wired
```

QMK BLE PCB is compatible with wired firmware.



### Flash

- Turn of power and unplug USB cable
- Hold ESC ( The top left button )
- Plug in cable
- Flash using [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases)

