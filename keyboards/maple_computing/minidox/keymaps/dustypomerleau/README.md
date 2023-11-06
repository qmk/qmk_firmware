## dustypomerleau, Minidox layout

The rationale behind my layout can be summarized as follows:

- Symmetry is important because use-cases are hard to predict. Whenever possible, modifiers and layer keys should be available from either hand.
- Inward rolls should be leveraged not just for alphas (Colemak DHm), but also for coding/symbols.
- Number order—like alpha order—should be designed to favor use of the strongest fingers.
- One-shot keys can greatly reduce the strain of typing, and should be leveraged.

Some aspects of my layout are optimized for macOS (order of modifiers, manner of producing en and em dashes, coding of micro-volume adjustments, etc.), but can be easily tweaked for the OS of your choice.

Shift can be a tricky modifier when used in `MT()` combinations, particularly for fast typists on split boards using serial. This can be partially mitigated with options in `config.h`, but still requires a relatively strict typing style/accuracy from the fast typist. The tendency is for faster typists to combat mod/tap mistakes by using very short intervals for `TAPPING_TERM`, but this can introduce its own set of complications. Shift is also one of the highest-yield opportunities to use `OSM()`. For these reasons, I pulled Shift onto dedicated keys in the thumbs for use during regular typing (the home row Shifts have been left in place for use during selection and keycuts). 

The tapdance code that I used to create mod/tap keys inside my symbol layer allows up to 2 consecutive symbols within `TAPPING_TERM`. If you think you will need to quickly nest more than that, feel free to add more `case`s.

### Special thanks

- Everyone on the QMK Discord, for helping me work out the code for mod/tap keys using shifted symbols.
- Everyone on the Colemak Discord, for their initial feedback on the layout.
- @stevep and @DreymaR, for their work on Colemak DH(m), a truly awesome typing experience (and of course Shai Coleman, for starting it all off!).
- @ckofy, for offering a dramatic improvement on Dvorak's original number order.
- u/That-Canadian, for designing this awesome keyboard.

### Questions or comments?

- GitHub @dustypomerleau
- Twitter @duspom
- Discord @dusty#8897
