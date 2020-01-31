# Word Per Minute (WPM) Calculcation

The WPM feature uses time between keystrokes to compute a rolling average words
per minute rate and makes this available for various uses.

Enable the WPM system by adding this to your `rules.mk`:

    WPM_ENABLE = yes

For split keyboards using soft serial, the computed WPM
score will be available on the master AND slave half.

## Functions

uint8_t get_current_wpm(void);

This function returns the current WPM as an unsigned integer.
