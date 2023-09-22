
# Ploopyco Madromys Trackball

It's a DIY, QMK-powered trackball!

* Keyboard Maintainer: [PloopyCo](https://github.com/ploopyco)
* Hardware Supported: RP2040
* Hardware Availability: [Store](https://ploopy.co), [GitHub](https://github.com/ploopyco)

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb ploopyco/madromys -km default

# Building Firmware

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

# Drag Scroll

Drag Scroll is a custom keycode for Ploopy devices that allows you to hold or tap a button and have the mouse movement translate into scrolling instead. 

Nothing needs to be enabled to use this functionality; it's enabled on Madromys by default.

### Drag Scroll Configuration

* `#define PLOOPY_DRAGSCROLL_MOMENTARY` - Makes the key into a momentary key, rather than a toggle.
* `#define PLOOPY_DRAGSCROLL_MULTIPLIER 0.75` - Sets the DPI multiplier to use when drag scroll is enabled. 
* `#define PLOOPY_DRAGSCROLL_FIXED` - Normally, when activating Drag Scroll, it uses a fraction of the current DPI. You can define this to use a specific, set DPI rather than a fraction of the current DPI. 
  * `#define PLOOPY_DRAGSCROLL_DPI 100` - When the fixed DPI option is enabled, this sets the DPI to be used for Drag Scroll.
* `#define PLOOPY_DRAGSCROLL_INVERT` - This reverses the direction that the scroll is performed. 
