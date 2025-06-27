# Lumino

<table>
<tr><td><b>Module</b></td><td><tt>getreuer/lumino</tt></td></tr>
<tr><td><b>Version</b></td><td>2025-04-17</td></tr>
<tr><td><b>Maintainer</b></td><td>Pascal Getreuer (@getreuer)</td></tr>
<tr><td><b>License</b></td><td><a href="../LICENSE.txt">Apache 2.0</a></td></tr>
<tr><td><b>Documentation</b></td><td>
<a href="https://getreuer.info/posts/keyboards/lumino">https://getreuer.info/posts/keyboards/lumino</a>
</td></tr>
</table>

Lumino is a community module for a minimal, opinionated control scheme for RGB
matrix lighting. This scheme is born from my personal use, but perhaps this
appeals to you too. Functionally, I want some backlighting to help find the keys
at a dim or strong level depending on my environment. Aesthetically, I want
lighting that looks good without being distracting.

What Lumino does:

* Pressing the <kbd>LUMINO</kbd> key cycles the lighting brightness between 3
  states: off, 40%, and 100%. The set brightness is saved persistently to
  EEPROM.

* Lighting turns off when idle. The normal timeout is 2&nbsp;minutes of
  inactivity. However, if the keyboard had few key strokes since it last awoke,
  it turns off after 5&nbsp;seconds.

* Brightness changes are smoothly animated to minimize distraction.

* When `QK_BOOT` is pressed, lighting is set to red color.

Brightnesses and details above are configurable.


## Use

Add the following to your `keymap.json`:

```json
{
    "modules": ["getreuer/lumino"]
}
```

Then use the "`LUMINO`" keycode somewhere in your layout.

Optionally, Lumino may be used in combination with
[PaletteFx](../palettefx/README.md) for custom palette-based lighting effects:

```json
{
  "modules": ["getreuer/lumino", "getreuer/palettefx"]
}
```

## Configuration

Lumino is configurable with the following options. Values below correspond to
the default settings:

```c
// Lumino cycles among off, LUMINO_LOW_BRIGHTNESS, and LUMINO_HIGH_BRIGHTNESS.
// The latter two are values between 0.0 (off) and 1.0 (max).
#define LUMINO_HIGH_BRIGHTNESS  1.0  // = max.
#define LUMINO_LOW_BRIGHTNESS   (0.4 * (LUMINO_HIGH_BRIGHTNESS))  // = 40%.
// By default, the set brightness is saved to EEPROM. Uncomment the next line
// to tell Lumino to never write to EEPROM.
// #define LUMINO_NO_EEPROM

// Normal idle timeout in milliseconds after which the lighting turns off. 
#define LUMINO_LONG_TIMEOUT     120000  // = 2 minutes.
// Fast idle timeout, used when few keystrokes were received since the last 
// time the keyboard woke up.
#define LUMINO_SOON_TIMEOUT     5000    // = 5 seconds.
// Animated transition time for smoothly changing brightness levels.
#define LUMINO_TRANSITION       500     // = 500 ms.

// Lighting color set when `QK_BOOT` is pressed.
#define LUMINO_BOOT_COLOR       RGB_RED
```

See the [Lumino
documentation](https://getreuer.info/posts/keyboards/lumino) for further
configuration options and details.

