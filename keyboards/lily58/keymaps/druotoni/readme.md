# HELL0 NAVI. Interface

HELL0 NAVI. Interface is a GUI based en [Serial Experiments Lain](https://en.wikipedia.org/wiki/Serial_Experiments_Lain). Turn your Lily58 keyboard into a Navi computer with it own Copland OS.


Ready to dive into the Wired ?


HELL0 NAVI provides interactive animations for both sides :
- a scope on left side for burst, WPM and active layer
- a ring on right side for the last key stroke







## Typing animation

The scope displays your burst time on a chart. The WPM is represented by an horizontal line.

The ring display the last letter in the upper frame. Each time you enter a key, the Navi searches into the circular database and locks the position. A special animation is displayed whem you hit key like Enter, Backspce or Escape.

![Typing animation](https://imgur.com/iIG1tQE.gif)

## Startup animation

Your Navi boots when you leave the sleep mode. The animation is canceled when you hit a key.

![Startup animation](https://i.imgur.com/EXU92Ev.gif)


## Waking up animation

After a period of inactivity, the scope and the ring turn off and the Navi runs Idle mode. A new key stroke wakes them up.

![Waking up animation](https://imgur.com/9GWa7rR.gif)

## Idle animation

The Copland OS is still in beta test. After a while, some visual glitches could occur. 

![Idle animation](https://imgur.com/eKZ7qgC.gif)


## Shutdown animation
The Navi run sleep mode after 10 seconds in Idle mode. A nice (and to difficult for me to render in a gif) animation is run. The OLED display turns off. 

## How to build & flash

You need to flash each side with a specific version. This information is set in the config.h

 ### Left side (master)

IS_RIGHT needs to be commented in config.h
```
#define IS_LEFT 1
//#define IS_RIGHT 1
```
Connect the left side and flash

 ### Right side (slave)

Comment IS_LEFT and uncomment IS_RIGHT  in config.h
```
//#define IS_LEFT 1
#define IS_RIGHT 1
```
Connect the right side and flash

## Customization

### Logo

### Layer names

The current version handle 3 differents layers. Names can be changed in layer_frame.h.
```
// layer name : must be 3 chars
#define LAYER_NAME_0 "ABC"
#define LAYER_NAME_1 "NAV"
#define LAYER_NAME_2 "SPE"
```

### Timing

You can tweak states timing in gui_state.h.
```
// states timing
#define BOOTING_TIME_TRESHOLD 6000
#define WAKING_UP_TIME_TRESHOLD 300
#define IDLE_TIME_TRESHOLD 4000
#define HALTING_TIME_TRESHOLD IDLE_TIME_TRESHOLD + 6000
#define SLEEP_TIME_TRESHOLD HALTING_TIME_TRESHOLD + 8000
```

