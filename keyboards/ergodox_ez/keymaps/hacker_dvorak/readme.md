# [Ergodox EZ Hacker Dvorak Layout](https://configure.ergodox-ez.com/layouts/Wadz/latest/0)

Inspired by the [*Programmer Dvorak*](https://www.kaufmann.no/roland/dvorak) keyboard layout, cherry picked ideas from other layouts in the [EZ Repository](https://configure.ergodox-ez.com/search?q=dvorak&legacy=true), a character distribution [heatmap vizualizer](https://run.plnkr.co/plunks/5EEO8nJ2wRzYAfT3), my own subjective use cases and lots of trial and error.

## Setup

Configure your OS keyboard layout to US, or the keymap will be incorrect.

## Limitations

I plan to use [QMK](https://docs.qmk.fm) in the future, in order to overcome some limitations of the Ergodox EZ [graphical configurator](https://configure.ergodox-ez.com/layouts/default/latest/0)), however I will defer that, until more progress is made to the new [configurator](https://medium.com/the-ergo/the-configurator-is-out-of-beta-e107aec80cae).

## Layers

1. Dvorak
  * US Dvorak layout.
  * All symbols (including shifted symbols).
  * All modifier are dual keys positioned near the home row.
2. Querty
  * Used to overcome the limitation pointed above, when your OS layout is set to Dvorak instead of US, this way you can use 
    Standard Dvorak (available by default on all the main operating systems) on other normal keybdoards and Hacker Dvorak on 
    the Ergodox EZ Shine at the same time, without changing back and forth tho OS layout.
3. Gaming
  * Still in development.
  * Left side is mainly "normal" Qwerty.
  * Right side is mainly for movement, either using the mouse, the arrow keys, the number pad or the `H`, `J`, `K`, `L` as       direction keys.
4. Arrows
  * Arrow keys navigation.
  * All modifier keys.
  * Common text edititng shortcuts (doesn't work for MacOS).
5. Mouse
  * Mouse navigation.
  * All modifier keys.
  * Common text edititng shortcuts (doesn't work for MacOS).
6. Numpad
  * ATM style numpad.
  * All modifier keys.
  * Letters from `A` to `F` for hexadecimal numbers (`B` is also used for binary numeric literals in most programming 
    languages, ie. `0b11001`).
  * `X` for hexadecimal numeric literals in most programming languages, ie. `0xbeef`.
  * `O` for octal numeric literals in most programming languages, ie `0o123`.
  * `J` for complex numeric literals in Python, ie. `3j`.
  * `I` and `M` for complex Julia numeric literals, ie. `3im`.
  * Common symbols for mathematical operations.
7. Hyper Fn
  * Useful for custom global shortcuts.
8. Media Fn
  * Media keys.
  * Function keys.
  * EZ Shine keys.
9. Meh Fn
  * Useful for custom application shortcuts.
10. Meh Fn +
  * Useful for custom standard shortcuts.
  
## To Do

Add images.

***

Please comment below if you have any ideas or suggestions. If you have used this layout or used it as a base, I'd love to hear about your experience!