![mitosis:datagrok layout image](https://i.imgur.com/eum3fsc.png)

[Keyboard layout editor source](http://www.keyboard-layout-editor.com/#/gists/9cf33be8a8e773647cfa44a0dbc44b31)

# a layout for the Mitosis

- Emphasis on momentary modifiers, all usable from either hand, arranged
  symmetrically, but distinguishable left/right by the OS. Shift, Red
  ("Lower"), Blue ("Raise"), Super ("Windows"), Meta ("Alt"), Hyper.

- Red and Blue are used to momentary-enable (like a shift key) one of three layers:

    - Red: Symbols layer
    - Blue: Numbers layer
    - "Purple" (both Red and Blue): Functions layer

- The base layer is QWERTY. A slight variant of [Workman][] may be toggled-on.

- Emphasis on minimizing hand travel, so as not to lose orientation with
  homerow.

- Paired programming symbols (braces, brackets, parentheses) are arranged
  symmetrically in the symbols layer.

- `?` and `!` are moved to take the place of `<` and `>`. Rationale: unmodded
  and shifted keys should be for prose, while symbols useful for programming
  should be colocated on their own layer.

- No OS keymap modification required.

## Design notes

- **I use an 8Mhz Pro Micro.** If you want to use this keymap with the standard
  16Mhz Pro Micro specified in the Mitosis design:

    - Remove the lines in `rules.mk` mentioning `F_CPU` and `F_USB`.
    - Remove the lines in `config.h` mentioning `SERIAL_UART_BAUD`.

- Workman layout

    - I'm learning a new physical key placement, so I might as well go all out
      and use an optimal non-QWERTY layout.

    - I like the way Workman feels and some of its advantages over Colemak.
      Unfortunately, it was designed using a weighting system based on a
      standard column-staggered keyboard so is probably not as optimal as one
      could achieve on an ergonomic board like the Mitosis. Maybe run an
      optimizer routine after I determine good values for key difficulty on the
      Mitosis.

- Arrows in the home position (on a layer). Mod+Arrows = PgUp/PgDn/Home/End,
  which is intuitive for me

- I use tab all the time for autocompletion. To allow it to live on the base
  layer it is now Mod-Tapped with left shift.

### Abandoned ideas

- ~~"Since QWERTY and Workman keep angle brackets together, place other
  enclosing symbols on the same keys. This informs the numbers placement,
  which informs the function-key placement."~~

    - I tried this and it was bad. I don't like having to pick the right
      modifier to get the right flavor of bracket. Instead, now, one modifier
      activates a symbols layer where all brackets are easily accessible.

- Space/Enter to the left of layer select for Enter doesn't work well; I always
  trigger space first when mashing the keys simultaneously. This might not
  continue to be true if I change the angle at which I strike the keys e.g.
  with a neoprene base or a wrist support.

- I used to have Blue on ring finger, but that was too hard to use in
  conjunction with shift.

## To do

- Figure out where to place non-numpad numbers so we don't need num lock turned
  on to type them?
- Improve LED indications (may require modding bluetooth firmware):
    - Is any board nonresponsive (which one?)
    - Does either board have a low battery?
- Add Insert, PrintScr, Pause/Break
- ~~Make QWERTY base layer for people who customize layout in software?~~ I
  default to QWERTY now.
- Store default base layer in eeprom?
- See if the henkan/muhenkan placement is at all useful for Japanese speakers,
  or abuse different keysyms for Left/Right Hyper. (Original space cadet used
  scancodes 145/175. 145 is LANG2, 175 is "reserved" in USB HID spec.)
- Mod a buzzer onto my receiver and enable tones
- Implement "layer lock" key
- Improve tri-layer behavior

[Workman]: https://viralintrospection.wordpress.com/2010/09/06/a-different-philosophy-in-designing-keyboard-layouts/
