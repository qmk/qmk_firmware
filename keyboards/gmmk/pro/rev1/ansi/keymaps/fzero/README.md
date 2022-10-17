# fzero's GMMK Pro layout

> Credit where credit is due - this keymap borrows heavily from [andrebrait](../andrebrait)

Do you primarily use a Mac but also have a PC? Then this keymap might be for you!

![My GMMK Pro, as configured in this keymap](https://i.snap.as/jRuikQ5S.jpeg)

Base layer has modifiers in the usual mac order:

- `L-CTRL` / `L-ALT` / `L-CMD` on the left
- `R-CMD` / `R-ALT` / `FN` on the right

The Windows layer has been configured for people who mainly use a mac:

- `L-CTRL` / `R-ALT` / `R-CTRL` on the left!
  - No more remapping your brain from `CMD` to `CTRL`! Let the keyboard do the work
  - If you're used to `Option`/`ALT`-accents on the mac check out [@adunning](https://github.com/adunning)'s [Mac Keyboard Layouts for Windows](/adunning/Mac-Keyboard-Layouts-for-Windows)
- `L-WIN` / `L-ALT` / `FN` on the right
  - There's your Win key!
  - Remember that Windows cares about which `ALT` you're pressing (rejoice Excel wizards)
    - You can remap these keys in **Via** though - Windows is layer 2

But the main feature is definitely **the knob**!

Instead of unnecessarily duplicating volume up/down functionality, this version **unnecessarily duplicates the mouse wheel!** I know right?

Oh, **and pressing the knob changes layers**. The keyboard will flash white for macOS layer and blue for Windows.

What else?

- **Via-enabled!** You won't be able to tweak Knob or RGB settings (for now?), but everything else works fine
- Layer 0 (macOS):
  - `PrintScreen` &rarr; `CMD + SHIFT + 4` (macOS region PrintScreen)
- Layer 1 (accessed by pressing Fn):
  - `Fn + Backspace` &rarr; `Del`
  - `Fn + PrintScreen` &rarr; `CMD + SHIFT + 5` (macOS screen recorder)
- Layer 2 (Windows):
  - See above
- Layer 3 (accessed by pressing Fn):
  - Modifier keys are back in their regular places

The following features have been carried over from [andrebrait](../andrebrait)'s keymap:

- RGB turns off after 20 minutes of inactivity
- RGB turns off when USB is suspended

This keymap also includes CAPS LOCK ON indicator. All left and right side LEDs, and the Caps key LED will turn solid red while CAPS LOCK is ON.
