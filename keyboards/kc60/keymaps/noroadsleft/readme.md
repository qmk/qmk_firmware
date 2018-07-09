# @noroadsleft's KC60 keymap

## Last updated: July 9, 2018, 10:31 AM UTC-0700

![](https://i.imgur.com/tzhXQYI.jpg)

I am a full-time Dvorak typist, and occasional semi-serious FPS gamer. The layers are oriented towards a mix of typing and gaming.


# Layer Outline

- Base Layers
  - Layer 0: QWERTY
  - Layer 1: Hardware Dvorak
- Overlays
  - Layers 2, 3 and 4: Quake 2 and Quake 2 Dvorak
- Function Layers
  - Layer 5: Windows Fn layer
  - Layer 6: MacOS-oriented Fn layer
  - Layer 7: Quake 2 Fn layer
- Other Layers
  - Layer 8: Numpad layer
  - Layer 9: Macro layer
  - Layer 10: System layer


# Layers

## Base Layers

### Layer 0: QWERTY - `_QW`

Standard QWERTY layout, with three QMK features:

- The `Menu` key has been replaced by `MO(_FW)`, which moves to my Windows Fn layer when held.
- The `Caps Lock` key has been replaced with a dual function `LT()` key, which opens the Windows Fn layer when held, and is `Caps Lock` when tapped
- The `Escape` key becomes a `` ` ~ `` key when used with a `Fn` key or a `Shift` key

For the rest of this readme, the physical location of keys will be referred to by their function in a US QWERTY layout.

```
┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
│GE │1 !│2 @│3 #│4 $│5 %│6 ^│7 &│8 *│9 (│0 )│- _│= +│ Bksp  │
├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
│ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │[ {│] }│ \ | │
├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
│ LT2  │ A │ S │ D │ F │ G │ H │ J │ K │ L │; :│' "│ Enter  │
├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
│ Shift  │ Z │ X │ C │ V │ B │ N │ M │, <│. >│/ ?│  Shift   │
├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
│Ctrl│Win │Alt │                        │Alt │Win │MO2 │Ctrl│
└────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
```

 ID     | Function                  | Keycode(s) Sent     | Notes
 :----: | :-----------------------: | :------------------ | :------------------------------
 `GE`   | Grave/Escape              | `KC_GESC`           | `Esc` when tapped alone, `` ` ~ `` when used with a `Fn` key or a `Shift` key.
 `LT2`  | Momentarily Open Layer 2  | `LT(_FW, KC_CAPS)`  | Opens the Windows Fn layer when held; toggles Caps Lock when tapped.
 `MO2`  | Momentarily Open Layer 2  | `MO(_FW)`           | Opens the Windows Fn layer when held.


### Layer 1: Hardware Dvorak - `_DV`

#### Accessed by holding either `Fn` and tapping `/?` key, then tapping `2@`.

A hardware-based Dvorak Simplified layout. At my weekend job, I use a shared computer that runs MacOS Sierra, in US QWERTY layout. In this layer, I can leave the system in QWERTY, plug my keyboard in, and still type in Dvorak.

```
┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
│GE │1 !│2 @│3 #│4 $│5 %│6 ^│7 &│8 *│9 (│0 )│[ {│] }│ Bksp  │
├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
│ Tab │' "│, <│. >│ P │ Y │ F │ G │ C │ R │ L │/ ?│= +│ \ | │
├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
│ LT3  │ A │ O │ E │ U │ I │ D │ H │ T │ N │ S │- _│ Enter  │
├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
│ Shift  │; :│ Q │ J │ K │ X │ B │ M │ W │ V │ Z │  Shift   │
├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
│Ctrl│Win │Alt │                        │Alt │Win │MO3 │Ctrl│
└────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
```

 ID     | Function                  | Keycode(s) Sent     | Notes
 :----: | :-----------------------: | :------------------ | :------------------------------
 `GE`   | Grave/Escape              | `KC_GESC`           | `Esc` when tapped alone, `` ` ~ `` when used with a `Fn` key or a `Shift` key.
 `LT3`  | Momentarily Open Layer 3  | `LT(_FM, KC_CAPS)`  | Opens the MacOS-oriented function layer when held; toggles Caps Lock when tapped.
 `MO3`  | Momentarily Open Layer 3  | `MO(_FM)`           | Opens the MacOS-oriented function layer when held.


## Overlays

### Layer 2, 3 and 4: Quake 2 `_Q2`, Quake 2 Dvorak `_QD`, and Quake 2 Console `_QC`

#### Accessed by holding either `Fn` key and tapping the `/?` key, then tapping `3#`

These layers were born out of the confusion I have trying to use the in-game chat and the console in Quake 2. When Quake 2 came out, alternate keyboard layouts weren't really a thing. As a result, all in-game text input is hard-locked to US QWERTY, regardless of what the operating system is using for its input method.

I'm attempting to solve this by some creative use of QMK's macro feature. The keycode in the System layer that enables these layers, [`GO_Q2`](./keymap.c#L263), is a [macro](./keymap.c#L111-L116) that sets the default layer to the QWERTY layer, then turns the Quake 2 layer `_Q2` on. The result is a partially-overwritten QWERTY layer, that has some keycodes with some creative layer switching.

When I hit the `Enter` key (bound in-game to text chat), the [macro keycode](./keymap.c#L117-L121) I've created sends the keycode for `Enter`, then follows with enabling the Hardware Dvorak layer and its corresponding overlay. Now the game is in text chat mode, and my keyboard is in Dvorak. When I hit `Enter` again, another `Enter` [keycode macro](./keymap.c#L122-L126) is sent, which sends the message, then the macro brings me back to the standard QWERTY+Quake 2 setup. Hitting `Escape` runs a [macro](./keymap.c#L127-L131) that cancels the sending of the message, and undoes the layers.

I have not fully tested this configuration yet. Reports will come.


## Function Layers

### Layer 5: Windows Fn layer - `_FW`

#### Accessed by holding either `Fn` key in Layer 0

Arrows, Navigation keys (Insert, Home, Page Up, etc.), and Function keys are here. Also has keys for Volume Control.

```
┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
│   │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│Delete │
├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
│     │Cal│   │   │   │   │Ins│Hm │↑  │End│Pg↑│PSc│SLk│Pause│
├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
│      │   │   │   │   │   │Del│←  │↓  │→  │Pg↓│   │Num Ent │
├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
│        │   │App│   │   │   │   │VMt│V+ │V- │SYS│          │
├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
│    │    │    │ Toggle Numpad layer    │    │TgMa│    │    │
└────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
```

 ID       | Function
 :------: | :---------------:
 `PSc`    | Print Screen
 `SLk`    | Scroll Lock
 `Pause`  | Pause/Break
 `Cal`    | Calculator
 `App`    | Menu
 `VMt`    | Toggle Mute
 `V+`     | Volume Down
 `V-`     | Volume Up
 `SYS`    | Go to System layer
 `TgMa`   | Toggle Macro layer


### Layer 6: MacOS-oriented Fn layer - `_FM`

#### Accessed by holding either `Fn` key in Layer 1

Based on Layer 2, but swaps a few functions for a MacOS environment. Arrow, Navigation, and Function keys are basically unchanged from Layer 2. This layer enables using the Caps-as-Fn key as a sort of simulated `Command` key, which I find easier to reach and use.

```
┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
│   │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│Delete │
├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
│     │   │   │   │   │   │Ins│Hm │ ↑ │End│Pg↑│SCp│   │     │
├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
│      │All│   │   │   │   │Del│ ← │ ↓ │ → │Pg↓│   │Num Ent │
├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
│        │Und│Cut│Cpy│Pst│   │   │   │   │   │   │          │
├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
│    │    │    │ Toggle Numpad layer    │    │    │    │    │
└────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
```

 ID    | Function          | Keycode(s) Sent         | Notes
 :---: | :---------------: | :---------------------- | :------------------------------
  SCp  | Screen Capture    | `Command`+`Shift`+`3`   | Saves a screen capture as a PNG image on the Desktop
  Hm   | Home              | `Command`+`Left Arrow`  | Moves to the beginning of a line
  End  | End               | `Command`+`Right Arrow` | Moves to the end of a line
  All  | Select All        | `Command`+`A`           |
  Und  | Undo              | `Command`+`Z`           |
  Cut  | Cut               | `Command`+`X`           |
  Cpy  | Copy              | `Command`+`C`           |
  Pst  | Paste             | `Command`+`V`           |


### Layer 7: Quake 2 Fn layer - `_FQ`

#### Accessed by holding either `Fn` key while either Quake 2 overlay is active.

Based on the Windows function layer, but removes some functions that are pointless to have while in the game.

```
┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
│   │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│Delete │
├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
│     │   │   │   │   │   │Ins│Hm │ ↑ │End│Pg↑│PSc│SLk│Pause│
├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
│      │   │   │   │   │   │Del│ ← │ ↓ │ → │Pg↓│   │Enter   │
├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
│        │   │   │   │   │   │   │   │   │   │   │          │
├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
│    │    │    │                        │    │    │    │    │
└────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
```

 ID       | Function
 :------: | :---------------:
 `PSc`    | Print Screen
 `SLk`    | Scroll Lock
 `Pause`  | Pause/Break
 `SYS`    | Go to System layer
 `TgMa`   | Toggle Macro layer


## Other layers
  
### Layer 8: Numpad layer - `_NP`

#### Accessed by holding either `Fn` key and tapping `Space`, from either of the Base Layers

Puts a Numpad on the right-hand side of the keyboard. A through F included for hexadecimal input. Tapping `Space` returns to the previous Base Layer.

```
┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
│   │   │   │   │   │   │   │ 7 │ 8 │ 9 │   │   │   │       │
├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
│     │   │   │   │ E │ F │   │ 4 │ 5 │ 6 │ * │ / │ = │     │
├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
│      │   │   │   │ C │ D │   │ 1 │ 2 │ 3 │ + │ - │Num Ent │
├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
│        │   │   │   │ A │ B │   │ 0 │   │ . │   │          │
├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
│    │    │    │ Return to Base layer   │    │    │    │    │
└────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
```


### Layer 9: Macro layer - `_MA`

#### Accessed by holding the `Fn` key and tapping the right-side `Win` key

Has some macros that I use in Git, and some frequently-typed strings.

Tapping `Esc` exits the Macro layer, if the macro used doesn't do it automatically.

```
┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
│ext│   │   │   │   │   │   │   │   │   │   │   │   │       │
├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
│     │   │   │gp │   │   │   │   │   │   │   │   │   │     │
├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
│      │   │gr │gf │gc │   │   │   │   │tl │   │   │        │
├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
│        │   │   │cf │   │br │sg │   │   │   │   │          │
├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
│    │    │    │                        │    │    │    │    │
└────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
```

  ID   |  Macro  |  Inputs                      | Source                          | Usage
 :---: | :-----: | :--------------------------: | :-----------------------------: | :----
  tl   | T_L3DED | `lavak3DED `                 | [source](./keymap.c#L82-L84)    | Twitch emote for a streamer I watch a lot.
  gp   | G_PUSH  | `git push origin`            | [source](./keymap.c#L85-L87)    | Everything from here down is related to Git or GitHub.
  gf   | G_FTCH  | `git fetch upstream`         | [source](./keymap.c#L88-L90)    |
  gc   | G_COMM  | `git commit -m ""` `[Left]`  | [source](./keymap.c#L91-L94)    | Readies a `git commit` command, moves the cursor between the quotation marks, then disables the Macro layer.
  gr   | G_RST   | `git reset --soft `          | [source](./keymap.c#L95-L98)    | Runs a git alias that shows my last ten commits, then readies a `git reset --soft`. For when I commit something too soon. Disables the Macro layer when complete.
  cf   | G_C10R  | `cf/`                        | [source](./keymap.c#L99-L102)   | A branch prefix I use for my current work in QMK. Disables the Macro layer when finished.
  br   | G_BRCH  | `$(git branch-name)`         | [source](./keymap.c#L103-L106)  | A [git alias](./readme_git.md) that returns the name of the current branch. Disables the Macro layer when finished.
  sg   | SIGNA   | `\- @noroadsleft` `[Enter]`  | [source](./keymap.c#L107-L110)  | Sometimes on GitHub, I sign my comments. Types my GitHub name in Markdown syntax, and then taps the `Enter` key. Disables the Macro layer when finished.


### Layer 10: System layer - `_SY`

#### Accessed by holding either `Fn` key and tapping the `/?` key

This is where I change my keyboard function. Base layer select on `1` through `3`, Backlight controls on `C` through `N`, Reset on `8`.
