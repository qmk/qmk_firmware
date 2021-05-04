# @noroadsleft's Userspace

This directory holds the code that's the same for every keyboard I use in QMK, which is currently:

- `kc60`
- `kbdfans/kbd75/rev1`
- `coseyfannitutti/discipline`


## Macro Features and Custom Keycodes

### [VRSN](./noroadsleft.c#L33-L37)

Outputs a string that tells me the Git commit from which my flashed firmware was built. Looks something like:

    kc60:noroadsleft @ 0.6.326-6-gae6d7b-dirty

### Git Macros

Some frequently used Git commands.

| Keycode                             | Output                 | Output with <kbd>Shift</kbd> |
| :---------------------------------- | :--------------------- | :--------------------------- |
| [`G_PUSH`](./noroadsleft.c#L38-L42) | `git push origin `     | `git push origin `           |
| [`G_FTCH`](./noroadsleft.c#L43-L52) | `git fetch upstream `  | `git pull upstream `         |
| [`G_BRCH`](./noroadsleft.c#L53-L62) | `master`               | `$(git branch-name)`         |

`$(git branch-name)` is an alias for `git rev-parse --abbrev-ref HEAD`, which normally returns the name of the current branch.

### "Macro Mode" Macros and Customized Keycodes

Some of my macros and keycodes do different things depending on the value of the [`macroMode` variable](./noroadsleft.c#L23), which is [toggled between `0` and `1`](./noroadsleft.c#L116-L120) by the `M_MDSWP` custom keycode.[<sup>1</sup>](#footnotes) This is mainly at attempt to make various shortcuts use the same physical key combinations between Windows/Linux and MacOS (which I use at home and work, respectively).

| Keycode                                | `macroMode == 0` | `macroMode == 1` | `macroMode == 1` with <kbd>Shift</kbd> |
| :------------------------------------- | :--------------- | :--------------- | :------------------------------------- |
| [`M_SALL`](./noroadsleft.c#L63-L71)    | `Ctrl+A`         | `Cmd+A`          | `Cmd+A`                                |
| [`M_UNDO`](./noroadsleft.c#L72-L84)    | `Ctrl+Z`         | `Cmd+Z`          | `Cmd+Shift+Z`                          |
| [`M_CUT`](./noroadsleft.c#L85-L93)     | `Ctrl+X`         | `Cmd+X`          | `Cmd+X`                                |
| [`M_COPY`](./noroadsleft.c#L94-L102)   | `Ctrl+C`         | `Cmd+C`          | `Cmd+C`                                |
| [`M_PASTE`](./noroadsleft.c#L103-L115) | `Ctrl+V`         | `Cmd+V`          | `Cmd+Shift+Opt+V`                      |
| [`KC_PSCR`](./noroadsleft.c#L166-L174) | `KC_PSCR`        | `Cmd+Shift+3`    | `Cmd+Shift+3`                          |
| [`KC_HOME`](./noroadsleft.c#L175-L183) | `KC_HOME`        | `Cmd+Left`       | `Cmd+Left`                             |
| [`KC_END`](./noroadsleft.c#L184-L192)  | `KC_END`         | `Cmd+Right`      | `Cmd+Right`                            |

### [Emulated Non-US Backslash](./noroadsleft.c#L121-L135)

Sometimes I type in languages from countries that use ISO layout, but my keyboard is ANSI, so I have one key fewer. This macro simulates the Non-US Backslash key if I use Right Alt + `KC_Z`.

### [Emulated Numeric Keypad](./noroadsleft.c#L136-L150)

If I hold the Right Alt key, the number row (`KC_1` through `KC_0`) will output numpad keycodes instead of number row keycodes, enabling quicker access to characters like ™ and °.

### [Emulated Extended Function Keys](./noroadsleft.c#L151-L165)

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
