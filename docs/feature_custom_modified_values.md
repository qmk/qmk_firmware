# CMV (Custom Modified Values)

## Description

The **CMV** feature which stands for **Custom Modified Values** allows you to customize the keycodes processed by the firmware for given keys depending on the state of the **Character Modifiers**.
The **Character Modifiers** (or **charmods**) are `KC_LSHIFT`, `KC_RSHIFT` and `KC_RALT` (a.k.a. `AltGr`). There are **4 charmod configurations** handled:

|           CHARMODS PRESSED              | KCID |
|-----------------------------------------|------|
| None (or non-charmods mods are pressed) |  0   |
| Left and/or Right shift                 |  1   |
| Right alt                               |  2   |
| Left and/or Right shift AND Right alt   |  3   |

You can assign a custom value to any given key for any KCID value (i.e. **one key** can be assigned **up to 4 different keycodes** and one of them will be returned to and processed by the firmware depending on the current state of the charmods).

You can assign **any 16-bit keycode** (except the eight modifiers's) as a modified value. This means that you could for example assign to the key `K` the following:

| KCID | KEYCODE |
|------|---------|
| 0    | `TO(1)` |
| 1    | `TO(2)` |
| 2    | `TO(5)` |
| 3    | `TO(3)` |

Which means that: 
- Pressing `K` alone will switch to layer 1
- Pressing `K` with one or more `Shift` held down will switch to layer 2
- Pressing `K` with `AltGr` (= `Right Alt`) held down will switch to layer 5
- Pressing `K` with one or more `Shift` AND `AltGr` held down will switch to layer 3

Of course, you **don't have to** assign a keycode **for every KCID**. Assigning 0 (or  `KC_NO`) as a custom modified value makes CMV **return the default keycode** of the key (KCID=0) to the firmware. So, you could for instance bind `KC_DELETE` to a key when pressed while holding down `AltGr`, and `KC_BSPACE` to that very same key in every other cases.

---

## Configuration

CMV can be user-enabled by writing `#define CUSTOM_MODIFIED_VALUES_ENABLE` in your `config.h` file inside your keymap directory.

By default the **Lite** version of CMV is used which is enough for a **normal use of the feature**. There is another version called the **Complete** version, which is essentially the same as the **Lite** version but has **more functionalities** hence its **bigger storage usage**. To load the **Complete** version instead of the **Lite** version, add `#define CMV_COMPLETE_VERSION` along with `#define CUSTOM_MODIFIED_VALUES_ENABLE` in your `config.h` file.

For more advanced customization and configuration, see **Advanced functionalities**.

---

## Usage

- Redefine the `bool keycodes_for_key(uint16_t default_kc, uint8_t layer, uint8_t row, uint8_t col)` function in your `keymap.c` file the same way you would for the `bool process_record_user(uint16_t keycode, keyrecord_t *record)` function.
- In the `keycodes_for_key` function, use the function parameters to know which key is being processed. If you want to assign custom modified values to the processed key, use the `CMV(kcid0, kcid1, kcid2, kcid3)` macro.
    - The first parameter is the default keycode (just pass `default_kc`);
    - The second parameter is the keycode when one or more `Shift` are pressed (pass 0 if no custom modified value is desired here);
    - The third parameter is the keycode when one or more `AltGr` (=`Right Alt`) are pressed (pass 0 if no custom modified value is desired here).
    - The fourth parameter is the keycode when one or more `Shift` AND one or more `AltGr` (=`Right Alt`) are pressed (pass 0 if no custom modified value is desired here).
- The `keycodes_for_key` function must return `false` to make CMV understand that there are custom modified values assigned to the currently processed key. Otherwise, return `true`. (Tip: `CMV(...)` is always `false` so you can write `return CMV(/* ... */);` in your function).

---

## Examples

1. **Every `KC_BSPACE` key returns `KC_DELETE` if pressed with `KC_LSHIFT` and/or `KC_RSHIFT`:**
    ```C
    bool keycodes_for_key(uint16_t default_kc, uint8_t layer, uint8_t row, uint8_t col) {
        if(default_kc == KC_BSPACE) return CMV(default_kc, KC_DELETE, 0, 0);
        // To do the same but with AltGr instead of Shifts, we would have wrote:
        // if(default_kc == KC_BSPACE) return CMV(default_kc, 0, KC_DELETE, 0);
        return true;
    }
    ``` 

2. Let's say there is a layer `COLEMAK` on which you assigned the key on the **col `1`** and on the **row `0xC`** to **`KC_DOT`** and you want to send **`KC_COMMA` when pressing that key with `KC_LSHIFT` and/or `KC_RSHIFT`** (Usage of this method is **DEPRECATED**, see the **WARNING** below to understand why):
    ```C
    bool keycodes_for_key(uint16_t default_kc, uint8_t layer, uint8_t row, uint8_t col) {
        switch(layer) {
        case COLEMAK:
            switch(col) {
            case 1:
                switch(row) {

                /* ... */

                case 0xC: return CMV(default_kc, KC_COMMA, 0, 0);

                /* ... */
                    
                }
            break;

            /* ... */

            }
        break;

        /* ... */

        }
        return true;
    }
    ```
    (Note: This example was assuming that you assigned other Custom Modified Values on keys on the same row and/or on the same col and/or on the same layer. The following does essentially the same than the last one but is more optimized for the case that this is the only key you're assigning Custom Modified Values to:)

    ```C
    bool keycodes_for_key(uint16_t default_kc, uint8_t layer, uint8_t row, uint8_t col) {
        if(layer == COLEMAK && col == 1 && row == 0xC) return CMV(default_kc, KC_COMMA, 0, 0);
        return true;
    }
    ```

    **WARNING:** The values contained in `row` and in `col` do not correspond to the spatial key positions on the keyboard but to the rows and the columns of the matrix which is an electronic circuit differing from one keyboard to another. This makes the use of the `row` and `col` parameters pretty difficult and confusing.

3. Alternatively, for the same result than the example 2, you could **assign the key a custom keycode** and check the value of `default_kc` inside `keycodes_for_key`. This allows to avoid to have to deal with the rows and columns mess (see the **WARNING** above):

    ```C
    enum custom_keycodes {
        PLACEHOLDER = SAFE_RANGE,
        DOT_BECOMES_COMMA_WHEN_WITH_SHIFT,
    };

    const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [COLEMAK] = KEYMAP(
            /* ... */
            DOT_BECOMES_COMMA_WHEN_WITH_SHIFT,
            /* ... */
        ),

        /* ... */
    };

    bool keycodes_for_key(uint16_t default_kc, uint8_t layer, uint8_t row, uint8_t col) {
        if(default_kc == DOT_BECOMES_COMMA_WHEN_WITH_SHIFT) return CMV(KC_DOT, KC_COMMA, 0, 0);
        return true;
    }
    ```
    (Note: Of course, if you use lots of custom keycodes for your Custom Modified Values, a `switch` structure is probably better to increase readability)

4. Here's the code needed to accomplish the behaviour described as an example in the **Description** part:

    ```C
    enum custom_keycodes {
        PLACEHOLDER = SAFE_RANGE,
        KEY_SWICTHING_TO_DIFFERENT_LAYERS,
    };

    const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [COLEMAK] = KEYMAP(
            /* ... */
            KEY_SWICTHING_TO_DIFFERENT_LAYERS,
            /* ... */
        ),

        /* ... */
    };

    bool keycodes_for_key(uint16_t default_kc, uint8_t layer, uint8_t row, uint8_t col) {
        if(default_kc == KEY_SWICTHING_TO_DIFFERENT_LAYERS) return CMV(TO(1), TO(2), TO(5), TO(3));
        return true;
    }
    ```

---

## Advanced functionalities

CMV has to define an internally-used array containing some informations on the currently held keys (modifiers and non-modifiers keys mixed). The **keyboard report** sent to the host by the firmware can contain **up to 6 non-modifiers keys plus the state of the 8 modifiers**. The CMV holds up to **8 modifiers and non-modifiers keys mixed by default** but you can customize this value to **save a little space** by writing `#define CMV_NUMBER_OF_HELD_KEYS [custom_number_of_keys_tracked_by_CMV]` in your `config.h` file. 


### **Customizations for the complete version ONLY:**

This is the **less restrictive** version but also the **heavier** in terms of bytes to store. The two main functionalities that are in the **Complete** version but not in the **Lite** version are: **Dynamic Active Key Processing** and **Delay After Modifier Release**.

- **Dynamic Active Key Processing**: This functionality consists mainly of a queue of keycodes to be processed, filled by CMV in three cases:
    1. The user **pressed** a **Character Modifier** while having a non-modifier key held down (this is the **Active Key**). In the case the **Active Key** has **Custom Modified Values**, the release event of the current keycode of the **Active Key** as well as the press event of the new keycode of the **Active Key** are added to the queue. (Let a key `K` with `CMV(KC_DOT, KC_COMMA, 0, 0)`. First, we are pressing **`K` alone** so a **dot is sent** to the host. Then, we **press `KC_LSHIFT`**. The release event of `KC_DOT` then the press event of `KC_COMMA` are added to the queue; in other terms: **a comma is sent instead of a dot as soon as we press `Shift`.**)
    2. The user **released** a **Character Modifier** while having a non-modifier key held down (this is the **Active Key**). In the case the **Active Key** had **Custom Modified Values**, the release event of the current keycode of the **Active Key** as well as the press event of the new keycode of the **Active Key** are added to the queue. (Let a key `K` with `CMV(KC_DOT, KC_COMMA, 0, 0)`. First, we are pressing **`K` with `Shift` held down** so a **comma is sent** to the host. Then, we **release `Shift`**. The release event of `KC_COMMA` then the press event of `KC_DOT` are added to the queue; in other terms: **a dot is sent instead of a comma as soon as we release `Shift`.**)
    3. The user **released** a non-modifier key (the **old Active Key**) while having another non-modifier key held down (the **new Active Key**). The **new Active Key**'s keycode press event is then added to the queue so it *"reminds"* the host what key was pressed before we pressed the **old Active Key**. (Let a key `K` assigned to `KC_X` and a key `L` assigned to `KC_Y`. First, we are **pressing `K` alone** so **`X` is printing** on the host. Then, while keeping `K` pressed, we **press `L`** which becomes the **new Active Key** and **`Y` is now printing** on the host. Finally, we **release `L`** so `K` become the **Active Key** again and **`X` is printing** again).
    
    **WARNING** this functionality can result in **unwanted behaviours in certain softwares especially in video games**. This is why this functionality **can be enable and disable at run-time** by using **`toggle_dynamic_active_key_processing()`** or **`toggle_dakp()`**. Here's how:
    ```C
    enum macros {
        TOG_DAKP,
    };

    const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [COLEMAK] = KEYMAP(
            /* ... */
            M(TOG_DAKP), // When you press this key, it enables/disables the DAKP functionality
            /* ... */
        ),

        /* ... */
    };

    const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
        switch(id) {
        case TOG_DAKP:
            if(record->event.pressed) toggle_dakp();
        break;
        }
    }
    ```

    You can also customize the **number of key events that can be stored at once in the queue**. The default is **3**. Write `#define CMV_KEYS_IN_KEY_QUEUE [custom_number_of_keys_in_queue]` in your `config.h` file.

- **Delay After Modifier Release**: There is a pretty common problem when using the **Complete** version with the **Dynamic Active Key Processing** functionality: when, for example, you want to save a document by pressing `Ctrl + S` and you do it so quickly that you release `Ctrl` before `S`, without the **Delay After Modifier Release** functionality, CMV will print `S` as soon as you release `Ctrl` (see *case 2* described in **Dynamic Active Key Processing** functionality part) which is probably not the behaviour you desire.

    With the **Delay After Modifier Release** functionality, you can define an **amount of time that CMV has to wait** before sending `S` to the host after you release `Ctrl`. If you **release `S`** during that time interval, CMV **won't send `S`** after the delay expires. By default this delay is set to **200 milliseconds** but you can customize it by writing `#define CMV_TIME_AFTER_MODIFIER_RELEASE [delay_in_milliseconds_here]` in your `config.h` file.

    By writing `#define CMV_NO_DELAY_AFTER_MODIFIER_RELEASE` in your `config.h` file, you can **disable completely this functionality** to use **a little less space**.

    It is also possible to **enable/disable it at run-time** using the **`toggle_delay_after_modifier_release()`** or **`toggle_damr()`** functions, like this:
    ```C
    enum macros {
        TOG_DAMR,
    };

    const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [COLEMAK] = KEYMAP(
            /* ... */
            M(TOG_DAMR), // When you press this key, it enables/disables the DAMR functionality
            /* ... */
        ),

        /* ... */
    };

    const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
        switch(id) {
        case TOG_DAMR:
            if(record->event.pressed) toggle_damr();
        break;
        }
    }
    ```
    (Note: when the **Dynamic Active Key Processing** functionality is disabled, the **Delay After Modifier Release** functionality is not used.)
