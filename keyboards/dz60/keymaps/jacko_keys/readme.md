# DZ60 Mk II

My second keyboard edit. A multi-layer ANSI-60 with layers and function shift on each layer.
Changes from the default key-map include moving RESET, and a preferred arrangement for the cursor
block of keys. The function key was exchanged with the right control key to get it. This makes the layout of the right modifiers left to right be `Alt`/`Win`/`Ctrl`/`Fn`.

## Right `Win` is Application Context Menu Instead
The right `Win` key is for getting the application context menu.

### Notes on "Level 3 Shift"
* Ironically not being American I will not test the en_US local without hardware.
* I'm not sure if that locale supports an `Alt Gr` key interpretation of right `Alt`.
* Hacking Linux `termcap` or `GUI` equivalent files might be possible for the determined.

## Common to All `Fn` Layers
* Left control is ANSI layer select. Basic conformist ANSI.
* Left `Win` is macro-board layer select. Latching macro modifiers and function keys.
* Left `Alt` is navigation layer select. You MUST be in this mode for **BQN**.

## ANSI Layer (Complete RED Layer)
* Right control exchanged with function shift key as always.
* This layer is the keyboard default and has few surprises. To access this layer the key combination `Fn`+Left `Ctrl` has been reserved. In macro mode the `Fn` key is sticky and so it may cause a little confusion.

### ANSI Shift Layer (`Fn` ANSI MAGENTA Shift)
* Scroll lock placed on caps lock.
* Right `Alt`/`Win`/`Ctrl`/slash form cursor block.
* Backslash is insert.
* Backspace is delete.
* F1 to F12 form top row numbers and minus/equals.
* Square brackets are home and end.
* Comma and period are page up/down.
* Semicolon is pause.
* Apostrophe is print screen.
* RGB controls are Q-I.
* Backlight controls are C-N.Fn
* Backtick is escape.
* Various Unicode characters µ/ℎ(M), °/⦵(K), £/€(L), ω/Ω(Z), ∫/Σ(S), ∂/∇(D) and √/∛(G).
* System power down on P key.
* Global mute is X.
* Browser home key is O, search is A, favourites is F.
* Volume is up(J) and down(H).

### Control Shift Layer (Left Control on `Fn` Layer CYAN Shift)
* Various control code literals and icongraphs plus cursor.
* Comma and period are page up/down.
* Semicolon is pause.
* Apostrophe is print screen.
* The `control_codes.md` contains more information about control codes.

## Navigation Layer (Complete GREEN Layer)
* Right `Alt`/`Win`/`Ctrl`/slash form cursor block.
* Backslash enters a prefix to enter **BQN** characters. (The **BQN** Layer).

### Navigation Shift Layer (`Fn` Navigation MAGENTA Shift)
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
* Right `Ctrl`/`Alt` function as modifiers for F1-F24 usage.
* Various Unicode characters µ/ℎ(M), °/⦵(K), £/€(L), ω/Ω(Z), ∫/Σ(S), ∂/∇(D) and √/∛(G).
* Media control prev(C), play(V), next(B), launch(N).
* Global mute is X.
* Browser search is A, favourites is F.
* Volume is up(J) and down(H).

