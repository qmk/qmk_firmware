# @noroadsleft's Userspace

This directory holds the code that's the same for every keyboard I use in QMK, which is currently:

- `kc60`
- `kbdfans/kbd75/rev1`
- `coseyfannitutti/discipline`


## Macro Features and Custom Keycodes

### [VRSN](./noroadsleft.c#L44-L48)

Outputs a string that tells me the Git commit from which my flashed firmware was built. Looks something like:

    kc60:noroadsleft @ 0.6.326-6-gae6d7b-dirty

### Git Macros

Some frequently used Git commands.

| Keycode                             | Output                 | Output with <kbd>Shift</kbd> |
| :---------------------------------- | :--------------------- | :--------------------------- |
| [`G_PUSH`](./noroadsleft.c#L49-L53) | `git push origin `     | `git push origin `           |
| [`G_FTCH`](./noroadsleft.c#L54-L63) | `git fetch upstream `  | `git pull upstream `         |
| [`G_BRCH`](./noroadsleft.c#L64-L73) | `master`               | `$(git branch-name)`         |

`$(git branch-name)` is an alias for `git rev-parse --abbrev-ref HEAD`, which normally returns the name of the current branch.

### "Macro Mode" Macros and Customized Keycodes

Some of my macros and keycodes do different things depending on the value of the [`macroMode` variable](./noroadsleft.c#L23), which is [toggled between `0` and `1`](./noroadsleft.c#L127-L131) by the `M_MDSWP` custom keycode.[<sup>1</sup>](#footnotes) This is mainly at attempt to make various shortcuts use the same physical key combinations between Windows/Linux and MacOS (which I use at home and work, respectively).

| Keycode                                | `macroMode == 0` | `macroMode == 1` | `macroMode == 1` with <kbd>Shift</kbd> |
| :------------------------------------- | :--------------- | :--------------- | :------------------------------------- |
| [`M_SALL`](./noroadsleft.c#L74-L82)    | `Ctrl+A`         | `Cmd+A`          | `Cmd+A`                                |
| [`M_UNDO`](./noroadsleft.c#L83-L95)    | `Ctrl+Z`         | `Cmd+Z`          | `Cmd+Shift+Z`                          |
| [`M_CUT`](./noroadsleft.c#L96-L104)    | `Ctrl+X`         | `Cmd+X`          | `Cmd+X`                                |
| [`M_COPY`](./noroadsleft.c#L105-L113)  | `Ctrl+C`         | `Cmd+C`          | `Cmd+C`                                |
| [`M_PASTE`](./noroadsleft.c#L114-L126) | `Ctrl+V`         | `Cmd+V`          | `Cmd+Shift+Opt+V`                      |
| [`KC_PSCR`](./noroadsleft.c#L162-L170) | `KC_PSCR`        | `Cmd+Shift+3`    | `Cmd+Shift+3`                          |
| [`KC_HOME`](./noroadsleft.c#L171-L179) | `KC_HOME`        | `Cmd+Left`       | `Cmd+Left`                             |
| [`KC_END`](./noroadsleft.c#L180-L188)  | `KC_END`         | `Cmd+Right`      | `Cmd+Right`                            |

### [Emulated Non-US Backslash](./noroadsleft.c#L32-L42)

Sometimes I type in languages from countries that use ISO layout, but my keyboards are all ANSI layout, so I have one key fewer than necessary.

This macro simulates the Non-US Backslash key if I hold Right Alt and tap the key to the right of Left Shift.

Requires defining `ANSI_NUBS_ROW` and `ANSI_NUBS_COL` in `config.h` at the keymap level.[<sup>2</sup>](#footnotes)

### [Emulated Numeric Keypad](./noroadsleft.c#L132-L146)

If I hold the Right Alt key, the number row (`KC_1` through `KC_0`) will output numpad keycodes instead of number row keycodes, enabling quicker access to characters like ™ and °.

### [Emulated Extended Function Keys](./noroadsleft.c#L147-L161)

Similar to the emulated numpad, if I hold the Right Alt key with the Fn key, the function row (`KC_F1` through `KC_F12`) will output keycodes `KC_F13` throught `KC_F24`.


## License

Copyright 2020-2021 James Young (@noroadsleft)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.


## Footnotes

- 1: [^](#macro-mode-macros-and-customized-keycodes) The `M_MDSWP` keycode is used in my keymaps in the following locations:
  - [KC60](../../keyboards/kc60/keymaps/noroadsleft/keymap.c#L111)
  - [KBDfans KBD75 rev1](../../keyboards/kbdfans/kbd75/keymaps/noroadsleft/keymap.c#L93)
  - [CoseyFannitutti Discipline](../../keyboards/coseyfannitutti/discipline/keymaps/noroadsleft/keymap.c#L66)
- 2: [^](#emulated-non-us-backslash) `ANSI_NUBS_ROW` and `ANSI_NUBS_COL` are in the following locations:
  - [KC60](../../keyboards/kc60/keymaps/noroadsleft/config.h#L35-L36)
  - [KBDfans KBD75 rev1](../../keyboards/kbdfans/kbd75/keymaps/noroadsleft/config.h#L26-L27)
  - [CoseyFannitutti Discipline](../../keyboards/coseyfannitutti/discipline/keymaps/noroadsleft/config.h#L19-L20)
