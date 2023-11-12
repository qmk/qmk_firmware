# Default Junco Keymap

This is the default layout for Junco. For the most part it's a normal QWERTY layout. The exceptions being the thumb keys, rotary encoders, and lack of caps lock (which is replaced by escape).

One of the biggest features of QMK is it brings layers into the mix which can give you access to even more keys. There are 4 layers: the default/base layer (QWERTY), a symbol layer, an extension layer, and an adjust layer.

Layers are very similar to Shift on a normal keyboard, where "a" becomes "A" when holding down shift. With a custom layer, you can have "j" become "4" for example and make an entire side of the keyboard become a number pad.

The [symbol layer](#symbol-layer) is accessed by holding down backspace, the [extension layer](#extension-layer) is accessed by holding down delete, and the [adjust layer](#adjust-layer) is accessed by holding down both delete and backspace.

## Default Base Layer (QWERTY)

Grey keys are rotary encoders (the ones on far left and far right are optional). Middle legend is pressing down the encoder, bottom left legend is counter-clockwise turn, and bottom right legend is clockwise turn of the encoder.

Those arrows for the bottom legends on the encoders are mouse scroll directions.

Red legends are the layer activated by holding down a key.

![Junco's QWERTY Layout](https://i.imgur.com/fXGt5Jh.png)

## Symbol Layer

This layer is accessed by holding down backspace on the base layer, thus that key is blacked out.

On the symbol layer, the right side is a number pad, and the left side contains all the typical symbols (geared for programming).

Holding down delete within the symbol layer will take you to the adjust layer.

![Junco's Symbol Layer](https://i.imgur.com/6F35Z4Wh.png)

## Extension Layer

This layer's theme is navigation/extras, its accessed by holding down delete on the base layer, thus that key is blacked out.

On the extension layer, the right side is the function keys in a number-pad-esque layout with screen brightness up/down, and the left side has navigation keys and caps lock. Also, the rotary on the right side encoder becomes media controls.

Holding down backspace within the extension layer will take you to the adjust layer.

![Junco's Extension Layer](https://i.imgur.com/FETcqkCh.png)

## Adjust Layer

This layer's theme is adjusting the keyboard's settings, it's accessed by holding down both delete and backspace on the base layer.

On the adjust layer, the right side is the keyboard's settings: clear data, reboot, toggle debug mode, enter the bootloader, and change the base layer between QWERTY and [Colemak-DH](#colemak-dh). The left side adjusts the RGB lighting.

![Junco's Adjust Layer](https://i.imgur.com/fRsdlt3h.png)

## Colemak-DH

This keymap offers Colemak-DH as an alternative base layer to QWERTY.

QWERTY is default when flashing your keyboard, but you can change it to Colemak-DH by selecting it's key on the adjust layer.

If you've never heard of it, Colemak is a keyboard layout that was designed to be a more ergonomic, modern, efficient, and comfortable replacement to QWERTY. Colemak was designed to place the most common letters in english on the home row along with many of the most common bigrams together (two letters typed in a row). Colemak-DH is a variant of Colemak that moves D and H to beneath the index fingers rather than the home row since most people find it easier and faster to reach the keys that way rather than the middle of the home row.

![Junco's Colemak-DH Layout](https://i.imgur.com/8biZfn2h.png)
