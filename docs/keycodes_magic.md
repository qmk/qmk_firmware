# Magic Keycodes :id=magic-keycodes

**Magic Keycodes** are prefixed with `MAGIC_`, and allow you to access the functionality of the deprecated Bootmagic feature *after* your keyboard has initialized. To use the keycodes, assign them to your keymap as you would any other keycode.

|Key                               |Aliases  |Description                                                               |
|----------------------------------|---------|--------------------------------------------------------------------------|
|`MAGIC_SWAP_CONTROL_CAPSLOCK`     |`CL_SWAP`|Swap Caps Lock and Left Control                                           |
|`MAGIC_UNSWAP_CONTROL_CAPSLOCK`   |`CL_NORM`|Unswap Caps Lock and Left Control                                         |
|`MAGIC_CAPSLOCK_TO_CONTROL`       |`CL_CTRL`|Treat Caps Lock as Control                                                |
|`MAGIC_UNCAPSLOCK_TO_CONTROL`     |`CL_CAPS`|Stop treating Caps Lock as Control                                        |
|`MAGIC_SWAP_LCTL_LGUI`            |`LCG_SWP`|Swap Left Control and GUI                                                 |
|`MAGIC_UNSWAP_LCTL_LGUI`          |`LCG_NRM`|Unswap Left Control and GUI                                               |
|`MAGIC_SWAP_RCTL_RGUI`            |`RCG_SWP`|Swap Right Control and GUI                                                |
|`MAGIC_UNSWAP_RCTL_RGUI`          |`RCG_NRM`|Unswap Right Control and GUI                                              |
|`MAGIC_SWAP_CTL_GUI`              |`CG_SWAP`|Swap Control and GUI on both sides                                        |
|`MAGIC_UNSWAP_CTL_GUI`            |`CG_NORM`|Unswap Control and GUI on both sides                                      |
|`MAGIC_TOGGLE_CTL_GUI`            |`CG_TOGG`|Toggle Control and GUI swap on both sides                                 |
|`MAGIC_SWAP_LALT_LGUI`            |`LAG_SWP`|Swap Left Alt and GUI                                                     |
|`MAGIC_UNSWAP_LALT_LGUI`          |`LAG_NRM`|Unswap Left Alt and GUI                                                   |
|`MAGIC_SWAP_RALT_RGUI`            |`RAG_SWP`|Swap Right Alt and GUI                                                    |
|`MAGIC_UNSWAP_RALT_RGUI`          |`RAG_NRM`|Unswap Right Alt and GUI                                                  |
|`MAGIC_SWAP_ALT_GUI`              |`AG_SWAP`|Swap Alt and GUI on both sides                                            |
|`MAGIC_UNSWAP_ALT_GUI`            |`AG_NORM`|Unswap Alt and GUI on both sides                                          |
|`MAGIC_TOGGLE_ALT_GUI`            |`AG_TOGG`|Toggle Alt and GUI swap on both sides                                     |
|`MAGIC_NO_GUI`                    |`GUI_OFF`|Disable the GUI keys                                                      |
|`MAGIC_UNNO_GUI`                  |`GUI_ON` |Enable the GUI keys                                                       |
|`MAGIC_TOGGLE_GUI`                |`GUI_TOG`|Toggles the status of the GUI keys                                        |
|`MAGIC_SWAP_GRAVE_ESC`            |`GE_SWAP`|Swap <code>&#96;</code> and Escape                                        |
|`MAGIC_UNSWAP_GRAVE_ESC`          |`GE_NORM`|Unswap <code>&#96;</code> and Escape                                      |
|`MAGIC_SWAP_BACKSLASH_BACKSPACE`  |`BS_SWAP`|Swap `\` and Backspace                                                    |
|`MAGIC_UNSWAP_BACKSLASH_BACKSPACE`|`BS_NORM`|Unswap `\` and Backspace                                                  |
|`MAGIC_HOST_NKRO`                 |`NK_ON`  |Enable N-key rollover                                                     |
|`MAGIC_UNHOST_NKRO`               |`NK_OFF` |Disable N-key rollover                                                    |
|`MAGIC_TOGGLE_NKRO`               |`NK_TOGG`|Toggle N-key rollover                                                     |
|`MAGIC_EE_HANDS_LEFT`             |`EH_LEFT`|Set the master half of a split keyboard as the left hand (for `EE_HANDS`) |
|`MAGIC_EE_HANDS_RIGHT`            |`EH_RGHT`|Set the master half of a split keyboard as the right hand (for `EE_HANDS`)|
