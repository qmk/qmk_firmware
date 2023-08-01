# [nfriend](https://gitlab.com/nfriend)'s ErgoDox EZ configuration

![nfriend's ErgoDox EZ keymap](https://i.imgur.com/CMMmdBc.png)

[View this keymap on
keyboard-layout-editor.com.](http://www.keyboard-layout-editor.com/#/gists/01283b322a647c96ef75955a9b0bac68)

Color legend:

-   **Black:** Primary layer.
-   **Blue:** Symbol layer. Accessed by holding either of the <kbd>to sym</kbd>
    keys on either end of the keyboard.
-   **Green:** Numpad layer. Accessed by holding the <kbd>to numpad</kbd> key.
-   **Red:** Arrow layer. Accessed by holding either of the <kbd>to arrows</kbd>
    thumb keys.
-   **Teal:** Window management layer. Accessed by holding either of the <kbd>to
    WM</kbd> thumb keys.
    -   Note: this layer is not pictured on this keymap since is tightly coupled
        to [Magnet](https://magnet.crowdcafe.com/).
-   **Yellow:** Miscellaneous layer. Includes LED control, layout toggling
    (Colemak/Dvorak/QWERTY), platform toggling (Windows/Mac), and other
    experimental features.
    -   Note: this layer is only partially pictured on this keymap

## Caveats

In its current state, this keymap is fairly Mac-centric. Some of the features
implemented in the Mac layers have not yet been ported to the corresponding
Windows layers.

## Building

To build this layout, open a command window in the root directory of this
repository and run:

```bash
make ergodox_ez:nfriend
```

This will create a `.build/ergodox_ez_nfriend.hex` file which can be flashed
using the [Teensy loader](https://www.pjrc.com/teensy/loader.html). After the
`.hex` file has been loaded into Teensy, the keyboard can be reprogrammed by
pressing the bottom-right key of the right half of the keyboard and the
top-right key of the left half (the <kbd>RESET</kbd> key in the screenshot
above).

## Developing

Use the template in `./template.c` to help create new layers quickly.

This layout was originally based on [this EZ Configurator
configuration](https://configure.ergodox-ez.com/ergodox-ez/layouts/x9MWL/latest/0).
