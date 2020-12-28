# Velocikey

Velocikey is a feature that lets you control the speed of lighting effects (like the Rainbow Swirl effect) with the speed of your typing. The faster you type, the faster the lights will go!

## Usage

For Velocikey to take effect, there are two steps. First, when compiling your keyboard, you'll need to set `VELOCIKEY_ENABLE=yes` in `rules.mk`, e.g.:

```
BOOTMAGIC_ENABLE = no
MOUSEKEY_ENABLE = no
STENO_ENABLE = no
EXTRAKEY_ENABLE = yes
VELOCIKEY_ENABLE = yes
```

Then, while using your keyboard, you need to also turn it on with the VLK_TOG keycode, which toggles the feature on and off.

The following light effects will all be controlled by Velocikey when it is enabled:

-   RGB Breathing
-   RGB Rainbow Mood
-   RGB Rainbow Swirl
-   RGB Snake
-   RGB Knight

Support for LED breathing effects is planned but not available yet.

As long as Velocikey is enabled, it will control the speed regardless of any other speed setting that your RGB lights are currently on.

## Configuration

In your `config.h`, you can define the following configuration options:

| Macro name                     | Default value                        |
| ------------------------------ | ------------------------------------ |
| `VELOCIKEY_MAX_TYPING_SPEED`   | 200                                  |
| `VELOCIKEY_ACCEL_RATE`         | VELOCIKEY_MAX_TYPING_SPEED / 100     |
| `VELOCIKEY_DECAY_RATE_1`       | 1                                    |
| `VELOCIKEY_DECAY_RATE_2`       | 1                                    |
| `VELOCIKEY_DECAY_RATE_3`       | 1                                    |
| `VELOCIKEY_DECAY_RATE_2_LIMIT` | `VELOCIKEY_MAX_TYPING_SPEED / 2`     |
| `VELOCIKEY_DECAY_RATE_3_LIMIT` | `VELOCIKEY_MAX_TYPING_SPEED / 4 * 3` |

Additionally, the minimum and maximum timings can be controlled on a per-animation
basis:

| Macro name                             | Default value |
| -------------------------------------- | ------------- |
| `VELOCIKEY_MAX_INTERVAL_BREATHING`     | 100           |
| `VELOCIKEY_MIN_INTERVAL_BREATHING`     | 1             |
| `VELOCIKEY_MAX_INTERVAL_RAINBOW_MOOD`  | 100           |
| `VELOCIKEY_MIN_INTERVAL_RAINBOW_MOOD`  | 5             |
| `VELOCIKEY_MAX_INTERVAL_RAINBOX_SWIRL` | 100           |
| `VELOCIKEY_MIN_INTERVAL_RAINBOX_SWIRL` | 1             |
| `VELOCIKEY_MAX_INTERVAL_SNAKE`         | 200           |
| `VELOCIKEY_MIN_INTERVAL_SNAKE`         | 1             |
| `VELOCIKEY_MAX_INTERVAL_KNIGHT`        | 100           |
| `VELOCIKEY_MIN_INTERVAL_KNIGHT`        | 5             |
