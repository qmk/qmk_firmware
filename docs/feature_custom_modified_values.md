# CMV (Custom Modified Values)

## General **Description**

The **CMV** feature which stands for **Custom Modified Values** allows you to customize the keycodes processed by the firmware for given keys depending on the state of the **Character Modifiers**.
The **Character Modifiers** (or **charmods**) are `Left Shift`, `Right Shift` and `Right Alt` (a.k.a. `AltGr`). There are **4 charmod configurations** handled:

|           CHARMODS PRESSED              | KCID |
|-----------------------------------------|------|
| None (or non-charmods mods are pressed) |  0   |
| Left and/or Right shift                 |  1   |
| Right alt                               |  2   |
| Left and/or Right shift AND Right alt   |  3   |

You can assign a custom value to any given key for any KCID value (i.e. **one key** can be assigned **up to 4 different keycodes** and one of them will be returned to and processed by the firmware depending on the current state of the charmods).

Of course, you **don't have to** assign a keycode **for every KCID**. Assigning 0 (or  `KC_NO`) as a custom modified value makes CMV **return the default keycode** of the key (KCID=0) to the firmware. So, you could for instance bind `KC_DELETE` to a key when pressed while holding down `AltGr`, and `KC_BSPACE` to that very same key in every other cases.

With most versions of **CMV**, you can assign **any 16-bit keycode as a modified value** (*This is not exactly true for every versions. Check out the detailed description for your version below*). This means that you could for example assign to a key (which we will reference as `K` in this documentation) the following:

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

---
## General **Set-Up** and **Configuration**

CMV can be user-enabled by writing `CUSTOM_MODIFIED_VALUES_ENABLE=yes` in your `rules.mk` file inside your keymap directory.

For more advanced customization and configuration, see **Advanced functionalities** for your corresponding version below.

---

## General **Usage**

- Redefine the `bool keycodes_for_key(uint16_t default_kc, uint8_t layer, uint8_t row, uint8_t col)` function in your `keymap.c` file the same way you would for the `bool process_record_user(uint16_t keycode, keyrecord_t *record)` function.
- In the `keycodes_for_key` function, use the function parameters to know which key is being processed. If you want to assign custom modified values to the processed key, use the `CMV(kcid0, kcid1, kcid2, kcid3)` macro.
    - The first parameter is the default keycode (just pass `default_kc`);
    - The second parameter is the keycode when one or more `Shift` are pressed (pass 0 if no custom modified value is desired here);
    - The third parameter is the keycode when one or more `AltGr` (=`Right Alt`) are pressed (pass 0 if no custom modified value is desired here).
    - The fourth parameter is the keycode when one or more `Shift` AND one or more `AltGr` (=`Right Alt`) are pressed (pass 0 if no custom modified value is desired here).
- The `keycodes_for_key` function must return `false` to make CMV understand that there are custom modified values assigned to the currently processed key. Otherwise, return `true`. (Tip: `CMV(...)` is always `false` so you can write `return CMV(/* ... */);` in your function).

---

## General **Examples**

1. **Every `KC_BSPACE` key returns `KC_DELETE` if pressed with `Left Shift` and/or `Right Shift`:**
    ```C
    bool keycodes_for_key(uint16_t default_kc, uint8_t layer, uint8_t row, uint8_t col) {
        if(default_kc == KC_BSPACE) return CMV(default_kc, KC_DELETE, 0, 0);
        // To do the same but with AltGr instead of Shifts, we would have written:
        // if(default_kc == KC_BSPACE) return CMV(default_kc, 0, KC_DELETE, 0);
        return true;
    }
    ``` 

2. Let's say there is a layer `COLEMAK` on which you assigned the key on the **col `1`** and on the **row `0xC`** to **`KC_DOT`** and you want to send **`KC_COMMA` when pressing that key with `Left Shift` and/or `Right Shift`** (Usage of this method is **DEPRECATED**, see the **WARNING** below to understand why):
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

4. Here's the code needed to accomplish the behaviour described as an example in the **General Description** section above:

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

# v2.*

## Description

Three **`CMV-v2.*`** versions will be available (All three **support classic modifiers and oneshot modifiers**):

- **`CMV-v2.*-Lite`**: 

    - The **lighter** of the three (~400 bytes).
    - It **doesn't update** the processed keycode when **pressing or releasing a modifier while a non-modifier key is held down**. It doesn't store the keycodes processed: this means it can result in **unexpected and undesirable behaviours** when releasing a key assigned to an **advanced keycode** (i.e. some of 16-bit *quantum* keycodes) **if the active modifiers are not the same as those when you pressed the key** in the first place.
    
        But this version handles the **basic keycodes** (i.e. every 8-bit *TMK* keycodes and some 16-bit *quantum* keycodes) as custom modified values just fine.

    - In conclusion, this version is **perfect for a basic use** of the CMV feature.

- **`CMV-v2.*-Normal`**: *TO BE COMING...*

- **`CMV-v2.*-Complete`**: *TO BE COMING...*

---
# v1.*

## v1.* - Description

