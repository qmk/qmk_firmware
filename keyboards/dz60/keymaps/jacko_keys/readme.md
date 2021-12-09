# DZ60 Mk II

My second keyboard edit. A multi-layer ANSI-60 with function shifts on each layer.
Changes from the default key-map include moving RESET (now on the mouse layer), and a preferred arrangement for the cursor block of keys. The function key was exchanged with the right control key to get it. This makes the layout of the right modifiers left to right be `Alt`/`Win`/`Ctrl`/`Fn`.

## General Notes
The right `Win` key is not the application context menu, which itself can often be found on `Fn`+`Enter`. Sometimes the `Win` key is part of the cursor block.
There is also a shared not (inverse) number lock or scroll lock LED pattern.
It is possible to do a `Ctrl`+`Alt`+`Del`, by `Fn`+`Tab` in most modes but not YELLOW mode.

### Notes on "Level 3 Shift"
* Ironically not being American I will not test the en_US local without hardware.
* I'm not sure if that locale supports an `Alt Gr` key interpretation of right `Alt`.
* Hacking Linux `termcap` or GUI equivalent files might be possible for the determined.
* The compse key on the input method may remove `Alt Gr` as a modofier. This can be edited in `config.h` and by the `#define ALG(x) ALGR(x)` macro in `keymap.c`.

### Common to All MAGENTA Shift `Fn` Layers (Exceptions Noted Below, Mainly in YELLOW Mode)
* Left `Ctrl` is ANSI layer select. Basic conformist ANSI.
* Left `Win` is macro-board layer selection. Latching macro modifiers and function keys.
* Left `Alt` is navigation layer select. You **MUST** be in this mode for **BQN**.
* Basically `Fn`+ a left modifier on the bottom row changes the main layer or enters a CYAN shift except when in **BQN** BLUE mode.
* In CYAN shift mode you may release the `Fn` key while keeping hold of the respective CYAN modifier.
* Scroll lock via caps lock.
* Backslash makes insert.
* Backspace makes delete.
* Backtick makes escape.
* **BQN** MAGENTA `Fn` is a locking mode for a different character Unicode layer.

## ANSI Layer (RED Layer)
* Right `Ctrl` is left of the `Fn` shift key as always.
* This layer is the keyboard default and has no surprises. To access this layer the key combination `Fn`+Left `Ctrl` has been reserved.

### ANSI Shift Layer (`Fn` Layer MAGENTA Shift)
* Right `Alt`/`Win`/`Ctrl`/slash form cursor block.
* F1 to F12 form top row numbers and minus/equals.
* Square brackets are home and end.
* Comma and period are page up/down.
* Semicolon is pause.
* Apostrophe is print screen.
* RGB controls are Q-I.
* Backlight controls are C-N.Fn
* Various Unicode characters µ/ℎ(M), °/⦵(K), £/€(L), ω/Ω(Z), ∫/Σ(S), ∂/∇(D) and √/∛(G).
* System power down on P key.
* Global mute is X.
* Browser home key is O, search is A, favourites is F.
* Volume is up(J) and down(H).

### Control Shift Layer (Left `Ctrl` on `Fn` Layer CYAN Shift)
* Various control code literals and icongraphs plus cursor.
* Comma and period are `Ctrl`+page up/down.
* Semicolon is `Ctrl`+pause.
* Apostrophe is `Ctrl`+print screen.
* The `control_codes.md` contains more information about control codes.
* Cursor block is `Ctrl` modified.
* As far as possible the modifiers have in implicit `Ctrl`.

## Navigation Layer (GREEN Layer)
* Right `Alt`/`Win`/`Ctrl`/slash form cursor block.
* Backslash enters a prefix to enter **BQN** characters. (The **BQN** Layer).

