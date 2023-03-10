
# apazzy's GMMK Pro layout
==========================

Layout/fn layer based on the [POK3R](https://hackorama.github.io/pok3r.html) (POKER v3), a 60% keyboard my brain remembers and I use on another computer.

Defines custom keycodes for mouse jiggler based on [DIYCharles' implementation](https://github.com/DIYCharles/MouseJiggler) and a GUI/Windows key toggle. Also borrowed inspiration fgrom jonavin and byungyoonc's keymaps.

FN+Encoder Press - Enable Mouse Jiggler
Encoder press or Esc - Stop Mouse Jiggler if running
FN+WIN - Windows key lock toggle

- `KC_WINLCK`   GUI/*WIN*dows key *L*o*CK*
- `KC_MJST`     *M*ouse *J*iggler *ST*art
- `KC_MJCX`     *M*ouse *J*iggler *CX*ancel

Not mapped yet but I want to map these at some point.
- `KC_TASK`     *TASK* Manager (`LCTL(LSFT(KC_ESC)))`)
- `EMO_SHRUG`   shrug guy: ¯\\_(ツ)_/¯ (not tested)

Code is messy - sorry. I tried to put as much of this in userspace as possible but couldn't get it working, so I shoved it all in my keymap.
