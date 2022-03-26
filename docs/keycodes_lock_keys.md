|Key                     |Aliases                        |Description                            |Windows      |macOS        |Linux<sup>1</sup>|
|------------------------|-------------------------------|---------------------------------------|-------------|-------------|-----------------|
|`KC_CAPS_LOCK`          |`KC_CAPS`                      |Caps Lock                              |✔            |✔            |✔                |
|`KC_SCROLL_LOCK`        |`KC_SCRL`, `KC_BRMD`           |Scroll Lock, Brightness Down (macOS)   |✔            |✔<sup>2</sup>|✔                |
|`KC_NUM_LOCK`           |`KC_NUM`                       |Keypad Num Lock and Clear              |✔            |✔            |✔                |
|`KC_LOCKING_CAPS_LOCK`  |`KC_LCAP`                      |Locking Caps Lock                      |✔            |✔            |                 |
|`KC_LOCKING_NUM_LOCK`   |`KC_LNUM`                      |Locking Num Lock                       |✔            |✔            |                 |
|`KC_LOCKING_SCROLL_LOCK`|`KC_LSCR`                      |Locking Scroll Lock                    |✔            |✔            |                 |

<sup>1. The Linux kernel HID driver recognizes [nearly all keycodes](https://github.com/torvalds/linux/blob/master/drivers/hid/hid-input.c), but the default bindings depend on the DE/WM.</sup><br/>
<sup>2. Treated as F13-F15.</sup><br/>