
// Behaviors That Can Be Configured

#define TAPPING_TERM 250
        // how long before a tap becomes a hold, if set above 500, a key tapped during the tapping term will turn it into a hold too

#define PERMISSIVE_HOLD
       // makes tap and hold keys trigger the hold if another key is pressed before releasing, even if it hasn't hit the TAPPING_TERM
#define IGNORE_MOD_TAP_INTERRUPT
        // makes it possible to do rolling combos (zx) with keys that convert to other keys on hold, by enforcing the TAPPING_TERM for both keys.

/*
    #define TAPPING_TERM_PER_KEY
        // enables handling for per key TAPPING_TERM settings
    #define RETRO_TAPPING
        // tap anyway, even after TAPPING_TERM, if there was no other key interruption between press and release
        // See Retro Tapping for details
    #define TAPPING_TOGGLE 2
        // how many taps before triggering the toggle
    #define TAPPING_FORCE_HOLD
        // makes it possible to use a dual role key as modifier shortly after having been tapped
        // See Hold after tap
        // Breaks any Tap Toggle functionality (TT or the One Shot Tap Toggle)
    #define LEADER_TIMEOUT 300
        // how long before the leader key times out
        // If you're having issues finishing the sequence before it times out, you may need to increase the timeout setting. Or you may want to enable the LEADER_PER_KEY_TIMING option, which resets the timeout after each key is tapped.
    #define LEADER_PER_KEY_TIMING
        // sets the timer for leader key chords to run on each key press rather than overall
    #define LEADER_KEY_STRICT_KEY_PROCESSING
        // Disables keycode filtering for Mod-Tap and Layer-Tap keycodes. Eg, if you enable this, you would need to specify MT(MOD_CTL, KC_A) if you want to use KC_A.
    #define ONESHOT_TIMEOUT 300
        // how long before oneshot times out
    #define ONESHOT_TAP_TOGGLE 2
        // how many taps before oneshot toggle is triggered
    #define QMK_KEYS_PER_SCAN 4
        // Allows sending more than one key per scan. By default, only one key event gets sent via process_record() per scan. This has little impact on most typing, but if you're doing a lot of chords, or your scan rate is slow to begin with, you can have some delay in processing key events. Each press and release is a separate event. For a keyboard with 1ms or so scan times, even a very fast typist isn't going to produce the 500 keystrokes a second needed to actually get more than a few ms of delay from this. But if you're doing chording on something with 3-4ms scan times? You probably want this.
    #define COMBO_COUNT 2
        // Set this to the number of combos that you're using in the Combo feature.
    #define COMBO_TERM 200
        // how long for the Combo keys to be detected. Defaults to TAPPING_TERM if not defined.
    #define TAP_CODE_DELAY 100
        // Sets the delay between register_code and unregister_code, if you're having issues with it registering properly (common on VUSB boards). The value is in milliseconds.
    #define TAP_HOLD_CAPS_DELAY 80
        // Sets the delay for Tap Hold keys (LT, MT) when using KC_CAPSLOCK keycode, as this has some special handling on MacOS. The value is in milliseconds, and defaults to 80 ms if not defined. For macOS, you may want to set this to 200 or higher.
*/
