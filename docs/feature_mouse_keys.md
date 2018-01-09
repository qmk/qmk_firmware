# Mousekeys


Mousekeys is a feature that allows you to emulate a mouse using your keyboard. You can move the pointer around at 3 speeds, click up to 5 buttons, and even scroll in all 4 directions.

## Enable Mousekeys

To enable the mouse key functionality, add the following line to your keymap's `Makefile`:

```
MOUSEKEY_ENABLE = yes
```

### Mapping Mouse Actions to Keyboard Keys

You can use these keycodes within your keymap to map button presses to mouse actions:

|Key             |Aliases  |Description                        |
|----------------|---------|-----------------------------------|
|`KC_MS_UP`      |`KC_MS_U`|Mouse Cursor Up                    |
|`KC_MS_DOWN`    |`KC_MS_D`|Mouse Cursor Down                  |
|`KC_MS_LEFT`    |`KC_MS_L`|Mouse Cursor Left                  |
|`KC_MS_RIGHT`   |`KC_MS_R`|Mouse Cursor Right                 |
|`KC_MS_BTN1`    |`KC_BTN1`|Mouse Button 1                     |
|`KC_MS_BTN2`    |`KC_BTN2`|Mouse Button 2                     |
|`KC_MS_BTN3`    |`KC_BTN3`|Mouse Button 3                     |
|`KC_MS_BTN4`    |`KC_BTN4`|Mouse Button 4                     |
|`KC_MS_BTN5`    |`KC_BTN5`|Mouse Button 5                     |
|`KC_MS_WH_UP`   |`KC_WH_U`|Mouse Wheel Up                     |
|`KC_MS_WH_DOWN` |`KC_WH_D`|Mouse Wheel Down                   |
|`KC_MS_WH_LEFT` |`KC_WH_L`|Mouse Wheel Left                   |
|`KC_MS_WH_RIGHT`|`KC_WH_R`|Mouse Wheel Right                  |
|`KC_MS_ACCEL0`  |`KC_ACL0`|Set mouse acceleration to 0(slow)  |
|`KC_MS_ACCEL1`  |`KC_ACL1`|Set mouse acceleration to 1(medium)|
|`KC_MS_ACCEL2`  |`KC_ACL2`|Set mouse acceleration to 2(fast)  |


## Configuring the Behavior of Mousekeys

In your keymap's `config.h`, you can precisely define 3 different speeds for both the cursor and the mouse wheel, and also whether speed selection is momentary or tap-to-select.
For each speed, you can specify how many milliseconds you want between reports(interval), and how far you want to it to move per report(offset).

For example:

```
#define MK_MOMENTARY_ACCEL // comment this out for tap-to-select acceleration
// cursor speeds:
#define MK_C_OFFSET_SLOW     1 // pixels
#define MK_C_INTERVAL_SLOW 100 // milliseconds
#define MK_C_OFFSET_MED      4
#define MK_C_INTERVAL_MED   16
#define MK_C_OFFSET_FAST    12
#define MK_C_INTERVAL_FAST  16
// scroll wheel speeds:
#define MK_W_OFFSET_SLOW     1 // wheel clicks
#define MK_W_INTERVAL_SLOW 400 // milliseconds
#define MK_W_OFFSET_MED      1
#define MK_W_INTERVAL_MED  200
#define MK_W_OFFSET_FAST     1
#define MK_W_INTERVAL_FAST 100
```

Medium values will be used as the default or unmodified speed.
The speed at which both the cursor and scrolling move can be selected with KC_ACL0, KC_ACL1, KC_ACL2 for slow, medium, and fast. However, if you leave MK_MOMENTARY_ACCEL defined then there is no need to ever send KC_ACL1, since that will be the unmodified speed.
