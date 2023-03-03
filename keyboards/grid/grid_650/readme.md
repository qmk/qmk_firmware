# grid 650

![grid 650](https://i.imgur.com/RGKxNq5h.jpg)

[grid 650]( (https://www.gridishere.com/work/grid650)) is a 65% custom mechanical keyboard. 

- Keyboard Maintainer: gridishere@gmail.com
- Hardware Support: grid 650 QMK PCB V1 and V1, wired and BLE.



### Compile

Currently, only wired firmware can be compiled automatically.

BLE firmware utilizes a [modified BLE driver](https://drive.google.com/file/d/1IBksQkk_YI8ERxd1O2vNbvkEjU2pdw5E/view?usp=share_link) ,which means you would need to download the modified driver files and replace the original one before compiling.

You can download the complete firmware, including the BLE keymap files [here](https://drive.google.com/drive/folders/101Sm2Rx9HjLjoGbEyEmlQc4R0IJlqbrN?usp=share_link).



Make example for this keyboard. (after setting up your build environment):

**We changed the naming method; the default is wired, and BLE is Bluetooth.**

Wired firmware

```
make grid/grid_650:default
```



QMK BLE PCB is compatible with wired firmware, but not vise versa.



See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).





### Flash

------

Method A, Bootmagic reset:

1. Turn of power and unplug USB cable
2. Wait for 5 seconds
3. Hold ESC ( The top left button )
4. Plug in cable
5. Flash using [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases)



Method B, physical reset button:

	1. Take off the bottom plate
	1. Plug in USB cable
	1. Press the reset button
	1. Flash using [QMK Toolbox](





