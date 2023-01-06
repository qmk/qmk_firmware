# Junco <!-- omit from toc -->

![Junco](https://i.imgur.com/WzZaIgQ.jpg)

Junco is a 60% Raspberry Pi Pico powered split keyboard boasting a 4x6 layout with an aggressive columnar stagger. It has 5 "thumb" keys on either side, support for 2-4 rotary encoders, and per-key RGB lighting.

- Keyboard Maintainer: [Dane Skalski](https://github.com/Daneski13)
- Hardware Supported: Junco PCB, Raspberry Pi Pico
- Hardware Availability: [PCB, Case, Parts List](https://github.com/Daneski13/Junco)

Remember you have to flash both halves of the keyboard for it to work!

Make example for this keyboard (after setting up your build environment):

    make junco:default

Flashing example for this keyboard:

```bash
# For flashing the left half...
make junco:default:uf2-split-left
# or the qmk cli equivalent:
qmk flash -kb junco --keymap default -bl uf2-split-left

# For flashing the right half...
make junco:default:uf2-split-right
# or the qmk cli equivalent:
qmk flash -kb junco --keymap default -bl uf2-split-right
```

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

Does one side of your keyboard think it's the other side? Holding down the `1` key on the left side of your keyboard while plugging it in will tell the left side it's the left side. Holding down the `9` key on the right side of your keyboard while plugging it in will tell the right side it's the right side.

## Bootloader <!-- omit from toc -->

Enter the bootloader in 3 ways:

- **Bootmagic reset** (works after you have flashed once): Hold down the top far corner key while plugging in the keyboard (`~` left half, `-` right half). This will also clear the EEPROM.
- **Physical reset button**: Hold the `BOOT` button on the Pico and press the `RST` button on the Pico, release the the `RST` button before the `BOOT` button.
- **Keycode in layout**: In the default layout, the `Bootloader` keycode is above home row pinky on the right side's adjust layer.

Once you enter the bootloader, the keyboard will show up as a USB device on your computer, you could drag and drop a firmware file to flash it, but I recommend using the flash commands for the respective side.

## Junco Sync <!-- omit from toc -->

Junco has a special feature called Junco Sync that will automatically save and sync certain data between the halves of the split. This means that no matter which side you plug in, whenever you change your default layer in a keymap with `DF(layer)`, change your RGB settings with `RGB_***` keycodes, or use one of the `MAGIC_***` keycodes, the data will be saved to EEPROM and synced to the other half of the keyboard. If you choose to plug the other half into a computer, your settings will be the same.

Also, if you ever clear the EEPROM with `EE_CLR` or reboot with `QK_RBT` on one half, the other half will automatically do the same.

To enable Junco Sync in your firmware, uncomment `#define JUNCO_SYNC_ENABLE` in your `config.h` so it looks like this:

```c
/*  - Junco Sync -
    Enables a special feature that will sync
    data between the halves of the split keyboard.
    So no matter which side you plug in, your
    default layer, RGB settings, and any changes made
    via the Magic keycodes will be the same.
*/
#define JUNCO_SYNC_ENABLE

// ... Rest of config.h ...
```

Junco Sync will do its thing by default, but you can disable it at any time without having to re-compile your firmware. `junco_sync_disable()` will disable syncing and `junco_sync_enable()` will re-enable syncing (these settings will sync and persist between sides). Clearing EEPROM will re-enable Junco Sync since it's enabled by default. `is_junco_sync_enabled()` will tell you whether or not Junco Sync is enabled.

### Junco Sync - Advanced <!-- omit from toc -->

- [Settings](#settings)
- [Syncing User Data](#syncing-user-data)
- [Manually Trigger a Sync](#manually-trigger-a-sync)
- [Extras](#extras)

#### Settings

There is a couple of settings for Junco Sync that you can define in your `config.h`. They are:

- The time between syncs. This is to prevent syncs from happening back to back and/or retries happening too quickly, reducing keyboard responsiveness. The default by not defining anything is 1 second, but you can change it by defining `JUNCO_SYNC_THROTTLE` in your `config.h`.
- The number of retries a sync will attempt before giving up. The default is 10, but you can change it by defining `JUNCO_SYNC_RETRIES` in your `config.h`.

```c
    #define JUNCO_SYNC_THROTTLE 1000 // Throttle to 1 second (already default)
    #define JUNCO_SYNC_RETRIES 10 // Allow up to 10 retries (already default)
```

Both of these settings have very sane defaults so there is not really a benefit to defining them. Syncs shouldn't decrease responsiveness at all during normal keyboard use since. They are only triggered after pressing keys that have an effect on EEPROM, which shouldn't happen during normal typing or gaming.

If for some reason you're having issues with syncs not working, you can try increasing the number of retries, but you should probably check if your TRRS cable or TRRS jack soldering job is the problem.

#### Syncing User Data

You can sync your own "user level" data between the halves, see [QMK's documentation](https://docs.qmk.fm/#/feature_eeprom) on the subject. To enable syncing of user data between the halves, set `user_config_raw_ptr` to your config's `raw` value in the `keyboard_post_init_user` after reading the config from EEPROM. For example:

```c
void keyboard_post_init_user(void) {
    // Read your config from EEPROM
    user_config.raw = eeconfig_read_user();
    // Set the pointer to your config's raw value
    user_config_raw_ptr = &user_config.raw;

    /* ... do stuff ... */
}
```

To sync your user data between the halves you can do:

```c
// Update your config
user_config.my_setting = 123;
// Trigger sync
kb_needs_sync = true;
```

The sync will save your config to both side's EEPROM so you so don't have to call `eeconfig_update_user(user_config.raw)` yourself.

For more info, see the next section about manually triggering a sync.

#### Manually Trigger a Sync

You can trigger sync updates manually by setting a flag in your `keymap.c`. You would want to do this if you are updating the default layer, magic settings, RGB, or rebooting / clearing EEPROM within `process_record_user`.

With Junco Sync...

- Magic settigs (`keymap_config`) will only be synced if a `MAGIC_***` keycode is pressed and not overridden by the user.
- Default layer will only become persistent and sync if a `DF(layer)` keycode is pressed.
- RGB will only be synced if a `RGB_***` keycode is pressed and not overridden by the user.
- Synced reboot and clear eeprom only happens when `QK_RBT` or `EE_CLR` is pressed and not overridden by the user.
- Custom user data between the halves won't be synced automatically, it won't know whenuser data needs to be synced.

Triggering a sync is as simple as setting the respective flag to true. For example:

*Don't worry if your IDE complains about any values being undefined, they will be defined if you have `#defne JUNCO_SYNC_ENABLE` in your config.h and your firmware should still compile.*

```c
/* Trigger a sync */
// Syncs keymap_config ("Magic" settings), 
// keyboard level config, default layer, and
// user level config (if you have set user_config_raw_ptr)
kb_needs_sync = true;

// Trigger a RGB sync
kb_needs_rgb_sync = true;

// Trigger a reboot and optionally an EEPROM clear
// .reset needs to be true even when you want to
// just clear EEPROM
kb_needs_reset = {
    .reset = true, // True will trigger a reboot
    .eeprom = true // True will clear EEPROM before rebooting
};
```

Once you have set a flag, the keyboard will carry out the action on it's own and set the flag back to false when it's complete. No need to worry about clearing the flags yourself.

If for some reason your sync isn't working, try setting the flag on the key's release instead of press.

#### Extras

- You can directly call Junco Sync functions by including the `junco_sync.h` header file in your `keymap.c`.
  - Even after calling `junco_sync_disable()`, you can still manually sync data between the halves by calling Junco Sync functions directly within your `housekeeping_task_user`. `junco.c` can give you some ideas on how to do this.
- All of the Junco Sync's functions are weakly defined so you can override them if you really want to.
