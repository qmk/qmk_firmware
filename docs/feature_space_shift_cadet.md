## Space Cadet Shift Enter: The future, built in

Based on the Space Cadet Shift by Steve Losh [described](http://stevelosh.com/blog/2012/10/a-modern-space-cadet/) 
Essentially, you hit the Shift on its own, and it acts as the enter key. When hit with other keys, the Shift key keeps working as it always does. Yes, it's as cool as it sounds. This solution works better than using a macro since the timers defined in quantum allow us to tell when another key is pressed, rather than just having a janky timer than results in accidental endlines. 

To use it, use `KC_SFTENT` (Shift, Enter) for any Shift on your keymap.

It's defaulted to work on US keyboards, but if you'd like to use a different key for Enter, you can define those in your `config.h` like this:

    #define SFTENT_KEY KC_ENT


The only other thing you're going to want to do is create a `rules.mk` in your keymap directory and set the following:

```
COMMAND_ENABLE   = no  # Commands for debug and configuration
```

This is just to keep the keyboard from going into command mode when you hold both Shift keys at the same time.





PLEASE NOTE: this feature uses the same timers as the Space Cadet Shift feature, so using them in tandem may produce unwanted results. 

