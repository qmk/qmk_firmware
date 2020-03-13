# Tap Dancing to different beats.
Tap Dance is constrained normally by `TAPPING_TERM` defined in your keyboard's config.h This proves to be challenging to work with when sometimes you just need more time to tap out your dance, or even a different "beat".



- `ACTION_TAP_DANCE_FN_ADVANCED_TIME(user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset, tap_specific_tapping_term)` : This works the same as `ACTION_TAP_DANCE_FN_ADVANCED` just with the extra `tap_specific_tapping_term` arguement at the end. This way you can set a specific tap dance to have a longer or shorter tap in between your taps, giving you more, or less, time in between each tap.   


`tap_specific_tapping_term` should be the same type and range of values that one would put into the `TAPPING_TERM` definition in the config.h file.
