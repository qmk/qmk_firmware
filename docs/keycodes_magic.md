# Magic Keycodes {#magic-keycodes}

**Magic Keycodes** are prefixed with `MAGIC_`, and allow you to access the functionality of the deprecated Bootmagic feature *after* your keyboard has initialized. To use the keycodes, assign them to your keymap as you would any other keycode.

|Key                                  |Aliases  |Description                                                               |
|-------------------------------------|---------|--------------------------------------------------------------------------|
|`QK_MAGIC_SWAP_CONTROL_CAPS_LOCK`    |`CL_SWAP`|Swap Caps Lock and Left Control                                           |
|`QK_MAGIC_UNSWAP_CONTROL_CAPS_LOCK`  |`CL_NORM`|Unswap Caps Lock and Left Control                                         |
|`QK_MAGIC_TOGGLE_CONTROL_CAPS_LOCK`  |`CL_TOGG`|Toggle Caps Lock and Left Control swap                                    |
|`QK_MAGIC_CAPS_LOCK_AS_CONTROL_ON`   |`CL_CTRL`|Treat Caps Lock as Control                                                |
|`QK_MAGIC_CAPS_LOCK_AS_CONTROL_OFF`  |`CL_CAPS`|Stop treating Caps Lock as Control                                        |
|`QK_MAGIC_SWAP_ESCAPE_CAPS_LOCK`     |`EC_SWAP`|Swap Caps Lock and Escape                                                 |
|`QK_MAGIC_UNSWAP_ESCAPE_CAPS_LOCK`   |`EC_NORM`|Unswap Caps Lock and Escape                                               |
|`QK_MAGIC_TOGGLE_ESCAPE_CAPS_LOCK`   |`EC_TOGG`|Toggle Caps Lock and Escape swap                                          |
|`QK_MAGIC_SWAP_LCTL_LGUI`            |`CG_LSWP`|Swap Left Control and GUI                                                 |
|`QK_MAGIC_UNSWAP_LCTL_LGUI`          |`CG_LNRM`|Unswap Left Control and GUI                                               |
|`QK_MAGIC_SWAP_RCTL_RGUI`            |`CG_RSWP`|Swap Right Control and GUI                                                |
|`QK_MAGIC_UNSWAP_RCTL_RGUI`          |`CG_RNRM`|Unswap Right Control and GUI                                              |
|`QK_MAGIC_SWAP_CTL_GUI`              |`CG_SWAP`|Swap Control and GUI on both sides                                        |
|`QK_MAGIC_UNSWAP_CTL_GUI`            |`CG_NORM`|Unswap Control and GUI on both sides                                      |
|`QK_MAGIC_TOGGLE_CTL_GUI`            |`CG_TOGG`|Toggle Control and GUI swap on both sides                                 |
|`QK_MAGIC_SWAP_LALT_LGUI`            |`AG_LSWP`|Swap Left Alt and GUI                                                     |
|`QK_MAGIC_UNSWAP_LALT_LGUI`          |`AG_LNRM`|Unswap Left Alt and GUI                                                   |
|`QK_MAGIC_SWAP_RALT_RGUI`            |`AG_RSWP`|Swap Right Alt and GUI                                                    |
|`QK_MAGIC_UNSWAP_RALT_RGUI`          |`AG_RNRM`|Unswap Right Alt and GUI                                                  |
|`QK_MAGIC_SWAP_ALT_GUI`              |`AG_SWAP`|Swap Alt and GUI on both sides                                            |
|`QK_MAGIC_UNSWAP_ALT_GUI`            |`AG_NORM`|Unswap Alt and GUI on both sides                                          |
|`QK_MAGIC_TOGGLE_ALT_GUI`            |`AG_TOGG`|Toggle Alt and GUI swap on both sides                                     |
|`QK_MAGIC_GUI_OFF`                   |`GU_OFF` |Disable the GUI keys                                                      |
|`QK_MAGIC_GUI_ON`                    |`GU_ON`  |Enable the GUI keys                                                       |
|`QK_MAGIC_TOGGLE_GUI`                |`GU_TOGG`|Toggles the status of the GUI keys                                        |
|`QK_MAGIC_SWAP_GRAVE_ESC`            |`GE_SWAP`|Swap <code>&#96;</code> and Escape                                        |
|`QK_MAGIC_UNSWAP_GRAVE_ESC`          |`GE_NORM`|Unswap <code>&#96;</code> and Escape                                      |
|`QK_MAGIC_SWAP_BACKSLASH_BACKSPACE`  |`BS_SWAP`|Swap `\` and Backspace                                                    |
|`QK_MAGIC_UNSWAP_BACKSLASH_BACKSPACE`|`BS_NORM`|Unswap `\` and Backspace                                                  |
|`QK_MAGIC_TOGGLE_BACKSLASH_BACKSPACE`|`BS_TOGG`|Toggle `\` and Backspace swap state                                       |
|`QK_MAGIC_NKRO_ON`                   |`NK_ON`  |Enable N-key rollover                                                     |
|`QK_MAGIC_NKRO_OFF`                  |`NK_OFF` |Disable N-key rollover                                                    |
|`QK_MAGIC_TOGGLE_NKRO`               |`NK_TOGG`|Toggle N-key rollover                                                     |
|`QK_MAGIC_EE_HANDS_LEFT`             |`EH_LEFT`|Set the master half of a split keyboard as the left hand (for `EE_HANDS`) |
|`QK_MAGIC_EE_HANDS_RIGHT`            |`EH_RGHT`|Set the master half of a split keyboard as the right hand (for `EE_HANDS`)|
