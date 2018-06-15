# @noroadsleft's KC60 keymap

## Last updated: June 8, 2018, 3:13 PM UTC-0700

![](https://i.imgur.com/tzhXQYI.jpg)

I am a full-time Dvorak typist, and occasional semi-serious FPS gamer. All the layers, however, are oriented towards typing and my most-used activities. A custom FPS-gaming-oriented layer is on my wish list, but I haven't gotten there yet.


# Layer Outline

- Base Layers
  - Layer 0: QWERTY
  - Layer 1: Hardware Dvorak
- Function Layers
  - Layer 2: Windows Fn layer
  - Layer 3: MacOS-oriented Fn layer
- Other Layers
  - Layer 4: Numpad layer
  - Layer 5: Macro layer


# Layers

## Layer 0: QWERTY

Standard QWERTY layout, with three QMK features:

- The `Menu` key has been replaced by `MO(_FW)`, which moves to my Windows Fn layer when held.
- The `Caps Lock` key has been replaced with a dual function `LT()` key, which opens the Windows Fn layer when held, and is `Caps Lock` when tapped
- The `Escape` key becomes a `` ` ~ `` key when used with a `Fn` key or a `Shift` key

For the rest of this readme, keys will be referred to by their function in a US QWERTY layout.


## Layer 1: Hardware Dvorak

A hardware-based Dvorak Simplified layout. At my weekend job, I use a shared computer that runs MacOS Sierra, in US QWERTY layout. In this layer, I can leave the system in QWERTY, plug my keyboard in, and still type in Dvorak.

Holding either `Fn` key and tapping the `/?` key switches between each Base Layer.


## Layer 2: Windows Fn layer

### Accessed by holding either `Fn` key in Layer 0

Arrows, Navigation keys (Insert, Home, Page Up, etc.), and Function keys are here. Also has the keys for Backlighting and Volume Control.

 `Fn`+Key    | Function                      |   | `Fn`+Key            | Function
 :---------: | :---------------------------: |:-:| :-----------------: | :--------------------------:
 Number Row  | F1 through F12                |   | `[ {`               | Print Screen
 `] }`       | Scroll Lock                   |   | `\ \|`              | Pause/Break
 `I`         | Up                            |   | `K`                 | Down
 `J`         | Left                          |   | `L`                 | Right
 `Y`         | Insert                        |   | `H` or `Backspace`  | Delete
 `U`         | Home                          |   | `O`                 | End
 `P`         | Page Up                       |   | `; :`               | Page Down
 `Q`         | Calculator                    |   | `Enter`             | Numpad Enter
 `X`         | Menu                          |   | `C`                 | Backlight Brightness Down
 `V`         | Backlight Toggle              |   | `B`                 | Backlight Brightness Up
 `N`         | Backlight Breathing Toggle    |   | `M`                 | Toggle Mute
 `, <`       | Volume Down                   |   | `. >`               | Volume Up


## Layer 3: MacOS-oriented Fn layer

### Accessed by holding either `Fn` key in Layer 1

Based on Layer 2, but swaps a few functions for a MacOS environment. Arrow, Navigation, and Function keys are basically unchanged from Layer 2. This layer enables using the Caps-as-Fn key as a sort of simulated `Command` key, which I find easier to reach and use.

 `Fn`+Key   | Function          | Notes
 :--------: | :---------------: | :------------------------------
 `[ {`      | Screen Capture    | Saves a screen capture as a PNG image on the Desktop
 `U`        | Home              | Moves to the beginning of a line (Normally `Command`+`Left Arrow`)
 `O`        | End               | Moves to the end of a line (Normally `Command`+`Right Arrow`)
 `A`        | Select All        | Normally `Command`+`A`
 `F`        | Backlight Toggle  |
 `Z`        | Undo              | Normally `Command`+`Z`
 `X`        | Cut               | Normally `Command`+`X`
 `C`        | Copy              | Normally `Command`+`C`
 `V`        | Paste             | Normally `Command`+`V`


## Layer 4: Numpad layer

### Accessed by holding either `Fn` key and tapping `Space`, from either of the Base Layers

Puts a Numpad on the right-hand side of the keyboard. Tapping `Space` returns to the previous Base Layer.

```
┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
│   │   │   │   │   │   │   │7  │8  │9  │   │   │   │       │
├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
│     │   │   │   │   │   │   │4  │5  │6  │*  │/  │=  │     │
├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
│      │   │   │   │ • │   │   │1• │2  │3  │+  │-  │Num Ent │
├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
│        │   │   │   │   │   │   │0  │   │.  │   │          │
├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
│    │    │    │ Return to Base layer   │    │    │    │    │
└────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
```


## Layer 5: Macro layer

### Accessed by holding the `Fn` key and tapping the right-side `Win` key

Has some macros that I use in Git, and some frequently-typed strings. `Reset` key on Left `Ctrl`, which I really need to move.

Tapping the right-hand `Win` key exits the Macro layer, if the macro you use doesn't do it automatically.

```
┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
│   │   │   │   │   │   │   │   │   │   │   │   │   │       │
├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
│     │   │or │gu │up │   │   │   │   │   │tp │   │   │     │
├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
│      │   │   │gd │cm │   │   │   │   │tl │   │   │        │
├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
│        │   │   │cf │   │br │sg │   │   │   │   │          │
├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
│RST │    │    │                        │    │exit│    │    │
└────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
```

  ID   |  Macro  |  Inputs                     | Source                    | Usage
 :---: | :-----: | :-------------------------: | :-----------------------: | :----
  tl   | T_L3DED | `lavak3DED `                | [Line 51](./keymap.c#L51) | Twitch emote for a streamer I watch a lot.
  tp   | T_PEEKR | `"will u touch my peeker?"` | [Line 54](./keymap.c#L54) | A friend of mine who streams on Twitch says this a lot when she plays a specific character.
  gu   | G_PUSH  | `git pull `                 | [Line 57](./keymap.c#L57) | Everything from here down is related to Git or GitHub.
  gd   | G_PULL  | `git push `                 | [Line 60](./keymap.c#L60) |
  up   | G_UPS   | `upstream `                 | [Line 63](./keymap.c#L63) |
  or   | G_ORIG  | `origin `                   | [Line 66](./keymap.c#L66) |
  cm   | G_COMM  | `git commit -m ""` `[Left]` | [Line 69](./keymap.c#L69) | Types a `git commit` command, moves the cursor between the quotation marks, then disables the Macro layer.
  cf   | G_C10R  | `c10r-`                     | [Line 73](./keymap.c#L73) | A branch prefix I use for my current work in QMK. Disables the Macro layer when finished.
  br   | G_BRCH  | `$(git branch-name)`        | [Line 77](./keymap.c#L77) | Returns the name of the current branch in Git, when combined with a [Git alias](readme_git.md) I have set up. Disables the Macro layer when finished.
  sg   | SIGNA   | `\- @noroadsleft` `[Enter]` | [Line 81](./keymap.c#L81) | Sometimes on GitHub, I sign my comments. Types my GitHub name in Markdown syntax, and then taps the `Enter` key. Disables the Macro layer when finished.