These are the first versions of the feature. Although they work great, they use a **different internal architecture** (i.e. far **more messy** and far **less clean**) than more recent versions and are **heavier in general**.

---

## v1.* - Limitations

- **No `CMV-v1.*` version supports Oneshot modifiers.**
- You **cannot** assign **modifier**'s keycodes **as custom modified values**.
- `CMV-v1.*` versions require **more storage space** than more recent versions.

---

## v1.* - Configuration

By default the **Lite** version of `CMV-v1.*` is used which is enough for a **normal use of the feature**. There is another version called the **Complete** version, which is essentially the same as the **Lite** version but has **more functionalities** hence its **bigger storage usage**. To load the **Complete** version instead of the **Lite** version, add `#define CMV_COMPLETE_VERSION` along with `#define CUSTOM_MODIFIED_VALUES_ENABLE` in your `config.h` file.

For more advanced customization and configuration, see **Advanced functionalities**.

---

## v1.* - Advanced functionalities

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

---

# How does the feature work ?

## CMV-2.*

The magic happens mainly in `quantum/keymap_common.c` where we modify the `keymap_key_to_keycode` function to return the keycode returned by our custom function `keymap_key_to_keycode_cmv`:
```C
// in quantum/keymap_common.c near line 232
__attribute__ ((weak))
uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t key)
{
#if defined(CUSTOM_MODIFIED_VALUES_ENABLE)
    return keymap_key_to_keycode_cmv(layer, key);
#else
    // Read entire word (16bits)
    return pgm_read_word(&keymaps[(layer)][(key.row)][(key.col)]);
#endif
}
```

Fisrt thing we do in `keymap_key_to_keycode_cmv` is calling the functions `get_kcid` and `get_custom_modified_values_for_key` to determine **if the user assigned custom modified values to the currently processed key**: 
```C
// in quantum/keymap_common.c near line 220
static uint16_t keymap_key_to_keycode_cmv(uint8_t layer, keypos_t key) {
  uint8_t kcid = get_kcid(get_custom_modified_values_for_key(pgm_read_word(&keymaps[(layer)][(key.row)][(key.col)]), layer, key));
  if (kcid) {
    set_mods_blocker(true);
  } else {
    set_mods_blocker(false);
  }
  return cmv_buffer[kcid];
}
```

The function `get_custom_modified_values_for_key` calls the **user-overridable** function `keycodes_for_key` which returns `false` if custom modified values are assigned to the currently processed key or `true` otherwise.
```C
// in quantum/keymap_common.c near line 205
static uint16_t* get_custom_modified_values_for_key(uint16_t default_kc, uint8_t layer, keypos_t key) {
  if(keycodes_for_key(default_kc, layer, key)) {
    set_cmv_buffer(default_kc, 0, 0, 0);
  }
  return cmv_buffer;
}
```

Inside `keycodes_for_key`, the user must use the `CMV(...)` macro defined as following and passing it the wanted custom modified values which can be any 16-bit keycodes:
```C
// in quantum/custom_modified_values.h near line 13
#define CMV(kc_default, kc_shifted, kc_altgred, kc_sftralt) set_cmv_buffer(kc_default, kc_shifted, kc_altgred, kc_sftralt)
```

The `set_cmv_buffer` function fills the array used as a buffer by the feature which is initialized like this:
```C
// in quantum/keymap_common.c near line 190
static uint16_t cmv_buffer[4] = {0,0,0,0};
```

So back in `keymap_key_to_keycode_cmv`, `get_custom_modified_values_for_key` returns a pointer to `cmv_buffer` which is being passed as a parameter to the `get_kcid` function. This latter returns the *KCID* depending on the current state of the modifiers (we are going to use it as an index in `cmv_buffer`). The KCID is an integer from 0 to 4. For example, if `KC_LSHIFT` is currently being held down, `get_kcid` will return `1` IF AND ONLY IF there is a custom *shifted* keycode assigned to the key and this keycode is **different than 0**.
```C
// in quantum/keymap_common.c near line 212
static uint8_t get_kcid(uint16_t* kcs) {
  if(are_there_non_charmods()) return 0;
  else if(are_there_shifts() && are_there_ralts() && kcs[3]) return 3;
  else if(are_there_shifts() && kcs[1]) return 1;
  else if(are_there_ralts() && kcs[2]) return 2;
  return 0;
}
```
(Note: I think it is a good idea to return the default keycode (i.e. KCID=0) if there are any non-charmods modifiers active, so the user can still use shortcuts such as `Ctrl+Shift+;` (for example, in Visual Studio Code) even if they assigned a custom shifted keycode to the `;` key)

