# The extra special ergodox build for MacOS Sierra caps lock users

###Do you
- Hate the OSX / MacOS caps lock delay?
- Have an ergodox?

###Then this might just be for you!

[This](http://apple.stackexchange.com/questions/81234/how-to-remove-caps-lock-delay-on-apple-macbook-pro-aluminum-keyboard)
and [this](http://sleepycow.org/2014/07/removing-the-caps-lock-delay-on-a-macbook/)
are good workarounds for the caps lock delay, however none of these
work on Sierra.  This abomination of a keymap simulates capslock to the best
of its abilities.
This means that it keeps track of caps lock state internally rather than
sending a caps lock keypress to the OS.  It is smart enough to check for
modifiers, such as Control being held down, and stop it with the hanky panky
and just send on the key event unmolested even if FakeCaps is enabled.  And
since the macro isn't even registered on the non-alphas, it will not affect
them regardless.  Only in the event that FakeCaps is enabled and an alpha key
is pressed will it sneak in a shift keydown before the alpha keydown and
immediately afterward sneaks in a shift keyup.  Generally this works well,
however there is one known issue:

- Holding down a key will only have the first character in caps.  For instance,
  with caps lock on, if you hold down the 'a' key, you get:

  ```
  Aaaaaaaaaaaaaaaaaa
  ```

I have only tested this on an original Ergodox with a Teensy 2.0.

####Some other small tweaks
 - Layer 0 board light is off
 - Layer 1 board light is on solid
 - Layer 2 board light blinks at speed controlled by BLINK_BASE

![osx whiskey tango foxtrot](https://i.imgur.com/yQl1DFe.png)
