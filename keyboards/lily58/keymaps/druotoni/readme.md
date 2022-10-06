# HELL0 NAVI. Interface

HELL0 NAVI. Interface is a GUI based en [Serial Experiments Lain](https://en.wikipedia.org/wiki/Serial_Experiments_Lain). Turn your [Lily58](https://github.com/kata0510/Lily58) keyboard into a Navi computer with its own Copland OS.


Ready to dive into the Wired ?


HELL0 NAVI provides interactive animations for both sides :
- a scope on left side for burst, WPM and active layer
- a ring on right side for the last key stroke







## Typing animation

The scope displays your burst time on a chart. The WPM is represented by an horizontal line.

The ring display the last letter in the upper frame. Each time you enter a key, the Navi searches into the circular database and locks the position. A special animation is displayed when Enter, Backspce or Escape are struck.

<img src="https://imgur.com/Yf7D6UN.gif" height="400" >

## Startup animation

Your Navi boots when it leaves the sleep mode. The animation can be canceled by typing.



<img src="https://imgur.com/EXU92Ev.gif" height="400" >



## Waking up animation

After a period of inactivity, the scope and the ring turn off and the Navi runs in Idle mode. A new key stroke wakes them up.


<img src="https://imgur.com/9GWa7rR.gif" height="400" >


## Idle animation

The Copland OS is still in beta test. After a while, some visual glitches will occur. 


<img src="https://imgur.com/eKZ7qgC.gif" height="400" >



## Shutdown animation
The Navi runs in sleep mode after 10 seconds in Idle mode. A nice (and difficul to render in a gif) animation is run. The OLED display turns off. 

# How to build & flash

You need to flash each side with a specific version based on config.h configuration.

 ## Left side (master)

IS_RIGHT needs to be commented in config.h
```
#define IS_LEFT 1
//#define IS_RIGHT 1
```
Connect the left side and flash

 ## Right side (slave)

Comment IS_LEFT and uncomment IS_RIGHT  in config.h
```
//#define IS_LEFT 1
#define IS_RIGHT 1
```
Connect the right side and flash

# Customization

## Logo
Logo can be change in navi_logo.c.
The new logo must be 32x32 pixels.
```
static void render_logo_clean(void) {
    // your logo here
    static const char PROGMEM logo_raw[] = {
        0, 0, 0, 0, 0, 0, 128, 128, 0, 0, 128, 128, 192, 192, 204, 222, 222, 204, 192, 192, 128, 0, 0, 0, 128, 128, 0, 0,
        0, 0, 0, 0, 192, 240, 248, 28, 14, 7, 3, 249, 252, 255, 15, 7, 3, 225, 241, 241, 241, 241, 225, 3, 7, 15, 255, 252,
        249, 3, 7, 14, 28, 248, 240, 192, 192, 227, 231, 206, 28, 56, 112, 99, 15, 31, 60, 120, 240, 225, 227, 3, 3, 227,
        225, 240, 120, 60, 31, 15, 103, 112, 56, 28, 206, 231, 227, 192, 0, 1, 1, 0, 0, 0, 56, 120, 96, 192, 192, 192, 
        96, 127, 63, 0, 0, 63, 127, 96, 192, 192, 192, 96, 120, 56, 0, 0, 0, 1, 1, 0,
    };
    oled_write_raw_P(logo_raw, sizeof(logo_raw));
}
```
## Layer names

The current version handle 3 differents layers. Names can be changed in layer_frame.h.
```
// layer name : must be 3 chars
#define LAYER_NAME_0 "ABC"
#define LAYER_NAME_1 "NAV"
#define LAYER_NAME_2 "SPE"
```

## Timing

You can tweak states timing in gui_state.h.
```
// states timing
#define BOOTING_TIME_TRESHOLD 7000
#define WAKING_UP_TIME_TRESHOLD 300
#define IDLE_TIME_TRESHOLD 4000
#define HALTING_TIME_TRESHOLD IDLE_TIME_TRESHOLD + 6000
#define SLEEP_TIME_TRESHOLD HALTING_TIME_TRESHOLD + 8000
```

## Need space ?
Boot and gliches can be commented in config.h
```
// states timing
// logo glitch
//#define WITH_GLITCH
// boot sequence
//#define WITH_BOOT
```

![My Navi](https://imgur.com/eYkgoZJ.png)
> Keyboard : https://github.com/kata0510/Lily58
> 
> Case : https://github.com/BoardSodie/Lily58-Acrylic-Case

