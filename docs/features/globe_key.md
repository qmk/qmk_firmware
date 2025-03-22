# Apple Globe/Fn

With the release of the iPad Pro 2nd generation and its smart keyboard, in 2017, Apple introduced a the Globe key which was used to change the keyboard language. The key found its way in the keyboards of the M-series of laptop and desktop computers as a complement to the Fn-key.

This key is only compatible with Apple devices and can be used as a modifier and as a standalone key. As a standalone key, it opens an emoji menu (though this can be configured in settings) and as a modifier, the key can be used to control macOS windows.

## Usage

The QMK partially supports the Globe key, see Caveats below by providing the keycode `KC_GLOBE` which can be used in your keymap, it requires the option `KEYBOARD_SHARE_EP` to be set to `yes` in your `rules.mk`, or by having `usb.shared_endpoint.keyboard=true` in `keyboard.json`.

## Keycodes

| Key        | Aliases  | Description                                   |
| ---------- | -------- | --------------------------------------------- |
| `KC_GLOBE` | `KC_GLB` | Apple Globe/Fn as standalone and modifier key |

### Caveats

When used as a modified, the Globe key is only partially supported by QMK. Here is the status of the known combination and whether they work with macOS (default settings):

| Combination with the Globe key | Status | Description                                     |
| ------------------------------ | ------ | ----------------------------------------------- |
| Alone                          | op     | Show the emoji dialog (can be changed in setup) |
| `^🌐C`                         | op     | Center window in screen                         |
| `^🌐F`                         | op     | Fill screen                                     |
| `^🌐R`                         | op     | Return to previous size                         |
| `🌐+Arrows` or `^🌐+Arrows`    | nop    | No effect including with other modifiers        |
| `🌐A`                          | op     | Hide/unhide the Apple dock                      |
| `🌐C`                          | op     | Control center                                  |
| `🌐E`                          | op     | Inovkes the emoji menu                          |
| `🌐F`                          | op     | Full screen mode toggle                         |
| `🌐H`                          | op     | Toggle Desktop                                  |
| `🌐N`                          | op     | Toggle Notifications                            |
| `🌐Q`                          | op     | Invokes quite note                              |

`op` operate / `nop` does not operate
