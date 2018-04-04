# not-quite-neo

This is my personal take on porting the [neo2 layout](https://www.neo-layout.org/) to support both a ergodox (infinity) and a planck keyboard. Some sacrifices needed to be made, hence this layout is not-quite-neo.

## Use case
My use case is simple:

* I want to use neo2 (or a keymap as close as possible) on any computer I can plug my keyboards in. Because installing the neo2 SW driver is often not a acceptable solution.
* Since most computers I work on (colleagues, family, etc.) use a de-DE keymap, I can not use the official neo2 implementation, because it relies on a us layout and I often times do not even posses the administration rights to change that.
* neo2 makes use of most of the keys of a standard 104 key keyboard, especially for supporting the planck I needed to deviate from the original neo2 layout in order to fit everything I wanted.

Therefore, I put all reusable code in the users/not-quite-neo directory and created a custom not-quite-neo keymap for the planck and the ergodox infinity keyboard respectively.

## Pitfalls
Mind, since neo2 is a SW driver supported layout it offers a lot of features that are hard to support in hardware (especially the fancy utf stuff with math symbols and greek letters etc.). 

Right now this implementation only incompletely supports neo2 layers 1 to 4.

The biggest difference is probably the support for the German Umlauts ä, ö, ü and the ß. Since we rely on a smaller number of keys some glyphs needed to be created otherwise. See the implementation in [nqn-basic-layout.h](nqn-basic-layout.h) for details.

## Keyboards and keymaps

You can find the *not-quite-neo* keymap for the ergodox infinity under [qmk_firmware/keyboards/ergodox_infinity/keymaps/not-quite-neo/](../../keyboards/ergodox_infinity/keymaps/not-quite-neo/readme.md). Respectively the keymap for the planck resides in [qmk_firmware/keyboards/planck/keymaps/not-quite-neo/](../../keyboards/planck/keymaps/not-quite-neo/readme.md)
 .