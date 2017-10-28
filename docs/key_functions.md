# Quick Aliases To Common Actions

Your keymap can include shortcuts to common operations (called "function actions" in tmk).

These functions work the same way that their `ACTION_*` functions do - they're just quick aliases. To dig into all of the tmk `ACTION_*` functions, please see the [TMK documentation](keymap.md#2-action).

Instead of using `FNx` when defining `ACTION_*` functions, you can use `F(x)` - the benefit here is being able to use more than 32 function actions (up to 4096), if you happen to need them.

### Limits of these aliases

Currently, the keycodes able to used with these functions are limited to the TMK ones, meaning you can't use keycodes like `KC_TILD`, or anything greater than 0xFF. For a full list of the keycodes able to be used, [see this list](keycode.txt).

### Switching and toggling layers

`MO(layer)` - momentary switch to *layer*. As soon as you let go of the key, the layer is deactivated and you pop back out to the previous layer. When you apply this to a key, that same key must be set as `KC_TRNS` on the destination layer. Otherwise, you won't make it back to the original layer when you release the key (and you'll get a keycode sent). You can only switch to layers *above* your current layer. If you're on layer 0 and you use `MO(1)`, that will switch to layer 1 just fine. But if you include `MO(3)` on layer 5, that won't do anything for you -- because layer 3 is lower than layer 5 on the stack.

`OSL(layer)` - momentary switch to *layer*, as a one-shot operation. So if you have a key that's defined as `OSL(1)`, and you tap that key, then only the very next keystroke would come from layer 1. You would drop back to layer zero immediately after that one keystroke. That's handy if you have a layer full of custom shortcuts -- for example, a dedicated key for closing a window. So you tap your one-shot layer mod, then tap that magic 'close window' key, and keep typing like a boss. Layer 1 would remain active as long as you hold that key down, too (so you can use it like a momentary toggle-layer key with extra powers).

`LT(layer, kc)` - momentary switch to *layer* when held, and *kc* when tapped. Like `MO()`, this only works upwards in the layer stack (`layer` must be higher than the current layer).

`TG(layer)` - toggles a layer on or off. As with `MO()`, you should set this key as `KC_TRNS` in the destination layer so that tapping it again actually toggles back to the original layer. Only works upwards in the layer stack.

`TO(layer)` - Goes to a layer. This code is special, because it lets you go either up or down the stack -- just goes directly to the layer you want. So while other codes only let you go _up_ the stack (from layer 0 to layer 3, for example), `TO(2)` is going to get you to layer 2, no matter where you activate it from -- even if you're currently on layer 5. This gets activated on keydown (as soon as the key is pressed).

`TT(layer)` - Layer Tap-Toggle. If you hold the key down, the layer becomes active, and then deactivates when you let go. And if you tap it, the layer simply becomes active (toggles on). It needs 5 taps by default, but you can set it by defining `TAPPING_TOGGLE`, for example, `#define TAPPING_TOGGLE 1` for just one tap.


### Fun with modifier keys

* `LSFT(kc)` - applies left Shift to *kc* (keycode) - `S(kc)` is an alias
* `RSFT(kc)` - applies right Shift to *kc*
* `LCTL(kc)` - applies left Control to *kc*
* `RCTL(kc)` - applies right Control to *kc*
* `LALT(kc)` - applies left Alt to *kc*
* `RALT(kc)` - applies right Alt to *kc*
* `LGUI(kc)` - applies left GUI (command/win) to *kc*
* `RGUI(kc)` - applies right GUI (command/win) to *kc*
* `HYPR(kc)` - applies Hyper (all modifiers) to *kc*
* `MEH(kc)`  - applies Meh (all modifiers except Win/Cmd) to *kc*
* `LCAG(kc)` - applies CtrlAltGui to *kc*

You can also chain these, like this:

    LALT(LCTL(KC_DEL)) -- this makes a key that sends Alt, Control, and Delete in a single keypress.

The following shortcuts automatically add `LSFT()` to keycodes to get commonly used symbols. Their long names are also available and documented in `quantum/quantum_keycodes.h`.

    KC_TILD  ~
    KC_EXLM  !
    KC_QUES  ?
    KC_AT    @
    KC_HASH  #
    KC_DLR   $
    KC_PERC  %
    KC_CIRC  ^
    KC_AMPR  &
    KC_ASTR  *
    KC_LPRN  (
    KC_RPRN  )
    KC_UNDS  _
    KC_PLUS  +
    KC_DQUO  "
    KC_LCBR  {
    KC_RCBR  }
    KC_LABK  <
    KC_RABK  >
    KC_PIPE  |
    KC_COLN  :

`OSM(mod)` - this is a "one shot" modifier. So let's say you have your left Shift key defined as `OSM(MOD_LSFT)`. Tap it, let go, and Shift is "on" -- but only for the next character you'll type. So to write "The", you don't need to hold down Shift -- you tap it, tap t, and move on with life. And if you hold down the left Shift key, it just works as a left Shift key, as you would expect (so you could type THE). There's also a magical, secret way to "lock" a modifier by tapping it multiple times. If you want to learn more about that, open an issue. :)

`MT(mod, kc)` - is *mod* (modifier key - MOD_LCTL, MOD_LSFT) when held, and *kc* when tapped. In other words, you can have a key that sends Esc (or the letter O or whatever) when you tap it, but works as a Control key or a Shift key when you hold it down.

These are the values you can use for the `mod` in `MT()` and `OSM()`:

  * MOD_LCTL
  * MOD_LSFT
  * MOD_LALT
  * MOD_LGUI
  * MOD_RCTL
  * MOD_RSFT
  * MOD_RALT
  * MOD_RGUI
  * MOD_HYPR
  * MOD_MEH

These can also be combined like `MOD_LCTL | MOD_LSFT` e.g. `MT(MOD_LCTL | MOD_LSFT, KC_ESC)` which would activate Control and Shift when held, and send Escape when tapped. Note however, that you cannot mix right and left side modifiers.

We've added shortcuts to make common modifier/tap (mod-tap) mappings more compact:

  * `CTL_T(kc)` - is LCTL when held and *kc* when tapped
  * `SFT_T(kc)` - is LSFT when held and *kc* when tapped
  * `ALT_T(kc)` - is LALT when held and *kc* when tapped
  * `ALGR_T(kc)` - is AltGr when held and *kc* when tapped
  * `GUI_T(kc)` - is LGUI when held and *kc* when tapped
  * `ALL_T(kc)` - is Hyper (all mods) when held and *kc* when tapped. To read more about what you can do with a Hyper key, see [this blog post by Brett Terpstra](http://brettterpstra.com/2012/12/08/a-useful-caps-lock-key/)
  * `LCAG_T(kc)` - is CtrlAltGui when held and *kc* when tapped
  * `MEH_T(kc)` - is like Hyper, but not as cool -- does not include the Cmd/Win key, so just sends Alt+Ctrl+Shift.

##### Permissive Hold

As of [PR#1359](https://github.com/qmk/qmk_firmware/pull/1359/), there is a new `config.h` option:

```
#define PERMISSIVE_HOLD
```

This makes it easier for fast typists to use dual-function keys. As described in the PR:

Without this, if you let go of a held key inside the tapping term, it won't register.

Example: (Tapping Term = 200)

- SHFT_T(KC_A) Down
- KC_X Down
- KC_X Up
- SHFT_T(KC_A) Up

With permissive hold, if above is typed within tapping term, this will emit `X` (so, Shift+X).

With defaults, if above is typed within tapping term, this will emit `ax`, which I doubt is what anyone really wants
