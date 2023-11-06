# brandonschlack's TKL ANSI layout

A mostly typical Mac setup, with some personal QMK touches.

## Base Layer

The base layer has a standard macOS modifier layout, with **F13-F15** in the F row, in place of **Print Screen**, **Scroll Lock**, and **Pause/Break**.

### [Mod-Taps](https://docs.qmk.fm/#/feature_advanced_keycodes?id=mod-tap)

* Hyper Caps Lock
  * Hold **Caps Lock** for '**Hyper**' (**Shift**+**Control**+**Option**+**Command**). I use it for mapping global shortcuts for apps.
  * Tapping **Caps Lock** functions normally
* Media controls mapped to Right Modifiers
  * **Right Command** for **Prev Track**
  * **Right Option** for **Next Track**
  * **Fn** for **Play/Pause**

## Function Layer

The Function layer is a mix of [Apple's *Fn* shortcuts](https://support.apple.com/en-us/HT201236), [WASD Keyboard's Media shortcuts](https://codekeyboards.com/#multimedia), and some QMK functionality.

### [Apple's *Fn* shortcuts](https://support.apple.com/en-us/HT201236)

* **Home/Page Down/Page Up/End** as **Fn+Left/Down/Up/Right**
* **Foward Delete** as **Fn+Backspace**
* **Display Brightness Down/Up** as **Fn+F1/F2**
* **Misson Control** (*KC_FIND, but use [Karabiner-Elements](https://pqrs.org/osx/karabiner/index.html) as find -> mission_control*) as **Fn+F3**
* **Launchpad** (*KC_MENU, but use [Karabiner-Elements](https://pqrs.org/osx/karabiner/index.html) as menu -> launchpad*) as **Fn+F4**
* Keyboard Illumination Down/Up used as **RGB Underglow Value Decrease/Increase** on **Fn+F5/F6**

### [WASD Keyboard's Media shortcuts](https://codekeyboards.com/#multimedia)

* **Play/Pause** as **Fn+Insert**
* **Prev/Next Track** as **Fn+Delete/End**
* **Volume Up/Down** as **Fn+Page Up/Page Down**
* **Volume Mute** as **Fn+F15**

### Personal & QMK shortcuts

* **Sleep Display** (Shift+Control+Power) as **Fn+Home**.
* **QMK Make** as **Fn+Esc**. Sends make command to command line. Holding **Shift** will also append `:flash` target and put keyboard into bootloader.
* **Reset** as **Fn+B**

### RGB Controls

* **RGB Toggle** as **Fn+Caps Lock**
* **RGB Hue Increase/Decrease** as **Fn+Q/A**
* **RGB Saturation Increase/Decrease** as **Fn+W/S**
* **RGB Value Increase/Decrease** as **Fn+E/D**
* **RGB Mode Next/Previous** as **Fn+Tab/Shift+Tab**
* **RGB Toggle Layer Indication** as **Fn+Z**
  * Changes RGB Color with Layer change (*uses custom RGB_THEME*).
* **RGB Cycle Next Theme** as **Fn+X**

