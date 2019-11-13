# ninjonas Keymap for [ErgoDox (HotDox)](https://www.alpacakeyboards.com/)

## Setup
- Ensure you've cloned the [qmk](https://github.com/qmk/qmk_firmware) repo
- Create directory `ninjonas` on `/keyboards/hotdox/keymaps/`
- Run `copy_keymap.sh`. This copies the contents of this repo into `%qmk_firmware%/ninjonas/` directory
- To push your keymap to your keyboard run this command `make clean hotdox:ninjonas:dfu`
    - this compiles your keymap and creates a `hotdox_ninjonas.hex` file and will atempt to flash your board
    - if you get the following message:
      ```
      dfu-programmer: no device present.
      Error: Bootloader not found. Trying again in 5s.
      ```
    - Press the reset button underneath your ErgoDox keyboard
    - The following messages should show up and your board has successfuly been flashed
      ```
      Bootloader Version: 0x00 (0)
      Erasing flash...  Success
      Checking memory from 0x0 to 0x6FFF...  Empty.
      Checking memory from 0x0 to 0x5D7F...  Empty.
      0%                            100%  Programming 0x5D80 bytes...
      [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]  Success
      0%                            100%  Reading 0x7000 bytes...
      [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]  Success
      Validating...  Success
      0x5D80 bytes written into 0x7000 bytes memory (83.48%).
      ```
    - The alterenative is follow the steps on [Hotdox flashing guide](https://www.alpacakeyboards.com/flash/hot-dox-ergodox-76-flashing-instructions)

## Keymap
This keymap is designed based off my typing habits and is subject to change. Information about custom user macros and tap dances can be found [here](https://github.com/ninjonas/qmk-yonas/tree/master/users/ninjonas).

### QWERTY
```c
/* Keymap 0: QWERTY
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   `    |   1  |   2  |   3  |   4  |   5  | Play |           |K_LOCK |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |-------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |      |           |       |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |       |------+------+------+------+------+--------|
 * | Esc    |   A  |   S  |   D  |   F  |   G  |------|           |-------|   H  |   J  |   K  |   L  |  ;   |   '    |
 * |--------+------+------+------+------+------|  [   |           |   ]   |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |       |   N  |   M  |   ,  |   .  |  /   |   =    |
 * `--------+------+------+------+------+-------------'           `--------------+------+------+------+------+--------'
 *   |M_SHFT|      | Alt  |     | Ctl  |                                        | BkSP | Del  |LOWER |M_XXX1|M_PYNV|
 *   `----------------------------------'                                        `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |  Up  | Down |       | Left | Right|
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | Home |       | PgUp |      |      |
 *                                 | Space|Backsp|------|       |------| Del  |Enter |
 *                                 |      |ace   | End  |       | PgDn |      |      |
 *                                 `--------------------'       `--------------------'
 */
```

### LOWER
```c
/* Keymap 1: LOWER
 *
 * ,--------------------------------------------------.           ,----------------------------------------------------.
 * |  F11   |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |       |  F6  |  F7  |  F8  |  F9  |  F10  |  F12   |
 * |--------+------+------+------+------+-------------|           |-------+------+------+------+------+-------+--------|
 * |        |      |      |KC_BRU| Play | Mute |      |           |       | PgUp | Home |  Up  | End  |       |        |
 * |--------+------+------+------+------+------|      |           |       |------+------+------+------+-------+--------|
 * |        |      |      |KC_BRD| Next |VolUp |------|           |-------| PgDn | Left | Down |Right |K_LOCK |        |
 * |--------+------+------+------+------+------|      |           |       |------+------+------+------+-------+--------|
 * |        |      |      |      | Prev |VolDn |      |           |       |      |      |      |      |       |        |
 * `--------+------+------+------+------+-------------'           `--------------+------+------+------+-------+--------'
 *   |      |      |      |      |      |                                        |      |      |      |M_CODE |      |
 *   `----------------------------------'                                        `-----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
```

### RAISE
```c
/* Keymap 2: RAISE
 *
 * ,--------------------------------------------------.           ,----------------------------------------------------.
 * |        |      |      |      |K_CSCN|      |      |           |       |      |      |      |      |       |        |
 * |--------+------+------+------+------+-------------|           |-------+------+------+------+------+-------+--------|
 * | M_MAKE |      | MS_1 | MS_U | MS_2 | WH_U |      |           |       |      |      |      |      |       |        |
 * |--------+------+------+------+------+------|      |           |       |------+------+------+------+-------+--------|
 * | M_VRSN |      | MS_L | MS_D | MS_R | WH_D |------|           |-------|      |      |      |      |       |        |
 * |--------+------+------+------+------+------|      |           |       |------+------+------+------+-------+--------|
 * | M_FLSH |      |      |      |      |      |      |           |       |      |      |      |      |       |        |
 * `--------+------+------+------+------+-------------'           `--------------+------+------+------+-------+--------'
 *   |      |      |      |      |      |                                        |      |      |      |       |      |
 *   `----------------------------------'                                        `-----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
```