Priyadi Keymap for Planck-like Keyboards
========================================

Main layer modifications from default Planck layout:

* Enter moved to quotes position
* Quotes moved to semicolon position.
* QWERTZ style colon & semicolon. shift-. = :  shift-, = ;  This is done in hardware, no layout switching needed in software.
* < & > occupied precious real estate, and so they are moved down to punctuation layer.
* Right-shift on Enter position.
* Removed arrow keys, they are on another layer now.
* Put Ctrl-Alt-Super and Super-AltGr-Ctrl in left & right corners.
* Lower & Raise is now called Num and Fun.
* OS & Left keys become another thumb modifier: Empty & Greek (Empty because I used this for another use and my muscle memory is not adapted to it yet)

On Promethium, Trackpoint is enabled on PD2 and PD3. We impersonate a Thinkpad keyboard to be able to use Thinkpad driver on Windows (still needs verification).

AltGr & Compose dual use key. Tap for Compose (mapped to Scroll Lock in hardware) and press for AltGr.

Supported layouts: QWERTY, DVORAK, Colemak, Workman, Norman. Switchable from SYS layer. In DVORAK, semicolon is replaced by /? key.

Num activates NUM layer: hexkeypad on the right side and most punctuation on the left side. Hexkeypad is optimized for C-style hex, IPv6, HTML RGB triplets, etc.

Fun activates FUN layer: arrow cluster on right home row, F-numbers on left side.

Pressing Num+Fun activates PUNC layer: same punctuations as NUM layer on the left side, parens on the right side.

Greek activates either GREEKU or GREEKL layer, depending whether shift is pressed or not. Shift state changes are also taken into account when the layer is active.

Greek+Empty activates EMOJI layer. The whole keyboard now outputs emojis!

Pressing both spacebars (spacekeys, actually) activates GUI layer. QWERTYUIOP switches to a virtual desktop. J & L switches virtual desktop to the left or right. S & F behaves like Alt-Tab and Alt-Shift-Tab. This works by sending Alt press when entering the layer, and Alt release when other than S or F keys are pressed.

Pressing both Ctrls activates SYS layer for configuring the keyboard.

On Promethium, USB or Bluetooth output is detected on startup. If USB is connected, then USB is used initially. SYS-U and SYS-B switch output to USB or Bluetooth at runtime. Current active output is indicated with LEDs.

SYS-W, SYS-L, SYS-M switch Unicode input method. SYS-Q, SYS-D, SYS-C, SYS-K, SYS-N switch to QWERTY, DVORAK, Colemak, Workman and Norman, respectively.

On Planck, SYS-A (mnemonic: audio) toggles faux clicky: use buzzer to emit clicks on key presses and releases.

On Promethium there are 6 indicator LEDs, and under switch LEDs on each switches, including Trackpoint buttons. Totaling 57 LEDs. Output is limited to 0xF for each LEDs to conserve power. SYS-G (mnemonic: glow) toggles various backlighting modes.

On Promethium, there's a LED to indicate battery level. Hue indicates level: green is full, red is empty.