### Navigation Shift Layer (`Fn` Navigation MAGENTA Shift)
* F1 to F12 form top row numbers and minus/equals.
* F13 to F24 form second row Q-].
* Comma and period are page up/down.
* Semicolon is pause.
* Apostrophe is print screen.
* Right `Win` tap is slash, while hold is `Win`.
* Right `Ctrl`/`Alt` function as modifiers for F1-F24 usage.
* Various Unicode characters µ/ℎ(M), °/⦵(K), £/€(L), ω/Ω(Z), ∫/Σ(S), ∂/∇(D) and √/∛(G).
* Media control prev(C), play(V), next(B), launch(N).
* Global mute is X.
* Browser search is A, favourites is F.
* Volume is up(J) and down(H).

### Mouse Shift Layer (Left `Alt` on `Fn` Layer CYAN Shift)
* Right `Alt`/`Win`/`Ctrl`/slash form mouse movement block.
* Space is mouse button 1.
* Comma is scroll up.
* Period is scroll down.
* Enter, tab and escape (on backtick) are themselves.
* Backspace does a delete.
* Backtick is keyboard RESET, as this allows backtick to be held for entering the bootloader.
* Backslash is `SysReq`.
* Tab is itself.
* Caps lock cycles the Unicode input mechanism. Linux, WinCompose and Mac.
* The brackets are home and end.
* Minus and equals are buttons 4 and 5 (standard mice don't have this).
* Semicolon is mouse button 3 (scroll button).
* Apostrophe is mouse button 2.
* All the alpha and number keys are multi-character UTF-8 (for more flexible Unicode).
* Set up for `Shift` and `Ctrl` modifiers (can be extended to `Alt` and `Win`).
* Examples:
  * Sporadic groups on shift alphas.
  * Families on unshifted and shifted numbers plus null set.
  * The maths can get complicated as these are the "44 prime kinds" of all simple symmetry groups (plus the irregular honorary sporadic "Tits Group"). I included the zero null set symbol too.
  * Some shortcuts to input C language structure and what I call [Amperzand](amperzand.md).
  * `Ctrl`+letters for double struck alphas.
  * `Ctrl`+`Shift`+alphanumerics for Korean Jamo, with the normally "hard shifts" on number up and left.
  * `Ctrl`+numbers and `Ctrl`+`Shift`+6, 7 or 8 produce 13 special dimensional double strikes.
  * `Win` holds both `Ctrl` and `Shift` (for Korean Jamo) and does automatic combining.

### **BQN** Layer (BLUE Layer Within BQN Specification)
* **BQN** unshifted and shifted.
* Backspace exits back to navigation GREEN mode.
* The bottom row of modifiers emit some strange keys which could be detected amongst the automatic Unicode modifiers.

```
┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬─────────┐
│~ ¬ │! ⎉ │@ ⚇ │# ⍟ │$ ◶ │% ⊘ │^ ⎊ │&   │*   │( ⟨ │) ⟩ │_ √ │+ ⋆ │Backspace│
│` ˜ │1 ˘ │2 ¨ │3 ⁼ │4 ⌜ │5 ´ │6 ˝ │7   │8 ∞ │9 ¯ │0 • │- ÷ │= × │         │
├────┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬──────┤
│Tab    │Q   │W 𝕎 │E ⍷ │R 𝕣 │T ⍋ │Y   │U   │I ⊑ │O ⊒ │P ⍳ │{ ⊣ │} ⊢ │|     │
│       │q ⌽ │w 𝕨 │e ∊ │r ↑ │t ∧ │y   │u ⊔ │i ⊏ │o ⊐ │p π │[ ← │] → │\     │
├───────┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴──────┤
│Caps    │A   │S 𝕊 │D   │F 𝔽 │G 𝔾 │H « │J   │K ⌾ │L » │: · │" ˙ │Enter     │
│lock    │a ⍉ │s 𝕤 │d ↕ │f 𝕗 │g 𝕘 │h ⊸ │j ∘ │k ○ │l ⟜ │; ⋄ │' ↩ │          │
├────────┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──────────┤
│Shift      │Z ⋈ │X 𝕏 │C   │V ⍒ │B ⌈ │N   │M ≢ │< ≤ │> ≥ │? ⇐ │Shift       │
│           │z ⥊ │x 𝕩 │c ↓ │v ∨ │b ⌊ │n   │m ≡ │, ∾ │. ≍ │/ ≠ │            │
└───────────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────────────┘
                             Space: ‿
```

### Unicode Shift Layer (`Fn` After `\` **BQN** Prefix MAGENTA Shift)
* Backspace works to remove characters.
* Enter works as expected to end a paragraph.
* All the alphanumeric keys form Unicode characters (definable in code).
* Tap `Fn` to exit if you accidentally enter this MAGENTA locked mode.
* Cursor block works as expected to navigate text.
* All other punctuation has defined Unicode in code too.
* Modifier keys don't change layers except `Fn` which releases the MAGENTA shift.
* Not quite as flexible as the `Mouse Shift Layer` as only single Unicode code points can be used.
* But as it is locking, an alternate alphabet can be placed on the keys.
* The bottom row of modifiers emit some strange keys which could be detected amongst the automatic Unicode modifiers. This also true for `Shift` on this layer.
* Caps lock emits `ExSel`, a strange keycode usually not on keyboards.
* Tab does a tab and not `Ctrl`+`Alt`+`Del`, as this mode is designed for hours of fun as long as the `Fn` adult button is not pushed. Just the kind of thing for a novel.

## Macro-board Layer (YELLOW Layer)
* Escape is a one shot sticky `Ctrl`+`Shift`.
* Tab is a one shot sticky `Alt`+ `Shift`.
* Caps lock is a one shot sticky `Alt`+ `Ctrl`.
* The above is arranged so that the further down the keys are, the more down and to the right the group in pairs excluding the `Win` key is.
* This is because the `Win` key is less to do with application shortcuts, and more to do with the OS shortcuts. It is its own sticky.
* All modifiers are one shot sticky.
* `Fn` is not a sticky modifier, but cycles through the macro layers.
* F1 to F12 form top row numbers and minus/equals.
* F13 to F24 form second row Q-].
* F1 to F12 form third row A-enter with an implicit right `Alt Gr` applied.
* F13 to F23 form a fourth row Z-right shift with an implicit right `Alt Gr` applied.
* Backslash is F24 with an implicit right `Alt Gr` applied.
* Depending on your system the "Level 3 Shift" may be removed by localization of `Alt Gr`.
* Right `Alt`/`Ctrl` are `Alt`+`Tab` window switches (reverse and forward).
* Right `Win` key is the sticky right `Win` key.
* Backspace is `Ctrl`+`Shift`+`Alt` combination sticky.

### Macro-board Shift Layer (`Fn` Tap Macro-board MAGENTA Shift)
* Minus and equals are Korean modifiers.
* International modifiers are on Q-O.
* System power down on P key.
* Numbers are the number pad numbers for macro code options.
* Remaining language 3 to 7 are on Z-M.
* Right `Alt`/`Ctrl` are `Alt`+`Tab` window switch (reverse and forward).
* Left `Shift` key is sticky left and right `GUI` together.
* Right `Shift` key is itself but one shot sticky.
* Left `Win` key is the sticky left shift+`Win`.
* Right `Win` key is the sticky right shift+`Win`.
* Comma/period/slash set mouse acceleration 1, 2 and 3.
* Square brackets are home and end.
* Enter is itself.
* Various Unicode characters µ/ℎ(M), °/⦵(K), £/€(L), ω/Ω(Z), ∫/Σ(S), ∂/∇(D) and √/∛(G).
* Volume is up(J) and down(H).
* Browser search is A, favourites is F.
* Caps lock is number lock (the lighting is inverse, so off lights white).
* Backtick is escape.
* Space is `Alt Gr`+space.
* `Fn` cycles onto the CYAN Extra layer.

### Extra Shift Layer (`Fn` Tap Layer CYAN Shift)
* This layer toggle locks.
* `Fn` cycles to the YELLOW layer.
* `Ctrl`, `Shift` and `Alt` select one of eight modification planes.
* `Win` keys work as left and right cursor.
