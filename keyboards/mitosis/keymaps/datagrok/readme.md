![mitosis:datagrok layout image](https://i.imgur.com/Lt0t0nq.png)

[Keyboard layout editor source](http://www.keyboard-layout-editor.com/#/gists/e1a6a7a480fd4984c0bed38ee35f6c4f)

# a layout for the Mitosis

- Emphasis on momentary modifiers, all usable from either hand, arranged
  symmetrically, but distinguishable left/right by the OS. Shift, Fn1
  ("Lower"), Fn2 ("Raise"), Super ("Windows"), Meta ("Alt"), Hyper.

- Fn1 and Fn2 are used to momentary-enable (like a shift key) one of three layers:

    - Fn1 (Red): Symbols layer
    - Fn2 (Blue): Numbers layer
    - Both: Functions layer

- The base layer is a slight variant of [Workman][]. QWERTY may be toggled-on.

- Paired programming symbols (braces, brackets, parentheses) are arranged
  symmetrically in the symbols layer. `?` and `!` are moved to take the place
  of `<` and `>`.

- No OS keymap modification required.

## Design notes

- **I use an 8Mhz Pro Micro.** If you want to use this keymap with the standard
  16Mhz Pro Micro specified in the Mitosis design:

    - Remove the lines in `rules.mk` mentioning `F_CPU` and `F_USB`.
    - Remove the lines in `config.h` mentioning `SERIAL_UART_BAUD`.

- I'm learning a new key placement, so might as well go all out and use an
  optimal non-QWERTY layout.

- I like the way Workman feels and some of its advantages over Colemak.
  Unfortunately, it was designed using a weighting system based on a standard
  column-staggered keyboard so is probably not as optimal as one could achieve
  on an ergonomic board like the Mitosis.

- Arrows in the home position (on a layer). Mod+Arrows = PgUp/PgDn/Home/End,
  which is intuitive for me

### Abandoned ideas

- ~~"Since QWERTY and Workman keep angle brackets together, place other
  enclosing symbols on the same keys. This informs the numbers placement,
  which informs the function-key placement."~~

    - I tried this and it was bad. I don't like having to pick the right
      modifier to get the right flavor of bracket. Instead, now, one modifier
      activates a symbols layer where all brackets are easily accessible.

- Space/Enter to the left of layer select for Enter doesn't work well; I always
  trigger space first.

- I used to have Blue layer on ring finger, but that was too hard to use in
  conjunction with shift.

## To do

- Improve LED indications (may require modding bluetooth firmware):
    - Is any board nonresponsive (which one?)
    - Does either board have a low battery?
- Add Insert, PrintScr, Pause/Break
- Make QWERTY base layer for people who customize layout in software? Store
  default base layer in eeprom?
- See if the henkans placement is at all useful for Japanese speakers, or abuse
  different keysyms
- Mod a speaker onto my receiver and enable tones
- Implement "layer lock" key
- Improve tri-layer behavior

[Workman]: https://viralintrospection.wordpress.com/2010/09/06/a-different-philosophy-in-designing-keyboard-layouts/
