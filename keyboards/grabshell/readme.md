# Grabshell

![Grabshell](https://i.imgur.com/qCp6ZMK.jpeg)
![Grabshell](https://i.imgur.com/nFFXDRv.jpeg)

* Keyboard Maintainer: [Grabshell](https://github.com/mikubravo)
* Hardware Supported: Grabshell
* Hardware Availability: [Grabshell](https://grabshell.site/)

*** Important ***
Modifying your Grabshell keyboard as described below will certainly void your warranty. 

Build example for this keyboard (after setting up your build environment):

```shell
qmk compile -kb grabshell -km default
```

Flashing example for this keyboard:

```shell
qmk flash -kb grabshell -km default
```

### Release v1.3.6:
Grabshell does not have an external physical reset button.　The DFU state in the bootloader can be accessed in 2 ways:

* **Bootmagic reset**: hold down the key at (0,0), commonly programmed as *Esc* in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Keycode in layout**: press the key mapped with VIA to `QK_BOOT` if it is available

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

Grabshell firmwares are verified to compile with QMK 0.23.1.

### Pointing Device Mode
To change the function of the trackball or analog-joystick mode. 
| Function              | Description                                                             | 
| --------------------- | ----------------------------------------------------------------------- |
| set_joystick_mode(uint8_t mode) | set mode of joystick                                          |
| get_joystick_mode(void) | get mode of joystick                                                  |
| set_paw_motton_mode(uint8_t mode) | set mode of trackball                                       |
| get_paw_motton_mode(void) | get mode of trackball                                               |

### Trackball Mode
To change the function of the trackball sensor (FCT3065):
| Trackball Sensor Mode | Description | 
| --------------------- | ----------------------------------------------------------------------- |
| PAW_NONE_MODE         | no function                                                             |
| PAW_MOUSE_MODE        | controlling the mouse cursor                                            |
| PAW_SCROLL_MODE       | drag scroll                                                             |

### Analog Joystick Mode
To change the function of the analog joystick:
Analog Joystick mode define
| Analog Joystick mode  | Description                                                             | 
| --------------------- | ----------------------------------------------------------------------- |
| WASD_MODE             | (A, W, S, D) Send the W (KC_W), A (KC_A), S (KC_S), and D (KC_D) key codes used in games. |
| MOUSE_MODE            | controlling the mouse cursor                                           |
| ARROW_MODE            | (←, ↑, ↓, →) Send Up (KC_UP), Down (KC_DOWN), Left (KC_LEFT), and Right (KC_RIGHT) key codes.|
| GAME_MODE             | controlling as a gamepad joystick                                      |

### Magnetic (LIS2MDL) sensor

Get values from magnetic sensor
```c
Get_Lis2mdl_XYZ(int16_t *x, int16_t *y, int16_t *z);
```
### 6DOF IMU (LSM6DS3TR-C) sensor
Get values from an accelerometer, a gyro sensor, and a temperature sensor
Default full scale range
acceleration range: ±4 g
angular rate range: ±500 dps

```c
GetAccel(int16_t *x, int16_t *y, int16_t *z);
GetGyro(int16_t *x, int16_t *y, int16_t *z);
getTemp(int16_t *t);
```

| Set IMU sensor range  | Description                                                             | 
| --------------------- | ----------------------------------------------------------------------- |
| i2c_status_t lsm6ds3tr_c_block_data_update_set(uint8_t val) | Block data update |
| i2c_status_t lsm6ds3tr_c_xl_data_rate_set(lsm6ds3tr_c_odr_xl_t val) | Accelerometer data rate selection |
| i2c_status_t lsm6ds3tr_c_gy_data_rate_set(lsm6ds3tr_c_odr_g_t val) | Gyroscope data rate selection |
| i2c_status_t lsm6ds3tr_c_xl_full_scale_set(lsm6ds3tr_c_fs_xl_t val) | Accelerometer full-scale selection |
| i2c_status_t lsm6ds3tr_c_gy_full_scale_set(lsm6ds3tr_c_fs_g_t val) | Gyroscope chain full-scale selection |
| i2c_status_t lsm6ds3tr_c_xl_filter_analog_set(lsm6ds3tr_c_bw0_xl_t val) | Accelerometer analog chain bandwidth selection (accelerometer ODR ≥ 1.67 kHz) |
| i2c_status_t lsm6ds3tr_c_xl_lp2_bandwidth_set(lsm6ds3tr_c_input_composite_t val) | LPF2 on outputs |
| i2c_status_t lsm6ds3tr_c_gy_band_pass_set(lsm6ds3tr_c_lpf1_sel_g_t val) | Gyroscope low pass path bandwidth |
