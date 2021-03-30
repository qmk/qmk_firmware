# Bucktooth v2.0 (Mac)

Bucktooth is an alternate layout that pushes the letters to the edges and puts most punctuation in the center. It's derived in part from my experience with Ergodox boards. I call the main layer layout QWERTSplitlY, you may notice the right side punctuation moving to the center and the control keys missing from the left.

## Split QWERTY: Unorthodox

     QwertSplitly
     ,-----------------------------------------------------------------------------------.
     |   1  |   2  |   3  |   4  |   5  |   +  |   `  |   6  |   7  |   8  |   9  |   0  |
     |------+------+------+------+------+------+------+------+------+------+------+------|
     |   Q  |   W  |   E  |   R  |   T  |   [  |   ]  |   Y  |   U  |   I  |   O  |   P  |
     |------+------+------+------+------+-------------+------+------+------+------+------|
     |   A  |   S  |   D  |   F  |   G  |   -  |   '  |   H  |   J  |   K  |   L  |   ;  |
     |------+------+------+------+------+------|------+------+------+------+------+------|
     |LShift|   Z  |   X  |   C  |   V  |   \  |   /  |   B  |   N  |   M  |   ,  |./RSft|
     |------+------+------+------+------+------+------+------+------+------+------+------|
     |ESC/fn|LCtrl | LOpt | LCmd |Space | Tab  | BkSp |Space |En/Cmd|<-/fn |CRSR v|CRSR->|
     `-----------------------------------------------------------------------------------'


It is a bit of a departure from normal Preonic layouts. You will notice that the bottom letter row is shifted right, and this is both an accomodation for the left shift and because I could never get used to C being directly under D and some other similar staggered keyboard tendencies. If you are used to the default ortho layouts you may want to adjust this back; but, you may find that it is slightly easier to move between a typical staggered layout and ortho boards in this layout. Plus, having a dedicated shift is a good thing, even though the dot key does double duty as a right shift.

That left shift is the only control or modifier key on the top four rows. All the modifiers and control keys are in the bottom row. Most Ergodox boards put the braces ({}[]) in the center and keep the hands apart. The hands aren't very far apart in this layout but you can imagine moving between this layout and the Ergodox easily, if you can get used to the lack of the extra 1.5U columns on the left and right!

With all control keys on the bottom row, the ESC key now lives in the bottom left and on my keyboard I actually put a very heavy keyswitch in that space to keep me from hitting it accidentally instead of ctrl. Hold it down and it becomes fn. I usually hit it with my whole hand since it is in the corner, without moving my fingers down to it.

## Revision 2 Changes

The move of B to the right side of the keyboard may be controversial but has felt more and more comfortable to me. Again if you split a staggered layout keyboard down a straight line B has more in common with Y than T. I don't understand breaking the board into left and right on anything but a vertical line despite the long history of bringing the staggered layout slewing left.

Revision 2 also changes the positions of -, =, and ~ for better compatibility with sculpted profile keysets which offer a Dvorak set option that provides the middle row dash because a middle row backtick/tilde is not found anywhere.

## Function Layer

There are no raise and lower or multiple function pages. The Preonic has enough keys to avoid more than a single function page, and I prefer to have spacebars for both thumbs so the "Bucktooth" name comes from the typical keyset with darker function keys and lighter alphas and space keys giving the keyboard fang-like appearance where the two spaces are.


     Fn
     ,-----------------------------------------------------------------------------------.
     |  F1  |  F2  |  F3  |  F4  |  F5  | Vol+ | Mute |  F6  |  F7  |  F8  |  F9  |  F10 |
     |------+------+------+------+------+------+------+------+------+------+------+------|
     |  F11 |  F12 |  F13 |  F14 |  F15 |Track-|Track+|M:WhUp|M:Lclk| M:Up |M:Rclk| PgUp |
     |------+------+------+------+------+-------------+------+------+------+------+------|
     | Caps |^LPad |^DashB|^Help |^Drawr| Vol- | |>|| |M:WhDn|M:Left|M:Down|M:Rght| PgDn |
     |------+------+------+------+------+------|------+------+------+------+------+------|
     |RShift|^Menu |^SMenu|^Dock |^Tools|^Notif|  Ins |M:Slow|M:Norm|M:Fast| Home | End  |
     |------+------+------+------+------+------+------+------+------+------+------+------|
     |[ESC] |RCtrl | ROpt | RCmd |Space |Sh-Tab|  Del |Space |PadEnt| [fn] |  Up  | Left |
     `-----------------------------------------------------------------------------------'

### Cursor Keys

The cursor keys are a design I stole from the old Commodore computers which had DOWN and RIGHT keys on the bottom right part of the board. When shifted, they would move the cursor in the opposite direction, and Commodore saved two keys. Since shifted arrows are a common use case in selecting text, emulating this exactly is not desirable so the fn key is placed next to the cursor down and right keys and holding down fn will reverse their meaning. Unlike the Commodore keys they will not invert just by releasing fn but it is close. Because QMK supports it I also allow use the tap mode for fn to move the cursor left, so only going up requires the fn. This is surely the weirdest part of the layout for most people. As someone who learned to type on a Commodore keyboard, it is second nature to me!

### Mac Keyboard navigation Combo Macros

On Fn layer ZXCVB and SDFG keys I have set up the default key bindings for Mac OS Keyboard Focus keys since they are obscure and require FKeys mostly. They are pretty convenient for using the keyboard to search the menus, go to the dock, etc. Some like the one to jump to a window's toolbar and the one to jump to a window's accessory drawer are less commonly used.

---

Contributed to QMK and released with the QMK license by Jeri C. Mason, 3/16/2018 - Revision 2 2/26/2019
