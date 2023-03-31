# Deluxe Junco Keymap

This is my personal keymap for Junco at time of writing. It departs from the [default layout](../default/README.md) with the encoder mappings and some extra keycodes. This keymap also adds indicators when caps lock and num lock are enabled. When enabled, that key will become a static white (green on the white backlight mode) but only when the layer that respective key is on is active.

I wanted that classic rainbow barf RGB effect for the underglow even if the per-key lighting is something else, so I added 2 custom RGB matrix animations: white per-key lighting with rainbow underglow and pixel rain with rainbow underglow.

Here are some gifs of the animations:

![White + Underglow Animation](https://i.imgur.com/2vCiZz0.gif)

![Pixel Rain + Underglow Animation](https://i.imgur.com/f6t0OfD.gif)

## Base Layers

The base layers are the same as the default layout, except the right side's left encoder (by the thumb keys) is now media controls. Since I am using all 4 encoders it doesn't make sense to have 2 mouse scroll up/down, but for someone with just 2 encoders it may make sense to have media controls on a layer.

QWERTY:

![QWERTY Layer](https://i.imgur.com/vkS9Tceh.png)

Colemak-DH:

![Colemak-DH Layer](https://i.imgur.com/5YYgaUAh.png)

## Symbol Layer

Symbol layer is identical to the default layout.

![Symbol Layer](https://i.imgur.com/6F35Z4Wh.png)

## Extension Layer

Encoders on the right side become undo/redo and scrolling horizontally by word.

![Extension Layer](https://i.imgur.com/0VCStS8h.png)

## Adjust Layer

Pressing "Stick Adj Layer" will "stick" the adjust layer so you can use the rotary encoders for RGB settings rather than holding down both backspace and delete. To go back to the default layer, press that stick key again or press and release either Del or Backspace. When the adjust layer is currently "sticky" the sticky key will become the indicator color mentioned earlier.

"Toggle Base" will toggle between QWERTY and Colemak-DH and toggle OS will toggle between macOS and Windows key-mappings (swapping WIN/Command with Alt/Option by the thumb keys and properly mapping redo/word scrolling).

![Adjust layer](https://i.imgur.com/71ftNoNh.png)
