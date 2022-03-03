## Keyboard Layout Templates

This borrows from @jola5's "Not quite neo" code and from Drashnas userspace. This allows to maintain blocks of keymaps in the userspace, so they can be modified in the userspace, and changes reflect in all of the keyboards, at once.

This makes adding tap/hold mods, or other special keycodes or functions to all keyboards super easy, as it's done to all of them at once. 

The caveat here is that the keymap needs a processor/wrapper, as it doesn't like the substitutions. However, this is as simple as just pushing it through a define. For instance:

`#define LAYOUT_ergodox_wrapper(...)   LAYOUT_ergodox(__VA_ARGS__)`

Once that's been done and you've switched the keymaps to use the "wrapper", it will read the substitution blocks just fine.
