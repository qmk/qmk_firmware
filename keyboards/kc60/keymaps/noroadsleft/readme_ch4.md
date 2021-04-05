# @noroadsleft's KC60 keymap

- [Table of Contents](./readme.md)
  1. [Base Layers](./readme_ch1.md)
  2. [Quake 2 Overlays](./readme_ch2.md)
  3. [Function Layers](./readme_ch3.md)
  4. **Other Layers**


----

## Layer 8: Numpad layer - `_NP`

### Accessed by holding either `Fn` key and tapping `Space`, from any of the Base Layers

Puts a Numpad on the right-hand side of the keyboard. A through F included for hexadecimal input. Tapping `Space` returns to the previous Base Layer.

![Numpad layer](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/keyboards/kc60/keymaps/noroadsleft/Numpad.png)


----

## Layer 9: Macro layer - `_MA`

### Accessed by holding the right-side `Win` key

Has some macros that I use in Git, some frequently-typed strings, and keys for use with the [Dynamic Macros feature](https://docs.qmk.fm/#/feature_dynamic_macros).

Tapping `Esc` exits the Macro layer, if the macro used doesn't do it automatically.

![Macro layer](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/keyboards/kc60/keymaps/noroadsleft/Macro.png)


### Macros

#### [G_PUSH](./keymap.c#L71-L75)

Output: `git push origin `

Everything from here down is related to Git or GitHub.

#### [G_FTCH](./keymap.c#L76-L85)

| Condition | Output |
| :-------- | :----- |
| If <kbd>Shift</kbd> is active | `git pull upstream ` |
| Otherwise | `git fetch upstream ` |

#### [G_BRCH](./keymap.c#L86-L95)

| Condition | Output |
| :-------- | :----- |
| If <kbd>Shift</kbd> is active | `master` |
| Otherwise | `$(git branch-name)` |

`$(git branch-name)` is a [git alias](./readme_git.md) that returns the name of the current branch.

#### [SIGNA](./keymap.c#L96-L100)

Output: `\- @noroadsleft` <kbd>Enter</kbd>

Sometimes on GitHub, I sign my comments. Types my GitHub name in Markdown syntax, and then taps the `Enter` key.

#### "Macro Mode" Macros and Customized Keycodes

Some of my macros and keycodes do different things depending on the value of the [`macroMode` variable](./keymap.c#L65), which is toggled between `0` and `1` by the [`M_MDSWP` custom keycode](./keymap.c#L238-L242). This is mainly at attempt to make various shortcuts the same key combinations between Windows/Linux and MacOS (which I use at home and work, respectively).

| Keycode                         | `macroMode == 0` | `macroMode == 1` | `macroMode == 1` with Shift  |
| :------------------------------ | :--------------- | :--------------- | :--------------------------- |
| [M_SALL](./keymap.c#L138-L146)  | `Ctrl+A`         | `Cmd+A`          | `Cmd+A`                      |
| [M_UNDO](./keymap.c#L147-L159)  | `Ctrl+Z`         | `Cmd+Z`          | `Cmd+Shift+Z`                |
| [M_CUT](./keymap.c#L160-L168)   | `Ctrl+X`         | `Cmd+X`          | `Cmd+X`                      |
| [M_COPY](./keymap.c#L169-L177)  | `Ctrl+C`         | `Cmd+C`          | `Cmd+C`                      |
| [M_PASTE](./keymap.c#L178-L190) | `Ctrl+V`         | `Cmd+V`          | `Cmd+Shift+Opt+V`            |
| `KC_HOME`                       | `KC_HOME`        | `Cmd+Left`       | `Cmd+Left`                   |
| `KC_END`                        | `KC_END`         | `Cmd+Right`      | `Cmd+Right`                  |
| `KC_PSCR`                       | `KC_PSCR`        | `Cmd+Shift+3`    | `Cmd+Shift+3`                |

#### [Emulated Non-US Backslash](./keymap.c#L218-L232)

Sometimes I type in languages from countries that use ISO layout, but my keyboard is ANSI, so I have one key fewer. This macro simulates the Non-US Backslash key if I use Right Alt + Z.

#### [VRSN](./keymap.c#L233-L237)

Outputs a string that tells me the Git commit from which my flashed firmware was built. Looks something like:

    kc60/noroadsleft @ 0.6.326-6-gae6d7b-dirty

#### [Emulated Numeric Keypad](./keymap.c#L243-L257)

If I hold the Right Alt key, the number row (`KC_1` through `KC_0`) will output numpad keycodes instead of number row keycodes, enabling quicker access to characters like ™ and °.

#### [Emulated Extended Function Keys](./keymap.c#L258-L272)

Similar to the emulated numpad, if I hold the Right Alt key with the Fn key, the function row (`KC_F1` through `KC_F12`) will output keycodes `KC_F13` throught `KC_F24`.

----

### Layer 10: System layer - `_SY`

#### Accessed by holding either `Fn` key and tapping the `/?` key

This is where I change my keyboard function. Base layer select on `1` through `3`, Backlight controls on `C` through `N`, Reset on `8*`, Debug on `0)`.

![System layer](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/keyboards/kc60/keymaps/noroadsleft/System.png)


----

[Back to the index.](./)
