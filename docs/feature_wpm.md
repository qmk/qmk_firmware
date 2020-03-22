# Word Per Minute (WPM) Calculcation

The WPM feature uses time between keystrokes to compute a rolling average words
per minute rate and makes this available for various uses.

Enable the WPM system by adding this to your `rules.mk`:

    WPM_ENABLE = yes

For split keyboards using soft serial, the computed WPM
score will be available on the master AND slave half.

## Public Functions

`uint8_t get_current_wpm(void);`
This function returns the current WPM as an unsigned integer.


## Customized keys for WPM calc

By default, the WPM score only includes letters, numbers, space and some
punctuation.  If you want to change the set of characters considered as part of
the WPM calculation, you can implement `wpm_keycode_user(uint16_t keycode)`
and return true for any characters you would like included in the calculation,
or false to not count that particular keycode.
