traveler keyboard firmware
======================

## Traveller Specific Info ##
The traveller is a varient on the atreus keyboard. 
Like the Atreus, it is designed to be a good compromise between size and ergonomics. 

key differences are 
- an additional column for each pinky
- an RGB LED in the center to show the current layer
- more finger stagger,  splay angle and contoured keycaps (F2 profile for space key). 

You can make your own traveller  keyboard by using the openscad tools from the atreus repository, and adding a hole for the LED to shine through. 

## Quantum MK Firmware

For the full Quantum feature list, see [the parent README.md](/readme.md).

## Building

Download or clone the whole firmware and navigate to the keyboard/traveler folder. Once your dev env is setup, you'll be able to type `make` to generate your .hex - you can then use the Teensy Loader to program your .hex file. 

Depending on which keymap you would like to use, you will have to compile slightly differently.

### Default
To build with the default keymap, simply run `make`.

### Other Keymaps
Several version of keymap are available in advance but you are recommended to define your favorite layout yourself. To define your own keymap create file named `<name>.c` and see keymap document (you can find in top README.md) and existent keymap files.

To build the firmware binary hex file with a keymap just do `make` with `KEYMAP` option like:
```
$ make KEYMAP=[default|jack|<name>]
```
Keymaps follow the format **__\<name\>.c__** and are stored in the `keymaps` folder.
