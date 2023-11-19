# Ocean Dream

Tapping away at your IMX Corne with Box Jades, you feel yourself
drifting off, into a soundscape of waves and rustling leaves.
You open your eyes only to find yourself in an _Ocean Dream_.

Introducing, **Ocean Dream**, an animation for keyboards with tall OLED 
screens. Built for 128x32 screens, this animation should work for 128x64
at least, though it hasn't been tested there. 

Completely customizable, you can change everything about the animation, 
from the number of falling stars, to how likely a star is to twinkle, and 
even if the moon has phases or not.

# Installation

Installation is easy.

1. Add `ocean.h` and `ocean.c` to your keyboard folder or userspace.
2. In your `keymap.c` or wherever you handle your oled code, add
```c
#    ifdef OCEAN_DREAM_ENABLE
        render_stars();
#    endif
```
to `oled_task_user(void)`, where you would like (see [my keymap](../../keyboards/crkbd/keymaps/snowe/keymap.c) for an example)
3. In your `keymap.c` or wherever you handle your process_record code, 
   add an event that sets `is_calm` when you press `ctrl`
```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LCTL:
        case KC_RCTL:
#ifdef OCEAN_DREAM_ENABLE
            is_calm = (record->event.pressed) ? true : false;
#endif
            break;
    }
    return true;
}
```
4. In your `rules.mk` to make it easier to turn the animation on/off, add
```makefile
ifeq ($(strip $(OLED_ENABLE)), yes)
    #... your code here...

    ifdef OCEAN_DREAM_ENABLE
        ifeq ($(strip $(OCEAN_DREAM_ENABLE)), yes)
            SRC += ocean_dream.c
            OPT_DEFS += -DOCEAN_DREAM_ENABLE
        endif
    endif
    ifndef OCEAN_DREAM_ENABLE
        SRC += ocean_dream.c
        OPT_DEFS += -DOCEAN_DREAM_ENABLE
    endif
endif
```

You're done! Now you can enable **Ocean Dream** by simply turning on the OLED feature
```makefile
OLED_ENABLE = yes
```

And if you want to disable it without turning off the OLED Driver you can simply set 
```makefile
OCEAN_DREAM_ENABLE = no
```

# Settings

**Ocean Dream** comes with several different animations, all individually configurable:

* 🌌 Stars that twinkle
* 🌠 Meteor showers that get more vibrant the faster you type
* 🌊 Waves that get rougher the faster you type
* 🏝 An island with a palm tree that blows in the wind the faster you type
* 🌗 A moon that goes through the moon phases (or not, your choice!)

Each feature can be individually turned on and off, with a simple `#define`. 

You can see all the options and more documentation by looking at `ocean_dream.h`.

All options come enabled by default.

## Global Flags:

### Toggles:

You can toggle on/off any features using these flags:

* `ENABLE_MOON`            // Uses 182 bytes
* `ENABLE_WAVE`            // Uses 844 bytes
* `ENABLE_SHOOTING_STARS`  // Uses 872 bytes
* `ENABLE_ISLAND`
* `ENABLE_STARS`  // Uses 606 bytes

### Global Configuration:

* `STARRY_NIGHT_ANIM_FRAME_DURATION` - configures how long each frame lasts in ms
* `NUMBER_OF_FRAMES` - configures the number of frames that constitute a single 'round trip' of animation. 
  Enables keeping animations in sync/timed with each other. 
  Probably shouldn't touch this, not sure how stuff will work if it's changed. 
  If changed should probably be multiple of 1, 2, 3, 4, and 5
* `WIDTH` - for vertical displays, configures the width (the shortest measurement of your display). defaults to `OLED_DISPLAY_HEIGHT` 
* `HEIGHT` - for vertical displays, configures the height (the longest measurement of your display). defaults to `OLED_DISPLAY_WIDTH`

## Stars

### Description

