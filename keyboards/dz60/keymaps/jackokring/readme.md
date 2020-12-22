# DZ60

My first keyboard edit. A multi-layer ANSI-60 with layers and function shift on each layer.
Changes from the default keymap include moving RESET, and a prefered arangement for the cusor
block of keys. The function key was exchanged with the right control key to get it.

## Right Windows is Application Context Menu Instead
The right Windows key is for getting the application context menu. The right Windows GUI
key is not often used. It is available on the macroboard shift layer for completeness.

## Common to All Fn Layers
* If on a layer a switch is not necessary so the following keys become themselves.
* Left control is ANSI layer select.
* Left win is macroboard layer select.
* Left alt is navigation layer select.
* Space is numpad layer select.

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
* Apostrophy is print screen.
* RGB controls are Q-I.
* Backlight controls are C-N.
* Escape is backtick.
* Various unicode characters µ(M), °(K), £(L), Ω(Z), ∫(S), ∂(D) and √(G).
* System power down on P key.
* Global mute is X.
* Browser home key is O, search is A, favorites is F.
* Volume is up(J) and down(H).

## Macroboard Layer
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
* A macro can be recorded (128 keys) until power off by backspace (record start/stop).
* The macro can be played back by space.
* Right alt/control are alt tab window switch (reverse and forward).
* Right win key is the right win key and not the app context menu key as in other layers.

### Macroboard Shift Layer (Fn Macroboard)
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
* Caps lock is shifted tab and with tab can do form navigation.
* Escape is pure escape.
* All left modifiers are normal with no one shot sticky.
* Enter and backspace are themselves.
* Backslash is keyboard reset.
* Equals is numpad equals (for extra macro codes when possible).
* Comma is numpad comma.
* The brackets are scroll wheel up and down such the [ is up.
* Quote is the scroll button.
* Semicolon is auxilliary mouse button 4 (standard mice don't have this).
* All the alpha keys are themselves.
* Minus turns on key lock for the next key (for easier drag 'n' drop for example).

### Special Shift Layer
* Fn exits the special shift layer.
* Minus/equal is korean modifiers.
* P is key lock for holding down a key until the held key is pressed again.
* International modifiers are on Q-O.
* Numbers are the numpad numbers for macro code options.
* Remaining laguage 3 to 7 are on Z-M.
* All left and right modifiers are themselves.
* Comma/period/slash set moise acceleration 1, 2 and 3.
* Backspace is delete.
* Backslash is insert. 
* Square brackets are home and end.
* Enter is itself.
* Various unicode characters µ(M), °(K), £(L), Ω(Z), ∫(S), ∂(D) and √(G).
* Volume is up(J) and down(H).
* Browser search is A, favorites is F.

## Navigation Layer
* Right alt/win/control/slash form cusor block.

### Navigation Shift Layer (Fn Navigation)
* Scroll lock placed on caps lock.
* Backslash is insert.
* Backspace is delete.
* F1 to F12 form top row numbers and minus/equals.
* F13 to F24 form second row Q-].
* Comma and period are page up/down.
* Semicolon is pause.
* Apostrophy is print screen.
* Escape is backtick.
* Enter is pure escape for easy shift escape typing.
* Right control/alt function as modifiers for F1-F24 usage.
* Various unicode characters µ(M), °(K), £(L), Ω(Z), ∫(S), ∂(D) and √(G).
* Media control prev(C), play(V), next(B), launch(N).
* Global mute is X.
* Browser search is A, favorites is F.
* Volume is up(J) and down(H).

## Numpad Layer
* Apostrophy is launch calculator.
* Semicolon is insert. (A strange choice but assume it can insert an escaped calc instance.)
* Numbers on MJKLUIO789.
* All modifiers are one shot sticky.
* Function shift is a toggle to the shifted layer.
* Right alt/win/control/slash form cusor block.
* Square brackets produce parantheses.
* Keys enter, - and = produce numpad variants enter, - and +.
* P key is numpad *.
* Backslash is numpad /.
* 0 Key is delete.
* F1 to F6 form top row 1-6.
* F7 to F12 form second row Q-Y.
* F13 to F18 form third row A-H.
* F19 to F24 form fourth row Z-N.
* Comma is a numpad comma.
* Num lock placed on caps lock.

### Numpad Shift Layer (Fn Numpad)
* Standard ANSI layer except for left modifiers control/win/alt.
* Fn is still sticky and needs pressing to exit the layer shift.