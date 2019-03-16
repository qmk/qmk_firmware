# @noroadsleft's KC60 keymap

- [Table of Contents](./readme.md)
  1. [Base Layers](./readme_ch1.md)
  2. [OS Overlays](./readme_ch2.md)
  3. [Quake 2 Overlays](./readme_ch3.md)
  4. [Function Layers](./readme_ch4.md)
  5. **Other Layers**


----

## Layer 10: Numpad layer - `_NP`

### Accessed by holding either `Fn` key and tapping `Space`, from any of the Base Layers

Puts a Numpad on the right-hand side of the keyboard. A through F included for hexadecimal input. Tapping `Space` returns to the previous Base Layer.

![Numpad layer](https://i.imgur.com/fKVRkGH.png)


----

## Layer 11: Macro layer - `_MA`

### Accessed by holding the `Fn` key and tapping the right-side `Win` key

Has some macros that I use in Git, and some frequently-typed strings.

Tapping `Esc` exits the Macro layer, if the macro used doesn't do it automatically.

![Macro layer](https://i.imgur.com/wgbsluI.png)


### Macros

#### [T_L3DED](./keymap.c#L122-L126)

Output: `lavak3DED `

Twitch emote for [a streamer I watch a lot](https://www.twitch.tv/lavak3_).  
![lavak3DED](https://static-cdn.jtvnw.net/emoticons/v1/821796/1.0)

#### [G_PUSH](./keymap.c#L127-L131)

Output: `git push origin `

Everything from here down is related to Git or GitHub.

#### [G_FTCH](./keymap.c#L132-L141)

| Condition | Output |
| :-------- | :----- |
| If <kbd>Shift</kbd> is active | `git pull upstream ` |
| Otherwise | `git fetch upstream ` |

#### [G_COMM](./keymap.c#L142-L147)

Output: `git commit -m ""` <kbd>Left</kbd>

Readies a `git commit` command, moves the cursor between the quotation marks, then disables the Macro layer.

#### [G_BRCH](./keymap.c#L148-158)

| Condition | Output |
| :-------- | :----- |
| If <kbd>Shift</kbd> is active | `master` |
| Otherwise | `$(git branch-name)` |

`$(git branch-name)` is a [git alias](./readme_git.md) that returns the name of the current branch. This macro disables the Macro layer when finished.

#### [SIGNA](./keymap.c#L159-L164)

Output: `\- @noroadsleft` <kbd>Enter</kbd>

Sometimes on GitHub, I sign my comments. Types my GitHub name in Markdown syntax, and then taps the `Enter` key. Disables the Macro layer when finished.

#### [MC_UNDO](./keymap.c#L202-L210)

| Condition | Output |
| :-------- | :----- |
| If <kbd>Shift</kbd> is active | <kbd>Shift</kbd> + <kbd>Command</kbd> + <kbd>Z</kbd> |
| Otherwise | <kbd>Command</kbd> + <kbd>Z</kbd> |

An Undo shortcut that turns to Redo if <kbd>Shift</kbd> is being held. I'm not sure that part is required to get that behavior, but it works as desired, so I'm not messing with it.

#### [MC_PSTE](./keymap.c#L211-L219)

| Condition | Output |
| :-------- | :----- |
| If <kbd>Shift</kbd> is active | <kbd>Shift</kbd> + <kbd>Command</kbd> + <kbd>Option</kbd> + <kbd>V</kbd> |
| Otherwise | <kbd>Command</kbd> + <kbd>V</kbd> |

The program I use this in uses <kbd>Shift</kbd> + <kbd>Command</kbd> + <kbd>Option</kbd> + <kbd>V</kbd> to paste while maintaining formatting (typeface, text size, etc.). Sometimes I want this and sometimes I don't. Using <kbd>Shift</kbd> changes the behavior.

#### [NUBS_Z](./keymap.c#L220-L228)

| Condition | Output |
| :-------- | :----- |
| If Right <kbd>Alt</kbd> is active | `KC_NUBS` |
| Otherwise | `KC_Z` |

Sometimes I type in languages from countries that use ISO layout, but my keyboard is ANSI, so I have one key fewer. This macro simulates the Non-US Backslash key if I use Right Alt + Z.

#### [VRSN](./keymap.c#L229-L233)

Outputs a string that tells me the Git commit from which my flashed firmware was built. Looks something like:

    kc60/noroadsleft @ 0.6.240-20-ge91549-dirty

----

### Layer 12: System layer - `_SY`

#### Accessed by holding either `Fn` key and tapping the `/?` key

This is where I change my keyboard function. Base layer select on `1` through `3`, Backlight controls on `C` through `N`, Reset on `8*`, Debug on `0)`.

![System layer](https://i.imgur.com/95ovTBn.png)


----

[Back to the index.](./)