The 🌌 stars animation is a background of slowly twinkling stars. 
The stars are built on a grid of sorts, where each cell of the grid
is 8x8 pixels with 1 star per cell. There is a probability of any 
star twinkling on any given frame, decided by the corresponding flags.

### Flags

Enabled with the `#define ENABLE_STARS` directive.

The stars come with several configuration options:

* `STARS_PER_LINE` - configures the number of stars per line. Defaulting to 4, this would
  mean that you have 4 stars across each line (8x32 on a 128x32 display), where each star 
  is in a 8x8 grid
* `NUMBER_OF_STAR_LINES` - configures the number of lines to fill up with stars. 
  Defaults to 16, filling the whole display.
* `TWINKLE_PROBABILITY` - configures the probability of a star twinkling on a given frame.
* `STAR_ANIMATION_SPEED` - configures the number of frames you want to animate the star at. 
  Must be equal to or lower than `NUMBER_OF_FRAMES`. 
  Example: 
  ```c
    #define NUMBER_OF_FRAMES 20
    #define STAR_ANIMATION_SPEED 5
  ```
  would result in the star animation happening every 4 frames. 20 would result in every frame, 
  1 would be once every 20 frames. This essentially changes how fast stars will twinkle, but 
  does not change the probability of the stars twinkling. 

## Moon

### Description

The 🌗 moon animation is an 8x8 animation of a moon, or, if you are running out of program memory, you 
can set it to just a static crescent moon, with no animation. 

### Flags

Enabled with the `#define ENABLE_MOON` directive.

The moon comes with only a few configuration options:

* `STATIC_MOON` - include this directive if you want your moon to have no animation. It will simply be a static crescent 
  moon, only taking up 6 bytes of space. If you do not include this directive, then the moon will have an animation. 
  The default is a moon with animation.
