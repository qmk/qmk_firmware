# Glorious GMMK Pro / ANSI - Enhanced Keyboard

Tried to incorporate full featured GMMK Pro keyboard functionality without adding unnecessary features. Included Scroll Lock and Caps LEDs. NKRO can be toggled (Fn + N).
SHIFT and Ctrl keys for scrolling with the rotary, Fn-keys also used for screen brightness, media, PowerOff, Suspend, App Shortcuts, and RGB Toggle/Modifications. Trimmed down the amazing (currently 41) built-in RGB effects down to about 13 or so reasonable effects that feel are just enough for your entertainment without being too excessive.

BIG thank you to [AndreBrait](https://github.com/andrebrait), And of course, @drashna and @filterpaper, @noroadsleft and the entire discord community.

* Keymap Creator: [StickAndGum](https://github.com/StickAndGum)
* Keyboard: [More info on GMMK Pro](https://www.pcgamingrace.com/products/glorious-gmmk-pro-75-barebone-black)
* Controller [STM32F303CCT6](https://www.st.com/en/microcontrollers-microprocessors/stm32f303.html)

* Layout:  
  ![keyboard-layout](https://user-images.githubusercontent.com/22257588/130371838-875ba65b-88ea-4f81-a44a-bb24194c4989.png)

Features are as follows:

Rotary:
  - Default:  Volume Up/Down
  - Shift:    Mouse Wheel Down/Up
  - Ctrl:     Page Down/Up

Top/Default Layer:
  - Print Screen -> Print Screen (Left of rotary)
  - Delete -> Home (Under Rotary)
  - Right Alt -> Delete (Right of Spacebar)
  - All other keys defaults.

Fn Layer:
  - Fn + \ -> Bootloader Mode (Can also hold ESC while powering up) - If hit by mistake, just unplug and replug in.
  - Fn + Backspace -> Insert
  - Fn + Print  -> Pause/Break
  - Fn + Home -> Scroll Lock (Lights up white!)
  - Fn + Del (right of space) -> Right-Alt key.
  - Fn + RCtrl (right of Fn) -> Menu/App key.
  - Fn + N -> Toggle NKRO
  - Fn + End -> Power Off Computer
  - Fn + F12 -> Suspend Computer
  - Fn + F11 -> Wake Computer (Necessary on MAC OS?)
  - Fn + Page Up / Down -> Laptop Screen Brightness Up/Down
  - Fn + F1 - F5 -> Launch Calc, My Comp (Explorer), Media Player, Mail Client, Web Browser.
  - Fn + Up, Down, Left, Right Arrows -> Media Play, Stop, Previous, Next respectively.

- RGB Information:
  - Toggle for RGB via Fn-r (CAPS & ScrlLock still Light/Indicate)
  - CAPS: Side Light Rainbow Indicators and Left-side RED Indicators
  - Scroll-Lock: Fn-Home (Under Rotary) white indicator.
  - Modifiers identified around most of the edge of keyboard / Side lights also accented (Fn-1 looks GREAT IMHO)
  
- RGB Modifing (all via Function key) all via wasdqerf (common gaming keys) - easy to remember.
  - Fn + r -> Toggle RGB
  - Fn + w,s -> Brightness Up, Down
  - Fn + a,d -> Cycle Forward/Backward through rgb effects
  - Fn + q   -> Increase or Decrease Saturation (use SHIFT key to lower)
  - Fn + e   -> Increase or Decrease Hue/Color (use SHIFT key to lower)
  - Fn + f   -> Increase or Decrease Speed (Using "F" for Fast!) (Use SHIFT for slower)
  - Fn + ~, 0-9, - = keys (2nd row keys) -> 13 RGB different effects arranged to my liking. Fn-1 is my favorite.
  - Fn + L -> My easter egg... "QMK rocks!"
  
- Known issues:
  - The Heatmap and Matrix FrameBuffer effects (Fn - and =) are a bit buggy - F-keys light up when they shouldn't and the Caps/Scroll lights don't turn off properly when using. Just change the effect to something else to fix this. 
    - If you find a fix for this, please let me know.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
