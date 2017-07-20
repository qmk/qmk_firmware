## gh60 Rev C keyboard firmware

![gh60 Rev C PCB](https://i.imgur.com/FejpoNF.jpg)

    /* Column pin configuration
    * col: 0   1   2   3   4   5   6   7   8   9   10  11  12  13
    * pin: F0  F1  E6  C7  C6  B6  D4  B1  B7  B5  B4  D7  D6  B3  (Rev.C)
    */
     
    /* Row pin configuration
    * row: 0   1   2   3   4
    * pin: D0  D1  D2  D3  D5
    */
     
    GPIO pads
    0 F7 WASD LEDs
    1 F6 ESC LED
    2 F5 FN LED
    3 F4 POKER Arrow LEDs
     
    B2 Capslock LED
    B0 not connected
	
Functions to controls LED clusters
	
    gh60_caps_led_on()
    gh60_poker_leds_on()
    gh60_fn_led_on()
    gh60_esc_led_on()
    gh60_wasd_leds_on()
    
    gh60_caps_led_off()
    gh60_poker_leds_off()
    gh60_fn_led_off()
    gh60_esc_led_off()
    gh60_wasd_leds_off()
	
======================

## Quantum MK Firmware

For the full Quantum feature list, see [the parent readme.md](/readme.md).

## Building

Download or clone the whole firmware and navigate to the keyboards/gh60_rev_c folder. Once your dev env is setup, you'll be able to type `make` to generate your .hex - you can then use the Teensy Loader to program your .hex file. 

Depending on which keymap you would like to use, you will have to compile slightly differently.

### Default
To build with the default keymap, simply run `make default`.

### Other Keymaps
Several version of keymap are available in advance but you are recommended to define your favorite layout yourself. To define your own keymap create file named `<name>.c` in the keymaps folder, and see keymap document (you can find in top readme.md) and existent keymap files.

To build the firmware binary hex file with a keymap just do `make` with a keymap like this:

```
$ make [default|jack|<name>]
```

Keymaps follow the format **__\<name\>.c__** and are stored in the `keymaps` folder.
