
# Ploopy Trackball Mini

![Ploopyco Trackball Mini](mini.jpg)

It's a DIY, QMK Powered Trackball...Mini!

* Maintainer: [PloopyCo](https://github.com/ploopyco)
* Key contributors: [Drashna Jael're](https://github.com/drashna/), [Germ](https://github.com/germ/)
* Hardware Supported: ATMega32u4 16MHz(5v)  
* Hardware Availability: [Store](https://ploopy.co), [GitHub](https://github.com/ploopyco)

Make example for this trackball (after setting up your build environment):

    make ploopyco/trackball_mini/rev1_002:default:flash
    make ploopyco/trackball_mini/rev1_002:via:flash
    
To jump to the bootloader, hold down "Button 4" (immediate right of the ball) 

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Hardware Reset Button

The Ploopy Mini has a handy bootloader reset mechanism: two via pins on the board, designated by the reference designator `MCU.J.X BOOTLOADER`. If you stick an uninsulated paperclip or a pair of metal tweezers into both holes and plug in the Mini, it will start in bootloader mode.

## Revisions

Occasionally, new revisions of the PCB will be released. Every board comes with a designator that looks something like `R1.001`.

Match the firmware that you flash onto the board with the designator on the board.

# Customzing your Ploopy Mini Trackball

While the defaults are designed so that it can be plugged in and used right away, there are a number of things that you may want to change, such as adding DPI control, or using the ball to scroll while holding a button. To allow for this sort of control, there is a callback for both the scroll wheel and the mouse sensor.

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

Additionally, you can change the DPI/CPI or speed of the trackball by calling `adns_set_cpi` at any time. Additionally, there is a `DPI_CONFIG` macro that will cycle through an array of options for the DPI.  This is set to 375, 750, and 1375, but can be changed. 1375 is the default. 

To configure/set your own array, there are two defines to use, `PLOOPY_DPI_OPTIONS` to set the array, and `PLOOPY_DPI_DEFAULT`. 

```c
#define PLOOPY_DPI_OPTIONS { 375, 750, 1375}
#define PLOOPY_DPI_DEFAULT 2
```

The `PLOOPY_DPI_OPTIONS` array sets the values that you want to be able to cycle through, and the order they are in.  The "default" define lets the firmware know which of these options is the default and should be loaded by default.

The `DPI_CONFIG` macro will cycle through the values in the array, each time you hit it.  It stores this value in persistent memory, so it will load it the next time the device powers up.

## Drag Scroll

Drag Sroll is a custom keycode for the Ploopy devices that allow you to hold or tap a button and have the mouse movement translate into scrolling instead. 

Nothing needs to be enabled to use this functionality.  Just add the `DRAG_SCROLL` to your keymap. 

### Drag Scroll Configuration

* `#define PLOOPY_DRAGSCROLL_MOMENTARY` - Makes the key into a momentary key, rather than a toggle.
* `#define PLOOPY_DRAGSCROLL_DPI 375` - When the fixed DPI option is enabled, this sets the DPI to be used for Drag Scroll.
* `#define PLOOPY_DRAGSCROLL_INVERT` - This reverses the direction that the scroll is performed. 
## Fuse settings

When flashing the bootloader, use the following fuse settings:

| Fuse     | Setting     |
|----------|-------------|
| Low      | `0x5E`      |
| High     | `0x99`      |
| Extended | `0xC3`      |
