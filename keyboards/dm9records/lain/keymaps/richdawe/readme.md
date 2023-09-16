# richdawe keymap for Lain

## Leds setting

```
1: CAPS LOCK
2-3: Layer indicator
```

## Changes from default layout

There are too many changes to list here. I tried to change the layout in a way that felt natural to me. I put Tab next to Q, and moved Esc next to A. Tab next to Q is so engrained, that it's easier to move Esc.

Also, like on many of my kemaps, I've changed the key combination to enter the bootloader. Press the top-left key plus bottom-key together. I prefer an explicit combination than holding e.g.: escape when inserting the USB cable.

```
qmk compile -km richdawe -kb dm9records/lain
qmk flash -km richdawe -kb dm9records/lain
```

## Inspiration from Other 40% or Split Layouts

 * [Alish40](https://github.com/qmk/qmk_firmware/tree/master/keyboards/reedskeebs/alish40)
 * [Kolibrimini](https://github.com/kreme123/Kolibrimini)
 * [smAllice](https://github.com/qmk/qmk_firmware/tree/master/keyboards/keyhive/smallice/keymaps/default)
 * [Feather 40](https://kbd.news/Feather-40-1733.html)

 * [Designing a Symbol Layer](https://getreuer.info/posts/keyboards/symbol-layer/index.html)
 * [Designing a 36-key custom keyboard layout](https://peterxjang.com/blog/designing-a-36-key-custom-keyboard-layout.html)
 * [Building a 34 Key Keyboard Layout](https://ryan.himmelwright.net/post/building-34-key-layout/)
 * [T-32/2 keyboard layoyut](https://www.jonashietala.se/blog/2022/08/28/the_t-342_keyboard_layout/)
 * [QMK Heatmaps](https://precondition.github.io/qmk-heatmap)

 * [You Won’t Believe How Effective This Keyboard Layout Is](https://www.youtube.com/watch?v=8wZ8FRwOzhU) - Ben Vallack on his Ferris Sweep layout on Youtube
 * [Ben Vallack's Ferris Sweep layout](https://github.com/benvallack/34-QMK-Ferris-Sweep)
 * [Default layout for the Ferris Sweep](https://github.com/qmk/qmk_firmware/tree/master/keyboards/ferris/keymaps/default)

 * [Corne layout](https://i.imgur.io/o2E3s1u_d.webp?maxwidth=800&fidelity=high)