* `MOON_LINE` - defines the line that the moon sits on. Default is `4`. (see [reference](#reference))
* `MOON_COLUMN` - defines the column that the moon sits at. Default is `4`. (see [reference](#reference))
* `ANIMATE_MOON_EVERY_N_FRAMES` - only enabled when `STATIC_MOON` is disabled, this affects how often the moon changes phases. 
  Example: 
  ```c
  #define STARRY_NIGHT_ANIM_FRAME_DURATION 30
  #ifndef STATIC_MOON
  #    define ANIMATE_MOON_EVERY_N_FRAMES 100  
  #endif
  ```
  would result in the moon changing phases every 3000ms, or every 3 seconds.

## Ocean

### Description

The 🌊 ocean animation is a full width animation of ocean waves, where the waves get rougher the faster you type. 
You can configure the boundaries for each degree of _wave ferocity_ as well as how fast the ocean/waves move.

### Flags

* `OCEAN_LINE` - where to render the ocean at. Defaults to `14`. (see [reference](#reference))
* `OCEAN_ANIMATION_SPEED` - configures the number of frames you want to animate the ocean at.
  Must be equal to or lower than `NUMBER_OF_FRAMES`.
  Example:
  ```c
    #define NUMBER_OF_FRAMES 20
    #define OCEAN_ANIMATION_SPEED 5
  ```
  would result in the ocean animation happening every 4 frames. 20 would result in every frame,
  1 would be once every 20 frames. This essentially changes how fast the waves will move.
* `WAVE_CALM` - Defines the WPM at which the _Wave Ferocity_ kicks up. 
  At any WPM between `WAVE_CALM` and `WAVE_HEAVY_STORM`, the waves will be just tiny ripples.
* `WAVE_HEAVY_STORM` - Defines the WPM at which the _Wave Ferocity_ kicks up to medium. 
  At any WPM between `WAVE_HEAVY_STORM` and `WAVE_HURRICANE`, the waves will be medium sized waves.
* `WAVE_HURRICANE` - Defines the WPM at which the _Wave Ferocity_ kicks up to the last notch. 
  At any WPM above `WAVE_HURRICANE`, the waves will be torrential.

## Shooting Stars

The 🌠 shooting star animation is a full screen animation that renders a meteor shower based on your typing speed. The
faster you type, the more shooting stars there are!

You can configure many parts of the shooting stars, from shower size, to speed, to length of each trail, to how spaced 
out they are.

Note: Each frame of a shooting star is only 2 pixels in length. This is a design decision, and could probably be changed 
with a decent amount of work, but was chosen for looks and memory constraints. 

### Flags

* `SHOOTING_STAR_DELAY` - Decides number of frames to delay, based on modulus, e.g. 12 means 0-11 frames of delay between each shooting star
* `SHOOTING_STAR_FRAMES` - how long each shooting star will be. A size of `16` will result in shooting stars that are 32 pixels long 
* `MAX_NUMBER_OF_SHOOTING_STARS` - maximum number of shooting stars that can be on screen at the same time
* `SHOOTING_STAR_WPM_INCREMENT` - every n WPM increase, add an extra star, up to MAX_NUMBER_OF_SHOOTING_STARS
  Example: an increment of 5 would result in 1 shooting star at 5-9wpm, 2 at 10-14, etc.
* `SHOOTING_STAR_ANIMATION_SPEED` - configures the number of frames you want to animate the shooting stars at.
  Must be equal to or lower than `NUMBER_OF_FRAMES`.
  Example:
  ```c
    #define NUMBER_OF_FRAMES 20
    #define SHOOTING_STAR_ANIMATION_SPEED 5
  ```
  would result in the shooting star animation happening every 4 frames. 20 would result in every frame,
  1 would be once every 20 frames. This essentially changes how fast the stars move through the sky.


## Island

The 🏝 island animation is a 32w x 16h animation of a small island with a single palm tree blowing in the wind. The faster
you type the harder the palm tree blows in the wind!

Since this animation has significant black space to the left side of the tree, certain design decisions were made to allow the 
shooting stars to still show up in the sky there. This animation should work on any size screen >=32 pixels wide, and you 
can place it anywhere on the screen, but above the ocean is recommended. 

### Flags

* `ISLAND_LINE` - where to render the island at. Defaults to `12`. The island is 2 lines tall. (see [reference](#reference))
* `ISLAND_COLUMN` - where to render the island at. Defaults to `0`. The island is 32 pixels wide. (see [reference](#reference))
* `ISLAND_CALM` - Defines the WPM at which the _Storm Ferocity_ kicks up.
  At any WPM between `ISLAND_CALM` and `ISLAND_HEAVY_STORM`, the palm tree will just calmly blow in the wind.
* `ISLAND_HEAVY_STORM` - Defines the WPM at which the _Storm Ferocity_ kicks up.
  At any WPM between `ISLAND_HEAVY_STORM` and `ISLAND_HURRICANE`, the palm tree will be blowing hard in the wind
* `ISLAND_HURRICANE` - Defines the WPM at which the _Storm Ferocity_ kicks up.
  At any WPM above `ISLAND_HURRICANE`, the palm tree will almost be torn from its roots!


# Reference

Any reference to `_LINE` or `COLUMN` refers to setting a cursor position using `oled_set_cursor()`, which uses 
`OLED_FONT_WIDTH` and `OLED_FONT_HEIGHT` internally.  
This will be the top-leftmost pixel of the image, so `_LINE 1` would start at the 9th pixel down and `_COLUMN 1` 
would be the 7th pixel to the right, starting from the topleftmost pixel on the screen.

This code has been untested with different font heights/widths, so you might have to adjust a bit to make it work if you 
have modified those values.

# ToDo

- [ ] don't require `is_calm` as a keyboard event. Not sure if the code will work without it currently.
- [ ] make all the stars twinkle brightly based on keypresses rather than timed. Not just a movement twinkle, but a larger
     'full' twinkle, where the star actually gets bigger. This will be quite difficult, thus is left out of the v1.
