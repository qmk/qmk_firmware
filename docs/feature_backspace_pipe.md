# Backspace Pipe

If you're using a Tsangan/HHKB layout with split backspace, you might might want to keep pressing Shift+`KC_BSPC` to produce a Pipe (`|`).

## Usage

Replace Backspace(`KC_BSPC`) key in your keymap with `QK_BSPIPE`.

## What Your OS Sees

Most of the time `QK_BSPIPE` will output `KC_BSPC` when pressed. However, when Shift is held down it will output a Pipe (`|`) instead, and when GUI/CMD/WIN is held down it will output a Backslash(`\`).

## Keycodes

|Key                |Aliases    |Description                                                          |
|-------------------|-----------|---------------------------------------------------------------------|
|`QK_BACKSPACE_PIPE`|`QK_BSPIPE`|Backspace when pressed, <br><code>&vert;</code> when chorded with Shift or<br><code>&bsol;</code> when chorded with GUI|
