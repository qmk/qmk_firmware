# @noroadsleft's KC60 keymap

- [Table of Contents](./readme.md)
  1. [Base Layers](./readme_ch1.md)
  2. [OS Overlays](./readme_ch2.md)
  3. [Quake 2 Overlays](./readme_ch3.md)
  4. [Function Layers](./readme_ch4.md)
  5. **Other Layers**

### Last updated: September 2, 2018, 1:03 PM UTC-0700


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

[![lavak3DED](https://static-cdn.jtvnw.net/emoticons/v1/821796/1.0)](./keymap.c#L122-L127)  
Inputs: `lavak3DED `  
Twitch emote for [a streamer I watch a lot](https://www.twitch.tv/lavak3_).

[G_PUSH](./keymap.c#L128-L133)  
Inputs: `git push origin `  
Everything from here down is related to Git or GitHub.

[G_FTCH](./keymap.c#L134-L139)  
Inputs: `git fetch upstream`

[G_COMM](./keymap.c#L140-L146)  
Inputs: `git commit -m ""` `[Left]`  
Readies a `git commit` command, moves the cursor between the quotation marks, then disables the Macro layer.

[G_RST](./keymap.c#L147-L153)  
Inputs: `git histt -n 10`, Enter, `git reset --soft `  
Runs a [git alias](./readme_git.md) that shows my last ten commits, then readies a `git reset --soft`. For when I commit something too soon. Disables the Macro layer when complete.

[G_C10R](./keymap.c#L154-L160)  
Inputs: `cf/`  
A branch prefix I use for my current work in QMK. Disables the Macro layer when finished.

[G_BRCH](./keymap.c#L161-L167)  
Inputs: `$(git branch-name)`  
A [git alias](./readme_git.md) that returns the name of the current branch. Disables the Macro layer when finished.

[SIGNA](./keymap.c#L168-L174)  
Inputs: `\- @noroadsleft` `[Enter]`  
Sometimes on GitHub, I sign my comments. Types my GitHub name in Markdown syntax, and then taps the `Enter` key. Disables the Macro layer when finished.


----

### Layer 12: System layer - `_SY`

#### Accessed by holding either `Fn` key and tapping the `/?` key

This is where I change my keyboard function. Base layer select on `1` through `3`, Backlight controls on `C` through `N`, Reset on `8*`, Debug on `0)`.

![System layer](https://i.imgur.com/95ovTBn.png)


----

[Back to the index.](./)
