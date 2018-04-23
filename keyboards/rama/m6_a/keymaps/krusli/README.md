# krusli's RAMA M6-A Layout

Personal keymap for the RAMA M6-A.

Keymap was from my own port for the M6-A before official support was added, thus the backlighting code is not ported yet from the official default keymap.

Top-right button acts as a "toggle between layers" button. Layer 0 -> Layer 1 -> Layer 2 -> Layer 0 -> ...

- Layer 0: Git and Discord shortcuts
- Layer 1: Media playback and volume controls
- Layer 2: Osu! gamepad layer

## Helpful alternative keymaps (WIP)
### Arrow cluster
Use [karabiner-elements](https://github.com/tekezo/Karabiner-Elements) on macOS so that the state of the modifiers (shift, caps lock) are synchronised between keyboards (for shift + arrow key text selection, for example). It's also a handy tool for customising keyboard behaviour on a Mac.

On Windows/Linux modifier state should be shared between all keyboards by default.

Installation: install [homebrew](https://brew.sh) and run `brew install Caskroom/cask/karabiner-elements`.

```C
KEYMAP(
  KC_ESC,   KC_UP,   TO(_LAYER0),
  KC_LEFT,  KC_DOWN, KC_RIGHT
)
```
