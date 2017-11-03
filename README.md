# A Mitosis keymap

- Base layer is a variant of Workman.
- Six modifiers (Shift, Fn1, Fn2, Super, Meta, Hyper), accessible on both hands.
- Paired programming symbols (braces, brackets, parens) arranged symmetrically.
- In general, prose symbols use shift while programming symbols use a layer.
- No OS keymap modification required.

## Design notes

- I'm learning a new key placement, so might as well go all out and use an
  optimal non-QWERTY layout. Would be nice to toggle QWERTY so friends can
  poke a few letters if needed.

- Arrows in the home position (on a layer). Fn+Arrows = PgUp/PgDn/Home/End,
  which is intuitive for me

- ~~"Since QWERTY and WORKMAN keep angle brackets together, place other
  enclosing symbols on the same keys. This informs the numbers placement,
  which informs the function-key placement."~~

  - I tried this and it was bad. I don't like having to pick the right modifier
    to get the right flavor of bracket. Instead, now, one modifier activates a
    symbols layer where all brackets are easily accessible.

- I used to have Blue layer on ring finger, but that was too hard to use in
  conjunction with shift.

## To do

- Improve LED indications (may require modding bluetooth firmware):
    - Is any board nonresponsive (which one?)
    - Does either board have a low battery?
- Use "shifted keys" hack to make programming symbols easier to type
- Add "media" keysyms, Insert, PrintScr, Pause/Break
- Dynamically toggle QWERTY or other layouts
- See if the henkans placement is at all useful for Japanese speakers, or abuse
  different keysyms
- Overlay a 10key numpad somewhere
- Mod a speaker onto my receiver and enable tones
- Mod more indicator LEDs onto my receiver
- Do something with Num/Caps/Scroll lock?
- Improve tri-layer behavior
