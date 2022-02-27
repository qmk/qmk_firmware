# Tap Dancing to different beats.
Tap Dance is constrained normally by `TAPPING_TERM` defined in your keyboard's config.h This proves to be challenging to work with when sometimes you just need more time to tap out your dance, or even a different "beat".



- Implementing `uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record)`, you can set a specific tap dance to have a longer or shorter tap in between your taps, giving you more, or less, time in between each tap. The return value should be the same type and range of values that one would put into the `TAPPING_TERM` definition in the config.h file.
