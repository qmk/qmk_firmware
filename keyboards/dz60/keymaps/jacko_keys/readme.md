# DZ60

My second keyboard edit. A multi-layer ANSI-60 with layers and function shift on each layer.
Changes from the default key-map include moving RESET, and a preferred arrangement for the cursor
block of keys. The function key was exchanged with the right control key to get it. This makes the layout of the right modifiers left to right be alt/win/control/Fn.

## Right Windows is Application Context Menu Instead
The right Windows key is for getting the application context menu. The right Windows GUI
key is not often used. It is available on the macro-board shift layer for completeness.

## Common to All Fn Layers
* If on an Fn layer a switch is not necessary so the following keys become themselves.
* Left control is ANSI layer select. Basic conformist ANSI.
* Left win is macro-board layer select.
* Left alt is navigation layer select. You MUST be in this mode for **BQN**.

## ANSI Layer
* Right control exchanged with function shift key as always.

### ANSI Shift Layer (Fn ANSI)
* Scroll lock placed on caps lock.
* Right alt/win/control/slash form cusor block.
* Backslash is insert.
* Backspace is delete.
* F1 to F12 form top row numbers and minus/equals.
* Square brackets are home and end.
* Comma and period are page up/down.
* Semicolon is pause.
* Apostrophe is print screen.
* RGB controls are Q-I.
* Backlight controls are C-N.
* Backtick is escape.
* Various Unicode characters µ/ℎ(M), °/⦵(K), £/€(L), ω/Ω(Z), ∫/Σ(S), ∂/∇(D) and √/∛(G).
* System power down on P key.
* Global mute is X.
* Browser home key is O, search is A, favourites is F.
* Volume is up(J) and down(H).

## Macro-board Layer
* Escape is a one shot sticky alt shift.
* Tab is a one shot sticky control alt.
* Caps lock is a one shot sticky control shift.
* All modifiers are one shot sticky.
* Function shift is a toggle to the shifted layer.
* F1 to F12 form top row numbers and minus/equals.
* F13 to F24 form second row Q-].
* F1 to F12 form third row A-enter with an implicit right alt gr applied.
* F13 to F23 form fourth row Z-right shift with an implicit right alt gr applied.
* Backslash is F24 with an implicit right alt gr applied.
* Depending on your system the "Level 3 Shift" may be removed by localization of alt gr.
* Right alt/control are alt tab window switch (reverse and forward).
* Right win key is the right win key and not the app context menu key as in other layers.

### Macro-board Shift Layer (Fn Macro-board)
* The right win key is one shot sticky.
* Escape is a one shot sticky win alt shift.
* Tab is a one shot sticky win control alt.
* Caps lock is a one shot sticky win control shift.
* Left shift is a one shot sticky win shift.
* Backspace is a one shot sticky control alt shift.
* Fn is still sticky and needs pressing to exit the layer shift.
* Right control enters the extended shift layer.
* Right alt enters the special shift layer.

### Extended Shift Layer
* Fn exits the extended shift layer.
* Right alt/win/control/slash form mouse movement block.
* Period is left mouse button.
* Right shift is right mouse button.
* All left modifiers are normal with no one shot sticky.
* Enter and backspace are themselves.
* Backslash is keyboard reset.
* Equals is numpad equals (for extra macro codes when possible).
* Comma is numpad comma.
* The brackets are scroll wheel up and down such the [ is up.
* Quote is the scroll button.
* Semicolon is auxiliary mouse button 4 (standard mice don't have this).
* All the alpha keys are themselves.
* Minus turns on key lock for the next key (for easier drag 'n' drop for example).

### Special Shift Layer
* Fn exits the special shift layer.
* P and equals is Korean modifiers.
* Minus is key lock for holding down a key until the held key is pressed again.
* International modifiers are on Q-O.
* Numbers are the numpad numbers for macro code options.
* Remaining language 3 to 7 are on Z-M.
* All left and right modifiers are themselves.
* Comma/period/slash set mouse acceleration 1, 2 and 3.
* Backspace is delete.
* Backslash is insert.
* Square brackets are home and end.
* Enter is itself.
* Various Unicode characters µ/ℎ(M), °/⦵(K), £/€(L), ω/Ω(Z), ∫/Σ(S), ∂/∇(D) and √/∛(G).
* Volume is up(J) and down(H).
* Browser search is A, favourites is F.
* Escape is pure escape.
* Caps lock is num lock.

#### Notes on "Level 3 Shift"
* Ironically not being American I will not test the en_US local without hardware.
* I'm not sure if that locale supports an alt gr key interpretation of right alt.
* Hacking Linux termcap/gui equivalent files might be possible for the determined.

## Navigation Layer
* Right alt/win/control/slash form cursor block.
* Backslash enters a prefix to enter **BQN** characters.

### Navigation Shift Layer (Fn Navigation)
* Scroll lock placed on caps lock.
* Backslash is insert.
* Backspace is delete.
* F1 to F12 form top row numbers and minus/equals.
* F13 to F24 form second row Q-].
* Comma and period are page up/down.
* Semicolon is pause.
* Apostrophe is print screen.
* Backtick is escape.
* Enter is pure escape for easy shift escape typing.
* Right control/alt function as modifiers for F1-F24 usage.
* Various Unicode characters µ/ℎ(M), °/⦵(K), £/€(L), ω/Ω(Z), ∫/Σ(S), ∂/∇(D) and √/∛(G).
* Media control prev(C), play(V), next(B), launch(N).
* Global mute is X.
* Browser search is A, favourites is F.
* Volume is up(J) and down(H).

## BQN Layer
* BQN unshifted and shifted.
* Fn shift holds the BQN layer.
* Left control/win/alt prefix meta of **\\** to select further layers.
* Left and right cursor work on right alt/control.
* Right GUI button is right win key.

### Control Shift Layer (BQN Left Control)
* Various control code literals and icongraphs plus cursor.
* Comma and period are page up/down.
* Semicolon is pause.
* Apostrophe is print screen.
* The `control_codes.md` contains more information about control codes.

### Unicode Shift Layer (BQN Left Alt)
* Unicode selection on alphas.
* Numbers unchanged.
* Square brackets are home and end.
* Comma and period are page up/down.
* Semicolon is pause.
* Apostrophe is print screen.

### Nothing Yet Layer (BQN Left Win)
* No space to define new codes to emit, but can emit any code already defined on any key.
* Needs programming.
