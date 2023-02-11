# Ploopyco Mouse

![Ploopyco Mouse](https://ploopy.co/wp-content/uploads/2021/06/g1.jpeg)

It's a DIY, QMK Powered Mouse!!!!


* Keyboard Maintainer: [PloopyCo](https://github.com/ploopyco), [Drashna Jael're](https://github.com/drashna/), [Germ](https://github.com/germ/)
* Hardware Supported: ATMega32u4 8MHz(3.3v)  
* Hardware Availability: [Store](https://ploopy.co), [GitHub](https://github.com/ploopyco)

Make example for this keyboard (after setting up your build environment):

    make ploopyco/mouse:default:flash
    
To jump to the bootloader, hold down "Button 4" (the "forward" button on the left side) 

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

# Customizing your PloopyCo Mouse

While the defaults are designed so that it can be plugged in and used right away, there are a number of things that you may want to change.  Such as adding DPI control, or to use the ball to scroll while holding a button.   To allow for this sort of control, there is a callback for both the scroll wheel and the mouse sensor. 

The default behavior for this is:

```c
void process_wheel_user(report_mouse_t* mouse_report, int16_t h, int16_t v) {
    mouse_report->h = h;
    mouse_report->v = v;
}

void process_mouse_user(report_mouse_t* mouse_report, int16_t x, int16_t y) {
    mouse_report->x = x;
    mouse_report->y = y;
}
```

This should allow you to more heavily customize the behavior. 

Alternatively, the `process_wheel` and `process_mouse` functions can both be replaced too, to allow for even more functionality.

Additionally, you can change the DPI/CPI or speed of the trackball by calling `pointing_device_set_cpi` at any time. Additionally, there is a `DPI_CONFIG` macro that will cycle through an array of options for the DPI.  This is set to 1200, 1600, and 2400, but can be changed.  1600 is also set to the default.

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
* `#define PLOOPY_DRAGSCROLL_MULTIPLIER 0.75` - Sets the DPI multiplier to use when drag scroll is enabled. 
* `#define PLOOPY_DRAGSCROLL_FIXED` - Normally, when activating Drag Scroll, it uses a fraction of the current DPI. You can define this to use a specific, set DPI rather than a fraction of the current DPI. 
  * `#define PLOOPY_DRAGSCROLL_DPI 100` - When the fixed DPI option is enabled, this sets the DPI to be used for Drag Scroll.
* `#define PLOOPY_DRAGSCROLL_INVERT` - This reverses the direction that the scroll is performed. 
