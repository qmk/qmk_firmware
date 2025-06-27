# PaletteFx

<table>
<tr><td><b>Module</b></td><td><tt>getreuer/palettefx</tt></td></tr>
<tr><td><b>Version</b></td><td>2025-03-07</td></tr>
<tr><td><b>Maintainer</b></td><td>Pascal Getreuer (@getreuer)</td></tr>
<tr><td><b>License</b></td><td><a href="../LICENSE.txt">Apache 2.0</a></td></tr>
<tr><td><b>Documentation</b></td><td>
<a href="https://getreuer.info/posts/keyboards/palettefx">https://getreuer.info/posts/keyboards/palettefx</a>
</td></tr>
</table>

This is a community module adaptation of
[PaletteFx](https://getreuer.info/posts/keyboards/palettefx) for colorful
palette-based RGB matrix effects. While most of QMK's built-in RGB matrix
effects are based on a single color hue, sampling from a palette of colors
allows for more personality. PaletteFx is a suite of custom effects for QMK's
RGB Matrix in which the effect colors are sampled from a palette, aka color
gradient or color map.


## Add PaletteFx to your keymap

Add the following to your `keymap.json`:

```json
{
    "modules": ["getreuer/palettefx"]
}
```

Then in your keymap folder, create a file `rgb_matrix_user.inc` with the
following content, or if it already exists, add this as the first line:

```c
#include "palettefx.inc"
```

## Using PaletteFx

**Selecting effects:** PaletteFx effects are appended to the list of existing
RGB Matrix effects. Use the usual `RM_NEXT` / `RM_PREV` keycodes to switch to
the PaletteFx effects.

**Selecting palettes:** PaletteFx effects repurpose the RGB Matrix hue setting to
select which palette to use. Use the hue keycodes `RM_HUEU` / `RM_HUED` to cycle
through them. The `i`th palette corresponds to hue = `RGB_MATRIX_HUE_STEP * i`.


## Further details

Optionally, you can define your own palettes and palette-based effects. See the
[PaletteFx documentation](https://getreuer.info/posts/keyboards/palettefx) for
details.

