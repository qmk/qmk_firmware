ToyKeeper's QMK Config
======================

Shared files used by more than one of ToyKeeper's QMK keymaps.


## Keymaps

* [Keychron Q65](../../keyboards/keychron/q65/q65_ansi_stm32l432_ec11/keymaps/toykeeper)
* [Keychron V1](../../keyboards/keychron/v1/v1_ansi_stm32l432_ec11/keymaps/toykeeper)
* [NovelKeys NK65](../../keyboards/novelkeys/nk65/keymaps/toykeeper)
* [Whitefox](../../keyboards/input_club/whitefox/keymaps/toykeeper)
* [Keyboardio Model-01](../../keyboards/keyboardio/model01/keymaps/toykeeper/)


## Boards / Layouts

Each layout can be edited on [KLE](keyboard-layout-editor.com) using the links
provided in each keymap's readme file.

Here's how each one looks:

### Q65

[KLE](http://www.keyboard-layout-editor.com/#/gists/9e5289cc338d78520da1495d697ed72a)

![TK Q65](http://toykeeper.net/keyboard/qmk/tk-q65-2022-11-25a.png)

### V1 / Q1

[KLE](http://www.keyboard-layout-editor.com/#/gists/cd13a756e9e519476489ab21df8140ba)

![Keychron V1](http://toykeeper.net/keyboard/qmk/keychron-v1/front.2.jpg)

![TK V1](http://toykeeper.net/keyboard/qmk/tk-v1-q1-2022-11-25a.png)

### NK65

[KLE](http://www.keyboard-layout-editor.com/#/gists/565ca8abb5825d160f962226fb9d58b7)

![NovelKeys NK65](http://toykeeper.net/keyboard/qmk/nk65-front-bright-blue.jpg)

![TK NK65](http://toykeeper.net/keyboard/qmk/tk-nk65-2022-11-25a.png)

### Whitefox

[KLE](http://www.keyboard-layout-editor.com/#/gists/25056bbe508ab0bb45d8e9688c23a478)

![TK Whitefox](http://toykeeper.net/keyboard/qmk/tk-whitefox-2022-11-25a.png)

### Keyboardio Model-01

[KLE](http://www.keyboard-layout-editor.com/#/gists/0b83353e391f27c7c19f82da0aecc56b)

![TK Keyboardio](http://toykeeper.net/keyboard/qmk/tk-keyboardio.2022-11-17a.png)


## Concept

Some layouts are designed so the user can stay in home row position all the
time, and anything outside that area is discouraged or even eliminated
entirely.  This is not that type of layout.

Instead, these layouts are designed to facilitate multiple different hand
positions for different tasks.  The user's hands are expected to move around
sometimes, like to tap something in the corner of the keyboard, or roll over to
the side, or even to hold the keyboard by the edges and navigate using only a
few keys at the edge.  Or drop both hands to the corners for extended mouse
use, with one hand moving the cursor and the other hand clicking buttons.  Or
use a touchpad with one hand, while clicking buttons on the keyboard with the
other.

Many oft-used keys and combos are placed where they can be used with one hand,
like while resting one's chin on their hand, or holding food in one hand.  The
arrow cluster in particular is built for this type of use.  The layout is also
designed to be couch-friendly, like typing on one's lap while using a media PC
with only the keyboard, no mouse... or leaving the keyboard to the side and
reaching over to start videos or scroll a page or whatever.

Additionally some concessions are made to keep the layout from diverging too
much from a traditional keyboard, to make it easier to switch between a nice
QMK board and notebooks or legacy hardware.  And some things are moved around
to help make mappings more consistent across different hardware models.


## Features

These keymaps attempt to provide a similar experience across several different
hardware models.  Some of the features available are:

  * Core layouts.  Multiple layouts selectable with hotkeys or the dipswitch on
    the back of the keyboard:
    * Qwerty
    * Dvorak
    * Colemak-DH-TK (my variant of Colemak-DH)
    * Undvorak (allows typing Qwerty when the host is remapped to Dvorak)
    * User can choose to swap U and I keys on Dvorak layer, for a small
      optimization.  In English it seems that "I" gets typed far more often
      than "U", so this can help reduce finger strain a bit.  These modes may
      be referred to as "Dvorak" and "Dvoriuk".

  * Extra layers
    * Two Fn layers -- Moon and Star.
    * Lockable layers for mouse keys and number pad, usually.
    * Other extras on hardware with extra keys:
      * Toggle what the F1-F12 row does.
      * Choose what the macro column keys do.
      * Third Fn layer when both palm keys are pressed.

  * RGB
    * Responsive RGB lighting shows active layers and modifiers, color-coded
      for clarity so they match the keymap diagrams.
    * RGB animation happens underneath the indicators.  The recommended mode is
      RGB_MATRIX_MULTISPLASH.
    * User can configure hue, saturation, value, effect type, and speed.

  * Easier access to frequently-used keys
    * The CapsLock key is Left Control.
    * Backspace and Backslash are swapped by default for easier access, but can
      be un-swapped.  There is also a left-thumb Backspace.
    * Star + the key next to it produces Shift+Insert, for pasting text.
    * Moon is placed where it can be pressed with a knuckle or palm.

  * Dual-role keys
    * Star doubles as a Home key.
    * LAlt is also backspace.
    * RCtl toggles the numpad layer.
    * RGUI is also RAlt, and sometimes MouseLock.
    * "Grave Escape" has the Escape key and Grave (`) / Tilde (~) on one key.
      * Tap normally for Esc
      * Shift for ~
      * Left GUI for `
      * Moon produces a Shift-Esc event (handy for Chrome task manager)

  * Smart Shift keys
    * Tap a shift key to emit a ( or ) paren.
    * Press both shift keys at the same time to enable CapsWord, which emits
      capital letters until you press a non-word key.  It's like CapsLock, but
      more practical and less annoying.  Useful for programmers who often need
      to type things like QMK_KEYWORD.

  * Ability to record and play macros.

  * Mouse keys
    * Easy access to mouse keys, for people who don't have a mouse nearby (or
      who simply don't want to use a mouse).
    * Mouse keys can be locked for single-finger access, and they glow while
      locked.
    * Extra key for MouseWarp (but really, it's just F23, and the user must map
      that to something in the host OS).
    * Uses the new "inertia" mode for more natural motion.  I'm biased since I
      wrote it, but I think it makes MouseKeys much more usable and I often go
      entire days without touching an actual mouse.
    * Accessible from multiple different hand positions, usually.
    * Mouse Warp feature depends on the host OS.  It simply sends F23 to the
      host... and the host must be configured to warp the cursor when that key
      is received.

  * Media / Launcher keys
    * Play/pause, prev song, next song
    * Launchers for My Computer and WWW Search
    * ... and whatever the user wants to map to F13 through F22

  * Knob (on some models)
    * Turn for mouse wheel up/down, or Star+turn for mouse wheel left/right.
    * Tap to change mode for extra column, if available.
    * Is near Shift, Ctrl, Alt, GUI, and Fn... to provide several knobby functions.

  * Dipswitch support, for easily switching between two layouts.

  * Physical design features
    * Built for 65% to 75% layouts.
    * All Fn keys are in the corners of the keyboard, with their functions in
      matching corners of the keymap diagram, and color-coded for easy
      readability.
    * Left-hand and right-hand access to Ctrl, Alt, and GUI... even though
      there are physically not enough mod keys.

  * Can dump out the firmware build info, for easy reference later.
  * Tap Star+Escape to enter bootloader mode (lightning bolt icon), for reflashing firmware.
  * Settings are remembered after unplugging.

*Note: VIA is not supported.*


## Known Issues

* Some settings aren't saved per dipswitch position:
  Backspace/Backslash toggle, Dvoriuk/Dvorak IU/UI toggle.


## Changes

*2022-11-26*

* First published version.

