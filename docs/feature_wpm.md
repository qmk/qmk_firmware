# Word Per Minute (WPM) Calculcation

The WPM feature uses time between keystrokes to compute a rolling average words per minute rate and makes this available for various uses.

Enable the WPM system by adding this to your `rules.mk`:

    WPM_ENABLE = yes

For split keyboards using soft serial, the computed WPM score will be available on the master AND slave half.

## Configuration

| Define                       | Default       | Description                                                                              |
|------------------------------|---------------|------------------------------------------------------------------------------------------|
| `WPM_ESTIMATED_WORD_SIZE`    | `5`           | This is the value used when estimating average word size (for regression and normal use) |
| `WPM_ALLOW_COUNT_REGRESSION` | _Not defined_ | If defined allows the WPM to be decreased when hitting Delete or Backspace               |
| `WPM_UNFILTERED`             | _Not defined_ | If undefined (the default), WPM values will be smoothed to avoid sudden changes in value |
| `WPM_SAMPLE_SECONDS`         | `5`           | This defines how many seconds of typing to average, when calculating WPM                 |
| `WPM_SAMPLE_PERIODS`         | `50`          | This defines how many sampling periods to use when calculating WPM                       |
| `WPM_LAUNCH_CONTROL`         | _Not defined_ | If defined, WPM values will be calculated using partial buffers when typing begins       |

'WPM_UNFILTERED' is potentially useful if you're filtering data in some other way (and also because it reduces the code required for the WPM feature), or if reducing measurement latency to a minimum is important for you.

Increasing 'WPM_SAMPLE_SECONDS' will give more smoothly changing WPM values at the expense of slightly more latency to the WPM calculation.

Increasing 'WPM_SAMPLE_PERIODS' will improve the smoothness at which WPM decays once typing stops, at a cost of approximately this many bytes of firmware space.

If 'WPM_LAUNCH_CONTROL' is defined, whenever WPM drops to zero, the next time typing begins WPM will be calculated based only on the time since that typing began, instead of the whole period of time specified by WPM_SAMPLE_SECONDS.  This results in reaching an accurate WPM value much faster, even when filtering is enabled and a large WPM_SAMPLE_SECONDS value is specified.

## Public Functions

|Function                  |Description                                       |
|--------------------------|--------------------------------------------------|
|`get_current_wpm(void)`   | Returns the current WPM as a value between 0-255 |
|`set_current_wpm(x)`      | Sets the current WPM to `x` (between 0-255)      |

## Callbacks

By default, the WPM score only includes letters, numbers, space and some punctuation.  If you want to change the set of characters considered as part of the WPM calculation, you can implement your own `bool wpm_keycode_user(uint16_t keycode)` and return true for any characters you would like included in the calculation, or false to not count that particular keycode.

For instance, the default is:

```c
bool wpm_keycode_user(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) || (keycode >= QK_MODS && keycode <= QK_MODS_MAX)) {
        keycode = keycode & 0xFF;
    } else if (keycode > 0xFF) {
        keycode = 0;
    }
    if ((keycode >= KC_A && keycode <= KC_0) || (keycode >= KC_TAB && keycode <= KC_SLSH)) {
        return true;
    }

    return false;
}
```

Additionally, if `WPM_ALLOW_COUNT_REGRESSION` is defined, there is the `uint8_t wpm_regress_count(uint16_t keycode)` function that allows you to decrease the WPM. This is useful if you want to be able to penalize certain keycodes (or even combinations). 

```c
__attribute__((weak)) uint8_t wpm_regress_count(uint16_t keycode) {
    bool weak_modded = (keycode >= QK_LCTL && keycode < QK_LSFT) || (keycode >= QK_RCTL && keycode < QK_RSFT);
    
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) || (keycode >= QK_MODS && keycode <= QK_MODS_MAX)) {
        keycode = keycode & 0xFF;
    } else if (keycode > 0xFF) {
        keycode = 0;
    }
    if (((get_mods() | get_oneshot_mods()) & MOD_MASK_CTRL} || weak_modded) && (keycode == KC_DEL || keycode == KC_BSPC)) {
        return WPM_ESTIMATED_WORD_SIZE;
    }
    if (keycode == KC_DEL || keycode == KC_BSPC) {
        return 1;
    }
}
```
