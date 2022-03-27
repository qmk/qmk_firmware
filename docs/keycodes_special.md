|Key                     |Aliases                        |Description                            |Windows      |macOS        |Linux<sup>1</sup>|
|------------------------|-------------------------------|---------------------------------------|-------------|-------------|-----------------|
|`KC_NO`                 |`XXXXXXX`                      |Ignore this key (NOOP)                 |*N/A*        |*N/A*        |*N/A*            |
|`KC_TRANSPARENT`        |`KC_TRNS`, `_______`           |Use the next lowest non-transparent key|*N/A*        |*N/A*        |*N/A*            |

<sup>1. The Linux kernel HID driver recognizes [nearly all keycodes](https://github.com/torvalds/linux/blob/master/drivers/hid/hid-input.c), but the default bindings depend on the DE/WM.</sup><br/>