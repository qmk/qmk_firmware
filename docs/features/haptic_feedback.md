# Haptic Feedback

## Haptic feedback rules.mk options

The following options are currently available for haptic feedback in `rules.mk`:

```make
HAPTIC_ENABLE = yes

HAPTIC_DRIVER = drv2605l
# or
HAPTIC_DRIVER = solenoid
```

The following `config.h` settings are available for all types of haptic feedback:

| Settings                             | Default       | Description                                                                                                   |
|--------------------------------------|---------------|---------------------------------------------------------------------------------------------------------------|
|`HAPTIC_ENABLE_PIN`                   | *Not defined* |Configures a pin to enable a boost converter for some haptic solution, often used with solenoid drivers.       |
|`HAPTIC_ENABLE_PIN_ACTIVE_LOW`        | *Not defined* |If defined then the haptic enable pin is active-low.                                                           |
|`HAPTIC_ENABLE_STATUS_LED`            | *Not defined* |Configures a pin to reflect the current enabled/disabled status of haptic feedback.                            |
|`HAPTIC_ENABLE_STATUS_LED_ACTIVE_LOW` | *Not defined* |If defined then the haptic status led will be active-low.                                                      |
|`HAPTIC_OFF_IN_LOW_POWER`             | `0`           |If set to `1`, haptic feedback is disabled before the device is configured, and while the device is suspended. |

## Known Supported Hardware