The `are_there_*` functions called in `get_kcid` are defined in `tmk_core/common/action_util.c`. They use the **appropriate *modifiers mask*** to see if the **wanted modifiers are set** in any of the four `uint8_t` variables holding the modifiers' state: **`real_mods`**, **`macro_mods`**, **`oneshot_mods`** and **`oneshot_locked_mods`**:
```C
// in tmk_core/common/action_util.c near line 69
// #define CMV_NON_CHARMODS_MASK (0b00000000 | MOD_BIT(KC_RGUI) | MOD_BIT(KC_RCTRL) | MOD_BIT(KC_LGUI) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LCTRL))
#define CMV_NON_CHARMODS_MASK 0b10011101
// #define CMV_SHIFTS_MASK (0b00000000 | MOD_BIT(KC_RSHIFT) | MOD_BIT(KC_LSHIFT))
#define CMV_SHIFTS_MASK 0b00100010
// #define CMV_RALT_MASK (0b00000000 | MOD_BIT(KC_RALT))
#define CMV_RALT_MASK 0b01000000

#ifndef NO_ACTION_ONESHOT
# define ARE_THERE_THESE_MODS(mods_mask) (  \
    (mods_mask & real_mods)     ||          \
    (mods_mask & macro_mods)    ||          \
    (mods_mask & oneshot_mods)  ||          \
    (mods_mask & oneshot_locked_mods))
#else
# define ARE_THERE_THESE_MODS(mods_mask) ((mods_mask & real_mods) || (mods_mask & macro_mods))
#endif

bool are_there_non_charmods(void) { return ARE_THERE_THESE_MODS(CMV_NON_CHARMODS_MASK); }
bool are_there_shifts(void) { return ARE_THERE_THESE_MODS(CMV_SHIFTS_MASK); }
bool are_there_ralts(void) { return ARE_THERE_THESE_MODS(CMV_RALT_MASK); }
```

Back in `keymap_key_to_keycode_cmv` now. If KCID value returned by `get_kcid` **is 0** this means that we want to return the **default keycode** to the firmware. If the KCID is **any other value** (i.e. 1, 2 or 3) this means there **is a custom modified value** and we have to return it to the firmware. However, since we want the user to be able to assign **any 16-bit keycode as a custom modified value**, we have to **NOT send the charmods** currently pressed so for example, `KC_X` assigned as a custom shifted value gives `x` (it would give `X` if we sent the currently pressed `Shift`). To *block* (or to *unblock*) the modifiers, we use the `set_mods_blocker` function which set the value of the variable `dont_send_modifiers` defined as:
```C
// in tmk_core/common/action_util.c near line 86
static bool dont_send_mods = false;
``` 

This variable is then used inside the `send_keyboard_report` function to **prevent the `mods` part of the `keyboard_report` to be filled** by `real_mods`, `macro_mods`, `oneshot_mods` or `oneshot_locked_mods` (But not `weak_mods` since it is used for keycodes such as `LFST(KC_DOT)`):
```C
// in tmk_core/common/action_util.c near line 187
void send_keyboard_report(void) {
#ifdef CUSTOM_MODIFIED_VALUES_ENABLE
    if (dont_send_mods) {
      keyboard_report->mods = weak_mods;
# ifndef NO_ACTION_ONESHOT
          if (oneshot_mods) {
#   if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
              if (has_oneshot_mods_timed_out()) {
                  dprintf("Oneshot: timeout\n");
                  clear_oneshot_mods();
              }
#   endif
              if (has_anykey(keyboard_report)) {
                  clear_oneshot_mods();
                  host_keyboard_send(keyboard_report); // These two lines are here to  
                  clear_keys();                        // prevent the keycode to get stuck
              }
          }
# endif
    } else {
#endif
    keyboard_report->mods  = real_mods;
    keyboard_report->mods |= weak_mods;
    keyboard_report->mods |= macro_mods;
#ifndef NO_ACTION_ONESHOT
    if (oneshot_mods) {
#if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
        if (has_oneshot_mods_timed_out()) {
            dprintf("Oneshot: timeout\n");
            clear_oneshot_mods();
        }
#endif
        keyboard_report->mods |= oneshot_mods;
        if (has_anykey(keyboard_report)) {
            clear_oneshot_mods();
        }
    }
#endif
#ifdef CUSTOM_MODIFIED_VALUES_ENABLE
    }
#endif

    host_keyboard_send(keyboard_report);
}
```

Finally, a last problem needed to be solved: if the user **release a key at a moment where the modifiers' state is different than it was when the key was pressed**, it is most likely that the returned keycode will not be the same as the one returned when the key was pressed in the first place which **will result in a *stuck* key**. To solve this issue without having to store the keycodes processed when the key was pressed (that would make the feature notably heavier (this is done in the `CMV-2.0-Normal` version)), we have to **clear keys when the modifiers' state changes** (for oneshots modifiers it is done by the two lines in the code right above this):
```C
// in tmk_core/common/action_util.c near line 221
void add_mods(uint8_t mods) {
#ifdef CUSTOM_MODIFIED_VALUES_ENABLE
  clear_keys();
#endif
  real_mods |= mods;
}

void del_mods(uint8_t mods) {
#ifdef CUSTOM_MODIFIED_VALUES_ENABLE
  clear_keys();
#endif
  real_mods &= ~mods;
}
```

(Please take note that this solves the problem for MOST of the keycodes but the problem can still potentially occur for some advanced keycodes. If you're absolutely willing to use these latter keycodes, please consider allocating a little more space to the feature and use the `CMV-2.0-Normal` version (currently in development) instead which will solve this problem.)