### Mouse Shift Layer (Left `Alt` on `Fn` Layer CYAN Shift)
* Right `Alt`/`Win`/`Ctrl`/slash form mouse movement block.
* Comma is left mouse button.
* Period is right mouse button.
* Enter and backspace are themselves.
* Backslash is keyboard reset.
* Equals is number pad equals.
* Comma is number pad comma.
* The brackets are scroll wheel up and down such the [ is up.
* Semicolon is mouse button 3 (scroll button).
* Apostrophe is mouse button 4 (standard mice don't have this).
* All the alpha keys form 26 Unicode characters (definable in code).
* Numbers unchanged.
* Minus turns on key lock for the next key (for easier drag 'n' drop for example).

### **BQN** Layer (Complete BLUE Layer Within BQN Specification)
* **BQN** unshifted and shifted.
* Left and right cursor work on right `Alt`/`Ctrl`.
* Right GUI button is right `Win` key.

```
┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬─────────┐
│~ ¬ │! ⎉ │@ ⚇ │# ⍟ │$ ◶ │% ⊘ │^ ⎊ │& ⍎ │* ⍕ │( ⟨ │) ⟩ │_ √ │+ ⋆ │Backspace│
│` ˜ │1 ˘ │2 ¨ │3 ⁼ │4 ⌜ │5 ´ │6 ˝ │7   │8 ∞ │9 ¯ │0 • │- ÷ │= × │         │
├────┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬──────┤
│Tab    │Q ↙ │W 𝕎 │E ⍷ │R 𝕣 │T ⍋ │Y   │U   │I ⊑ │O ⊒ │P ⍳ │{ ⊣ │} ⊢ │|     │
│       │q ⌽ │w 𝕨 │e ∊ │r ↑ │t ∧ │y   │u ⊔ │i ⊏ │o ⊐ │p π │[ ← │] → │\     │
├───────┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴──────┤
│Caps    │A ↖ │S 𝕊 │D   │F 𝔽 │G 𝔾 │H « │J   │K ⌾ │L » │: · │" ˙ │Enter     │
│lock    │a ⍉ │s 𝕤 │d ↕ │f 𝕗 │g 𝕘 │h ⊸ │j ∘ │k ○ │l ⟜ │; ⋄ │' ↩ │          │
├────────┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──────────┤
│Shift      │Z ⋈ │X 𝕏 │C   │V ⍒ │B ⌈ │N   │M ≢ │< ≤ │> ≥ │? ⇐ │Shift       │
│           │z ⥊ │x 𝕩 │c ↓ │v ∨ │b ⌊ │n   │m ≡ │, ∾ │. ≍ │/ ≠ │            │
└───────────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────────────┘
                             Space: ‿
```

### Unicode Shift Layer (`Fn` After \ **BQN** Prefix MAGENTA Shift)
* All the alpha keys form 26 Unicode characters (definable in code).
* Numbers unchanged.
* Square brackets are home and end.
* Comma and period are page up/down.
* Semicolon is pause.
* Apostrophe is print screen.

## Macro-board Layer (YELLOW Layer)
* Escape is a one shot sticky `Alt` shift.
* Tab is a one shot sticky control `Alt`.
* Caps lock is a one shot sticky control shift.
* All modifiers are one shot sticky.
* `Fn` is not a sticky modifier.
* F1 to F12 form top row numbers and minus/equals.
* F13 to F24 form second row Q-].
* F1 to F12 form third row A-enter with an implicit right `Alt Gr` applied.
* F13 to F23 form fourth row Z-right shift with an implicit right `Alt Gr` applied.
* Backslash is F24 with an implicit right `Alt Gr` applied.
* Depending on your system the "Level 3 Shift" may be removed by localization of `Alt Gr`.
* Right `Alt`/`Ctrl` are `Alt`+`Tab` window switch (reverse and forward).
* Right `Win` key is the right `Win` key and not the app context menu key as in other layers.
* Backspace is Left `Win` and Right `Win` combination sticky.

### Macro-board Shift Layer (`Fn` Macro-board MAGENTA Shift)
* The right `Win` key is one shot sticky.
* Escape is a one shot sticky `Win`+`Alt` shift.
* Tab is a one shot sticky `Win`+`Ctrl`+`Alt`.
* Caps lock is a one shot sticky `Win` control shift.
* Left shift is a one shot sticky `Win` shift.
* Backspace is a one shot sticky control `Alt` shift.
* `Fn` is still sticky and needs pressing to exit the layer shift.

### Special Shift Layer (Left `Win` on `Fn` Layer CYAN Shift)
* `Fn` exits the special shift layer.
* P and equals is Korean modifiers.
* Minus is key lock for holding down a key until the held key is pressed again.
* International modifiers are on Q-O.
* Numbers are the number pad numbers for macro code options.
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
* Caps lock is number lock.
