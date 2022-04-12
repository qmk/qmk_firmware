![Base](https://meagerfindings.com/assets/img/ergodox/base.png)

# Meagerfinding's ErgoDox Layout

<!-- TOC depthFrom:2 depthTo:6 withLinks:1 updateOnSave:1 orderedList:0 -->

- [Overview](#overview)
- [Credit where credit is due](#credit-where-credit-is-due)
- [Features](#features)
	- [Tap/Hold Macro Keys](#taphold-macro-keys)
	- [TapDance Keys](#tapdance-keys)
- [Base Layer](#base-layer)
	- [Things to note:](#things-to-note)
- [Old Base Layer](#old-base-layer)
- [Symbols Layer](#symbols-layer)
- [Mouse & Media Keys Layer](#mouse-media-keys-layer)
- [Markdown Layer](#markdown-layer)
- [Arrow/Movements Layer](#arrowmovements-layer)
- [Numpad Layer](#numpad-layer)

<!-- /TOC -->

## Overview

The overall goals of this layout are to:
1. Use the Ergodox thumb clusters to eliminate pinky reach.
2. Place as many useful keys under the home rows as possible.

I first decided to build an ErgoDox as I wanted to use my thumbs for more with the added ergonomic benefits of a split board and ortholinear layout. I knew my hands were hurting from the weird contortions of copying and pasting constantly on my Mac, but I had no idea how strained I really was until I started moving as many modifier keys to the thumb clusters.

## Credit where credit is due

The initial layout used created on the [ErgoDox EZ Configurator](https://ergodox-ez.com/pages/graphical-configurator). I went through 26+ iterations within the configurator prior to beginning my journey with QMK itself. Much of the dual function/layer keys are influenced by and adapted from the EZ Configurator.

Many features in this layout are either directly inspired by or are adaptations of [Algernon's incredible ErgoDox layout](https://github.com/algernon/ergodox-layout). Specifically: TapDance and its usage, and the brilliant idea of using TapDance to pair down the four keys for parens, brackets, and curly braces into just 2 keys.

## Features

### Tap/Hold Macro Keys
* `Paste/Paste Special` key sends Paste on tap and Paste Special when held.
* `Screen/Video` key sends `||scrn` when tapped and `||video` when held
  - [Typinator](http://www.ergonis.com/products/typinator/) expands `||scrn` into `(Screenshot: <CLIPBOARD CONTENTS>)`, and `||video` into `(Video: <CLIPBOARD CONTENTS>)`, the QMK macro then moves back to before the last paren, inserts a space and removes a space to create a hyperlink for use in Zendesk.
* When tapped, `Todoist` toggles quick add window for a new Todoist task (`CMD + Shift + A`) and switches to Todoist when held
* The RubyMine key opens RubyMine by triggering spotlight, typing out `Rubymine`, and submitting the enter key.
* `Zendesk` triggers spotlight and then calls Typinator expansion to open my Zendesk Agent dashboard in Chrome.


### TapDance Keys
* `Copy/Cut` key copies on tap, cut's on two taps.
* One tap on `Snagit` key = sends `Ctrl + Shift + C` which is Snagit's selector and two taps on `Snagit` key = `Cmd + Shift + Opt + 4`, OS X cropping screenshot that is copied to the clipboard only.
* Tapping the `[{(`/`)}]` keys once yields `[` or `{` when the shift key is engaged, tapping them twice yields `(`.

## Base Layer

![Base](https://meagerfindings.com/assets/img/ergodox/base.png)

The base layer retains the alphas from the QWERTY layout without any modifications.

### Things to note:

- The shift key is a One Shot Modifier key, meaning shift is not submitted when the key is tapped, instead, it only submits when you either tap it again, or on the next key press.
  - There is no CAPSLOCK key designated as it is pretty comfortable to simply hold down shift in this layout and continue typing.
- There is only one layer that you can fully switch to on this layout, the [Old Base layer](#old-base-layer). All other layers require holding a key to reach them. For the most part, the key that toggles a layer, will be on the opposite hand that will be typing with that layer.
  - For example: the symbols layer is reached by holding down the enter key with your right thumb, and most of the symbols are located on the left hand board.


## Old Base Layer

![Old Base](https://meagerfindings.com/assets/img/ergodox/old_base.png)

I am moving into a new position (software engineering) at work from a Support position. My hope is to use my F keys more often and write fewer emails. This is my old base layer, still easily accessible, as I'm not used to having F key's on my top row quite yet.

## Symbols Layer

![Symbols](https://meagerfindings.com/assets/img/ergodox/symbols.png)

Holding down the `enter` key with your right thumb toggles the symbol layer.

I've placed my most used symbols under the homerow. Granted, right now I mainly right emails/support ticket responses, so this home row may need to change as I transition to software engineering.

## Mouse & Media Keys Layer

![Mouse & Media](https://meagerfindings.com/assets/img/ergodox/mouse_media.png)

Holding down the `:` key on with your right pinky toggles the mouse and media layer. Your left hand controls the mouse directions just in a similar fashion to the keys used in the [movement layer](#arrowmovements-layer).

The right hand has a media controls under the homerow for quick muting/pausing.

* `XKCD #1319` Key that ironically partially-automates accessing the link to [XKCD #1319](https://xkcd.com/1319/).

## Markdown Layer

![Markdown](https://meagerfindings.com/assets/img/ergodox/markdown.png)

This layer places most common markdown symbols under the right hand. You can reach this layer by holding down the `F` key on your left hand.

## Arrow/Movements Layer

![Movement](https://meagerfindings.com/assets/img/ergodox/movement_arrows.png)

Toggled by holding down the space key with the right thumb. This isn't vim like movement, nope, it's `WASD` but over one column. So I guess it's actually `ESDF` on the left hand and `IJKL` on the right hand to better line up with the columns offset/staggered columns on the Dox.

## Numpad Layer

![Numpad](https://meagerfindings.com/assets/img/ergodox/numpad.png)

My right hand is pretty comfortable with tenkey number input so this is easily accessible by holding down backspace with the left thumb.

Also, on the left hand, there is a tap to copy and hold to cut macro under the `D` key, and a tap to paste and a hold to paste special macro on the `F` key. I guess I'm to too lazy to move my fingers when copying/pasting...
