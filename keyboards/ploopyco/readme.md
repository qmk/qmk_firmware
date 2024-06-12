# Ploopyco

* [Mouse](mouse/)
* [Trackball](trackball/)
* [Trackball Mini](trackball_mini/)
* [Trackball Nano](trackball_nano/)
* [Trackball Thumb](trackball_thumb/)
* [Adept/Madromys](manromys/)

# Customizing your PloopyCo Device

There are a number of behavioral settings that you can use to help customize your experience
|                                 |                   |                                                           |
|---------------------------------|-------------------|-----------------------------------------------------------|
| `PLOOPY_IGNORE_SCROLL_CLICK`    | *__not_defined__* | Ignores scroll wheel if it is pressed down.               |
| `PLOOPY_SCROLL_DEBOUNCE`        | `5`               | Number of milliseconds between scroll events.             |
| `PLOOPY_SCROLL_BUTTON_DEBOUNCE` | `100`             | Time to ignore scroll events after pressing scroll wheel. |

## DPI

You can change the DPI/CPI or speed of the trackball by calling `pointing_device_set_cpi` at any time. Additionally, there is a `DPI_CONFIG` macro that will cycle through an array of options for the DPI.  This is set to 1200, 1600, and 2400, but can be changed.  1600 is also set to the default.

To configure/set your own array, there are two defines to use, `PLOOPY_DPI_OPTIONS` to set the array, and `PLOOPY_DPI_DEFAULT`.

```c
#define PLOOPY_DPI_OPTIONS { 1200, 1600, 2400 }
#define PLOOPY_DPI_DEFAULT 1
```

The `PLOOPY_DPI_OPTIONS` array sets the values that you want to be able to cycle through, and the order they are in.  The "default" define lets the firmware know which of these options is the default and should be loaded by default.

The `DPI_CONFIG` macro will cycle through the values in the array, each time you hit it.  And it stores this value in persistent memory, so it will load it the next time the device powers up.

## Drag Scroll

Drag Sroll is a custom keycode for the Ploopy devices that allow you to hold or tap a button and have the mouse movement translate into scrolling instead.

Nothing needs to be enabled to use this functionality.  Just add the `DRAG_SCROLL` to your keymap.

### Drag Scroll Configuration

* `#define PLOOPY_DRAGSCROLL_MOMENTARY` - Makes the key into a momentary key, rather than a toggle.
* `#define PLOOPY_DRAGSCROLL_DIVISOR_H 8.0` - Sets the horizontal movement divisor to use when drag scroll is enabled.
* `#define PLOOPY_DRAGSCROLL_DIVISOR_V 8.0` - Sets the vertical movement divisor to use when drag scroll is enabled.
* `#define PLOOPY_DRAGSCROLL_INVERT` - This reverses the direction that the scroll is performed.
