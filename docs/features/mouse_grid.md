# Mouse grid

Mouse grid is a feature for quickly positioning the mouse cursor using coordinate or grid based methods.

### Enabling mouse grid 

To enable mouse grid, add the following line to your keymap’s `rules.mk`:

```c
MOUSEGRID_ENABLE = yes
```

## Alphabet-based coordinates

One of the methods is to divide the screen into a 26x26 grid and position the mouse by inputting 2 characters for coordinates.

This is triggered by `QK_MOUSE_GRID_ALPHABET` (or `MG_ABC`) key that will wait for a few seconds for 2 keypresses that will be interpreted as characters specifying the coordinates where to place the mouse.

That is, when pressing `MG_ABC`, `KC_M`, `KC_P`, the mouse would be positioned:

| |A|B|C|…|L|M|N|…|X|Y|Z|
|-|-|-|-|-|-|-|-|-|-|-|-|
|A| | | | | | | | | | | |
|B| | | | | | | | | | | |
|C| | | | | | | | | | | |
|…| | | | | | | | | | | |
|O| | | | | | | | | | | |
|P| | | | | |X| | | | | |
|R| | | | | | | | | | | |
|…| | | | | | | | | | | |
|X| | | | | | | | | | | |
|Y| | | | | | | | | | | |
|Z| | | | | | | | | | | |

## Repeated directional grid

The other method works by repeatedly picking from a 3x3 grid to repeatedly zoom in towards the desired cursor position.

This is triggered by `QK_MOUSE_GRID_RESET` (or `MG_RST`) to center the cursor and then repeatedly picking one of the 9 positions in the grid:

|  |-1     |0     |+1     |
|--|-------|------|-------|
|-1|`MG_TL`|`MG_T`|`MG_TR`|
|0 |`MG_L` |`MG_C`|`MG_R` |
|+1|`MG_BL`|`MG_B`|`MG_BR`|

In first interation, the whole screen is divided into a 3x3 grid to pick from, while second iteration picks within the 3x3 subgrid of the "quadrant" picked in the first iteration.

Since the "quadrants" are not visualized on screen while navigating, if a movement target is kind of between two quadrants, it can be difficult to tell which one is the "correct" coordinate.

In order to be forgiving of some inaccuracy, the default configuration leaves a little bit of buffer by zooming in slightly less than would be required for the 1/9th of the "quadrant". This means that for slightly inaccurate path can still reach the target but may require an extra keystroke.

While practicing, `QK_MOUSE_GRID_ANIMATE` (or `MG_ANIM`) can be pressed to cause the cursor to quickly jump through all the 9 positions of each quadrant choice. Additionally, `QK_MOUSE_GRID_UNDO` (or `MG_UNDO`) can be used to undo the last quadrant choice.

## Precision

On a 1920x1080 screen an alphabet of 26 characters divides the screen into grid of ~75x50 rectangles. This can be enough for larger UI elements (eg: browser tabs) but to accurately point at dense UI elements (eg: menu items).

On a 1920x1080 screen it takes 4 iterations of 3x3 grid to point at a grid of ~35x20 rectangles, which allows pointing at event relatively small UI elements, like menu items.

Both grid methods can combined, but for fine adjustments it may be better to use the mouse keys feature.

However, the `QK_MOUSE_GRID_NEAR` (or `MG_NEAR`) key can be used to to zoom out the cursor tot he local area, so that next keystrokes would allow move to a nearby UI element faster, without resetting to the center of the screen.

## Mouse grid keycodes

Full list of mouse grid keycodes:

|Key                         |Alias    |Description                                     |
|----------------------------|---------|------------------------------------------------|
|`QK_MOUSE_GRID_ALPHABET`    |`MG_ABC` |Position cursor according to alphabet-based grid|
|`QK_MOUSE_GRID_RESET`       |`MG_RST` |Reset cursor to the center of the screen        |
|`QK_MOUSE_GRID_TOP_LEFT`    |`MG_TL`  |Pick top-left quadrant                          |
|`QK_MOUSE_GRID_TOP`         |`MG_T`   |Pick top quadrant                               |
|`QK_MOUSE_GRID_TOP_RIGHT`   |`MG_TR`  |Pick top-right quadrant                         |
|`QK_MOUSE_GRID_LEFT`        |`MG_L`   |Pick left quadrant                              |
|`QK_MOUSE_GRID_CENTER`      |`MG_C`   |Pick center quadrant                            |
|`QK_MOUSE_GRID_RIGHT`       |`MG_R`   |Pick right quadrant                             |
|`QK_MOUSE_GRID_BOTTOM_LEFT` |`MG_BL`  |Pick bottom-left quadrant                       |
|`QK_MOUSE_GRID_BOTTOM`      |`MG_B`   |Pick bottom quadrant                            |
|`QK_MOUSE_GRID_BOTTOM_RIGHT`|`MG_BR`  |Pick bottom-right quadrant                      |
|`QK_MOUSE_GRID_ANIMATE`     |`MG_ANIM`|Quickly move the cursor through all quadrants   |
|`QK_MOUSE_GRID_UNDO`        |`MG_UNDO`|Undo last quadrant pick                         |
|`QK_MOUSE_GRID_NEAR`        |`MG_NEAR`|Zoom cursor to local/nearby quadrant navigation |