| Name               | Description                                     |
|--------------------|-------------------------------------------------|
| [LV061228B-L65-A](https://www.digikey.com/product-detail/en/jinlong-machinery-electronics-inc/LV061228B-L65-A/1670-1050-ND/7732325) | z-axis 2v LRA |
| [Mini Motor Disc](https://www.adafruit.com/product/1201)  | small 2-5v ERM |

## Haptic Keycodes

Not all keycodes below will work depending on which haptic mechanism you have chosen.

| Key                         | Aliases | Description                                           |
|-----------------------------|---------|-------------------------------------------------------|
|`QK_HAPTIC_ON`               |`HF_ON`  | Turn haptic feedback on                               |
|`QK_HAPTIC_OFF`              |`HF_OFF` | Turn haptic feedback off                              |
|`QK_HAPTIC_TOGGLE`           |`HF_TOGG`| Toggle haptic feedback on/off                         |
|`QK_HAPTIC_RESET`            |`HF_RST` | Reset haptic feedback config to default               |
|`QK_HAPTIC_FEEDBACK_TOGGLE`  |`HF_FDBK`| Toggle feedback to occur on keypress, release or both |
|`QK_HAPTIC_BUZZ_TOGGLE`      |`HF_BUZZ`| Toggle solenoid buzz on/off                           |
|`QK_HAPTIC_MODE_NEXT`        |`HF_NEXT`| Go to next DRV2605L waveform                          |
|`QK_HAPTIC_MODE_PREVIOUS`    |`HF_PREV`| Go to previous DRV2605L waveform                      |
|`QK_HAPTIC_CONTINUOUS_TOGGLE`|`HF_CONT`| Toggle continuous haptic mode on/off                  |
|`QK_HAPTIC_CONTINUOUS_UP`    |`HF_CONU`| Increase DRV2605L continuous haptic strength          |
|`QK_HAPTIC_CONTINUOUS_DOWN`  |`HF_COND`| Decrease DRV2605L continuous haptic strength          |
|`QK_HAPTIC_DWELL_UP`         |`HF_DWLU`| Increase Solenoid dwell time                          |
|`QK_HAPTIC_DWELL_DOWN`       |`HF_DWLD`| Decrease Solenoid dwell time                          |

### Solenoids

The solenoid code supports relay switches, and similar hardware, as well as solenoids.

For a regular solenoid,  you will need a build a circuit to drive the solenoid through a mosfet as most MCU will not be able to provide the current needed to drive the coil in the solenoid.

[Wiring diagram provided by Adafruit](https://cdn-shop.adafruit.com/product-files/412/solenoid_driver.pdf)

For relay switches, the hardware may already contain all of that ciruitry, and just require VCC, GND and a data pin.

| Settings                   | Default              | Description                                                  |
|----------------------------|----------------------|--------------------------------------------------------------|
|`SOLENOID_PIN`              | *Not defined*        |Configures the pin that the switch  is connected to.          |
|`SOLENOID_PIN_ACTIVE_LOW`   | *Not defined*        |If defined then the switch trigger pin is active low.         |
|`SOLENOID_PINS`             | *Not defined*        |Configures an array of pins to be used for switch activation. |
|`SOLENOID_PINS_ACTIVE_LOW`  | *Not defined*        |Allows you to specify how each pin is pulled for activation.  |
|`SOLENOID_RANDOM_FIRE`      | *Not defined*        |When there are multiple solenoids, will select a random one to fire.|
|`SOLENOID_DEFAULT_DWELL`    | `12` ms              |Configures the default dwell time for the switch.             |
|`SOLENOID_MIN_DWELL`        | `4` ms               |Sets the lower limit for the dwell.                           |
|`SOLENOID_MAX_DWELL`        | `100` ms             |Sets the upper limit for the dwell.                           |
|`SOLENOID_DWELL_STEP_SIZE`  | `1` ms               |The step size to use when `HF_DWL*` keycodes are sent.        |
|`SOLENOID_DEFAULT_BUZZ`     | `0` (disabled)       |On `HF_RST` buzz is set "on" if this is "1"                   |
|`SOLENOID_BUZZ_ACTUATED`    | `SOLENOID_MIN_DWELL` |Actuated-time when the switch is in buzz mode.                |
|`SOLENOID_BUZZ_NONACTUATED` | `SOLENOID_MIN_DWELL` |Non-Actuated-time when the switch is in buzz mode.            |

* If solenoid buzz is off, then dwell time is how long the "plunger" stays activated. The dwell time changes how the solenoid sounds.
* If solenoid buzz is on, then dwell time sets the length of the buzz, while `SOLENOID_BUZZ_ACTUATED` and `SOLENOID_BUZZ_NONACTUATED` set the (non-)actuation times within the buzz period.
* With the current implementation, for any of the above time settings, the precision of these settings may be affected by how fast the keyboard is able to scan the matrix.
  Therefore, if the keyboards scanning routine is slow, it may be preferable to set `SOLENOID_DWELL_STEP_SIZE` to a value slightly smaller than the time it takes to scan the keyboard.

Beware that some pins may be powered during bootloader (ie. A13 on the STM32F303 chip) and will result in the solenoid kept in the on state through the whole flashing process. This may overheat and damage the solenoid. If you find that the pin the solenoid is connected to is triggering the solenoid during bootloader/DFU, select another pin.

### DRV2605L

DRV2605L is controlled over i2c protocol, and has to be connected to the SDA and SCL pins, these varies depending on the MCU in use.

#### Feedback motor setup

This driver supports 2 different feedback motors. Set the following in your `config.h` based on which motor you have selected.

##### ERM

Eccentric Rotating Mass vibration motors (ERM) is motor with a off-set weight attached so when drive signal is attached, the off-set weight spins and causes a sinusoidal wave that translate into vibrations.

```c
#define DRV2605L_FB_ERM_LRA 0
#define DRV2605L_FB_BRAKEFACTOR 3 /* For 1x:0, 2x:1, 3x:2, 4x:3, 6x:4, 8x:5, 16x:6, Disable Braking:7 */
#define DRV2605L_FB_LOOPGAIN 1 /* For  Low:0, Medium:1, High:2, Very High:3 */

/* Please refer to your datasheet for the optimal setting for your specific motor. */
#define DRV2605L_RATED_VOLTAGE 3
#define DRV2605L_V_PEAK 5
```
##### LRA

Linear resonant actuators (LRA, also know as a linear vibrator) works different from a ERM. A LRA has a weight and magnet suspended by springs and a voice coil. When the drive signal is applied, the weight would be vibrate on a single axis (side to side or up and down). Since the weight is attached to a spring, there is a resonance effect at a specific frequency. This frequency is where the LRA will operate the most efficiently. Refer to the motor's datasheet for the recommended range for this frequency.

```c
#define DRV2605L_FB_ERM_LRA 1
#define DRV2605L_FB_BRAKEFACTOR 3 /* For 1x:0, 2x:1, 3x:2, 4x:3, 6x:4, 8x:5, 16x:6, Disable Braking:7 */
#define DRV2605L_FB_LOOPGAIN 1 /* For  Low:0, Medium:1, High:2, Very High:3 */

/* Please refer to your datasheet for the optimal setting for your specific motor. */
#define DRV2605L_RATED_VOLTAGE 2
#define DRV2605L_V_PEAK 2.8
#define DRV2605L_V_RMS 2.0
#define DRV2605L_V_PEAK 2.1
#define DRV2605L_F_LRA 205 /* resonance freq */
```

#### DRV2605L waveform library

DRV2605L comes with preloaded library of various waveform sequences that can be called and played. If writing a macro, these waveforms can be played using `DRV_pulse(*sequence name or number*)`

List of waveform sequences from the datasheet:

|seq# | Sequence name       |seq# | Sequence name                     |seq# |Sequence name                         |
|-----|---------------------|-----|-----------------------------------|-----|--------------------------------------|
| 1   | strong_click 		| 43  | lg_dblclick_med_60                | 85  | transition_rampup_med_smooth2        |
| 2   | strong_click_60 	| 44  | lg_dblsharp_tick                  | 86  | transition_rampup_short_smooth1      |
| 3   | strong_click_30 	| 45  | lg_dblsharp_tick_80               | 87  | transition_rampup_short_smooth2      |
| 4   | sharp_click 		| 46  | lg_dblsharp_tick_60               | 88  | transition_rampup_long_sharp1        |
| 5   | sharp_click_60      | 47  | buzz                              | 89  | transition_rampup_long_sharp2        |
| 6   | sharp_click_30      | 48  | buzz_80				              | 90  | transition_rampup_med_sharp1         |
| 7   | soft_bump           | 49  | buzz_60		                      | 91  | transition_rampup_med_sharp2         |
| 8   | soft_bump_60        | 50  | buzz_40				              | 92  | transition_rampup_short_sharp1       |
| 9   | soft_bump_30        | 51  | buzz_20				              | 93  | transition_rampup_short_sharp2       |
| 10  | dbl_click           | 52  | pulsing_strong                    | 94  | transition_rampdown_long_smooth1_50  |
| 11  | dbl_click_60        | 53  | pulsing_strong_80                 | 95  | transition_rampdown_long_smooth2_50  |
| 12  | trp_click           | 54  | pulsing_medium                    | 96  | transition_rampdown_med_smooth1_50   |
| 13  | soft_fuzz           | 55  | pulsing_medium_80                 | 97  | transition_rampdown_med_smooth2_50   |
| 14  | strong_buzz         | 56  | pulsing_sharp                     | 98  | transition_rampdown_short_smooth1_50 |
| 15  | alert_750ms         | 57  | pulsing_sharp_80                  | 99  | transition_rampdown_short_smooth2_50 |
| 16  | alert_1000ms        | 58  | transition_click	              | 100 | transition_rampdown_long_sharp1_50   |
| 17  | strong_click1       | 59  | transition_click_80               | 101 | transition_rampdown_long_sharp2_50   |
| 18  | strong_click2_80    | 60  | transition_click_60	              | 102 | transition_rampdown_med_sharp1_50    |
| 19  | strong_click3_60    | 61  | transition_click_40	              | 103 | transition_rampdown_med_sharp2_50    |
| 20  | strong_click4_30    | 62  | transition_click_20	              | 104 | transition_rampdown_short_sharp1_50  |
| 21  | medium_click1       | 63  | transition_click_10	              | 105 | transition_rampdown_short_sharp2_50  |
| 22  | medium_click2_80    | 64  | transition_hum                    | 106 | transition_rampup_long_smooth1_50    |
| 23  | medium_click3_60    | 65  | transition_hum_80                 | 107 | transition_rampup_long_smooth2_50    |
| 24  | sharp_tick1         | 66  | transition_hum_60                 | 108 | transition_rampup_med_smooth1_50     |
| 25  | sharp_tick2_80      | 67  | transition_hum_40                 | 109 | transition_rampup_med_smooth2_50     |
| 26  | sharp_tick3_60      | 68  | transition_hum_20                 | 110 | transition_rampup_short_smooth1_50   |
| 27  | sh_dblclick_str     | 69  | transition_hum_10                 | 111 | transition_rampup_short_smooth2_50   |
| 28  | sh_dblclick_str_80  | 70  | transition_rampdown_long_smooth1  | 112 | transition_rampup_long_sharp1_50     |
| 29  | sh_dblclick_str_60  | 71  | transition_rampdown_long_smooth2  | 113 | transition_rampup_long_sharp2_50     |
| 30  | sh_dblclick_str_30  | 72  | transition_rampdown_med_smooth1   | 114 | transition_rampup_med_sharp1_50      |
| 31  | sh_dblclick_med     | 73  | transition_rampdown_med_smooth2   | 115 | transition_rampup_med_sharp2_50      |
| 32  | sh_dblclick_med_80  | 74  | transition_rampdown_short_smooth1 | 116 | transition_rampup_short_sharp1_50    |
| 33  | sh_dblclick_med_60  | 75  | transition_rampdown_short_smooth2 | 117 | transition_rampup_short_sharp2_50    |
| 34  | sh_dblsharp_tick    | 76  | transition_rampdown_long_sharp1   | 118 | long_buzz_for_programmatic_stopping  |
| 35  | sh_dblsharp_tick_80 | 77  | transition_rampdown_long_sharp2   | 119 | smooth_hum1_50                       |
| 36  | sh_dblsharp_tick_60 | 78  | transition_rampdown_med_sharp1    | 120 | smooth_hum2_40                       |
| 37  | lg_dblclick_str     | 79  | transition_rampdown_med_sharp2    | 121 | smooth_hum3_30                       |
| 38  | lg_dblclick_str_80  | 80  | transition_rampdown_short_sharp1  | 122 | smooth_hum4_20                       |
| 39  | lg_dblclick_str_60  | 81  | transition_rampdown_short_sharp2  | 123 | smooth_hum5_10                       |
| 40  | lg_dblclick_str_30  | 82  | transition_rampup_long_smooth1    |     |                                      |
| 41  | lg_dblclick_med     | 83  | transition_rampup_long_smooth2    |     |                                      |
| 42  | lg_dblclick_med_80  | 84  | transition_rampup_med_smooth1     |     |                                      |
### Optional DRV2605L defines

```c
#define DRV2605L_GREETING *sequence name or number*
```
If haptic feedback is enabled, the keyboard will vibrate to a specific sequence during startup. That can be selected using the following define:

```c
#define DRV2605L_DEFAULT_MODE *sequence name or number*
```
This will set what sequence `HF_RST` will set as the active mode. If not defined, mode will be set to 1 when `HF_RST` is pressed.

### DRV2605L Continuous Haptic Mode

This mode sets continuous haptic feedback with the option to increase or decrease strength.

## Haptic Key Exclusion
The Haptic Exclusion is implemented as `__attribute__((weak)) bool get_haptic_enabled_key(uint16_t keycode, keyrecord_t *record)` in haptic.c. This allows a re-definition at the required level with the specific requirement / exclusion.

### NO_HAPTIC_MOD
With the entry of `#define NO_HAPTIC_MOD` in config.h, the following keys will not trigger feedback:

* Usual modifier keys such as Control/Shift/Alt/Gui (For example `KC_LCTL`)
* `MO()` momentary keys. See also [Layers](../feature_layers).
* `LM()` momentary keys with mod active.
* `LT()` layer tap keys, when held to activate a layer. However when tapped, and the key is quickly released, and sends a keycode, haptic feedback is still triggered.
* `TT()` layer tap toggle keys, when held to activate a layer. However when tapped `TAPPING_TOGGLE` times to permanently toggle the layer, on the last tap haptic feedback is still triggered.
* `MT()` mod tap keys, when held to keep a usual modifier key pressed. However when tapped, and the key is quickly released, and sends a keycode, haptic feedback is still triggered. See also [Mod-Tap](../mod_tap).

### NO_HAPTIC_ALPHA
With the entry of `#define NO_HAPTIC_ALPHA` in config.h, none of the alpha keys (A ... Z) will trigger a feedback.

### NO_HAPTIC_PUNCTUATION
With the entry of `#define NO_HAPTIC_PUNCTUATION` in config.h, none of the following keys will trigger a feedback: Enter, ESC, Backspace, Space, Minus, Equal, Left Bracket, Right Bracket, Backslash, Non-US Hash, Semicolon, Quote, Grave, Comma, Slash, Dot, Non-US Backslash.

### NO_HAPTIC_LOCKKEYS
With the entry of `#define NO_HAPTIC_LOCKKEYS` in config.h, none of the following keys will trigger a feedback: Caps Lock, Scroll Lock, Num Lock.

### NO_HAPTIC_NAV
With the entry of `#define NO_HAPTIC_NAV` in config.h, none of the following keys will trigger a feedback: Print Screen, Pause, Insert, Delete, Page Down, Page Up, Left Arrow, Up Arrow, Right Arrow, Down Arrow, End, Home.

### NO_HAPTIC_NUMERIC
With the entry of `#define NO_HAPTIC_NUMERIC` in config.h, none of the following keys between 0 and 9 (KC_1 ... KC_0) will trigger a feedback.
