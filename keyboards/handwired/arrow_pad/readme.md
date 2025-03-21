arrow_pad keyboard firmware
======================

## Keyboard Info

The ArrowPad is a wired conversion that can be made to any stand-alone keypad. It uses two main layers - a standard numpad, and a more advanced arrow cluster navigator.

The first 24-key ArrowPad was handwired, but the PCB was wired as listed below.

```
<Chip Ref Des> pin <Pin #>
<Keycap Name> (Silkscreen Name if different) - <Switch Pin #>


Note:
U2 pin 2 is the Num Lock LED and is  active low.

U2 pin 1
Clear (Num Lock) - 1
Enter - 2
Esc (ESC) - 2


U2 pin 3
- - 1

U2 pin 4
7 - 2
8 - 2
9 - 2

U2 pin 5
* - 2
Delete (BACK SPACE) -  2

U2 pin 6
1 - 2
0 - 2
. - 2
, - 2

U2 pin 7
4 - 2
5 - 2
6 - 2

U2 pin 8
Tab - 2
= (/) - 2

U2 pin 13
Delete (BACK SPACE) -  1
9 - 1
6 - 1
3 - 1
. - 1

U2 pin 14
Tab - 1
8 - 1
5 - 1
2 - 1
0 - 1

U2 pin 15
Esc (ESC) - 1
= (/) - 1
/ (*) - 1
7 - 1
4 - 1
1 - 1
+ - 1

U2 pin 16
Enter - 1
* (<--) - 1
, - 1

U2 pin 17
Fn (#NAME?) - 1
- - 2
Clear (Num Lock) - 2

U2 pin 18
Fn (#NAME?) - 2
* (<--) - 2
+ - 2
3 - 2
2 - 2
```

More info can be found on [GeekHack](https://geekhack.org/index.php?topic=73632.msg1802497#msg1802497)

The second ArrowPad was a conversion from a 21-key Genovation keypad. It used a 2 row x 11 column matrix.

## Quantum MK Firmware

For the full Quantum feature list, see [the parent readme.md](/readme.md).

## Building

Download or clone the whole firmware and navigate to the keyboards/arrow_pad folder. Once your dev env is setup, you'll be able to type `make` to generate your .hex - you can then use the Teensy Loader to program your .hex file.

Depending on which keymap you would like to use, you will have to compile slightly differently.

### Default
To build with the default keymap, simply run `make handwired/arrow_pad:default`.

### Other Keymaps
Several version of keymap are available in advance but you are recommended to define your favorite layout yourself. To define your own keymap create file named `<name>.c` in the keymaps folder, and see keymap document (you can find in top readme.md) and existent keymap files.

To build the firmware binary hex file with a keymap just do `make` with a keymap like this:

```
$ make handwired/arrow_pad:[default|pad_21|pad_24|<name>]
```

Keymaps follow the format **__\<name\>.c__** and are stored in the `keymaps` folder.
