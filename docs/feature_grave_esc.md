# Grave Escape

If you're using a 60% keyboard, or any other layout with no F-row, you will have noticed that there is no dedicated Escape key. 
Grave Escape is a feature that allows you to share the grave key (<code>&#96;</code> and `~`) with Escape.

## Usage

Replace the `KC_GRAVE` key in your keymap (usually to the left of the `1` key) with `KC_GESC`. 
When pressed it will behave like `KC_ESC`, but with Shift or GUI held it will send `KC_GRAVE`.

## Keycodes

| Key       | Aliases     | Description                                                        |
|-----------|-------------|--------------------------------------------------------------------|
| `KC_GESC` | `GRAVE_ESC` | Escape when pressed, <code>&#96;</code> when Shift or GUI are held |

## Configuration

### Overrides

There are several possible key combinations this will break, among them Control + Shift + Escape on Windows 
and Command + Option + Escape on macOS. 
To work around this, you can `#define` these options in your `config.h`:

| Define                     | Default       | Description                              |
|----------------------------|---------------|------------------------------------------|
| `GRAVE_ESC_ALT_OVERRIDE`   | *Not defined* | Always send Escape if Alt is pressed     |
| `GRAVE_ESC_CTRL_OVERRIDE`  | *Not defined* | Always send Escape if Control is pressed |
| `GRAVE_ESC_GUI_OVERRIDE`   | *Not defined* | Always send Escape if GUI is pressed     |
| `GRAVE_ESC_SHIFT_OVERRIDE` | *Not defined* | Always send Escape if Shift is pressed   |

### Ignore mods

Also you can customize ignore mod combination. It assumes these situations:

* left Shift uses for `~` ( Shift +  <code>&#96;</code>, it is normal behavior ), but right Shift want to use <code>&#96;</code>
* want to send just <code>&#96;</code> , when pressed GUI + `KC_GESC`
    * depend on enviroment, it will be sent GUI + <code>&#96;</code> message
* apply above both sides

They provided these options, add `#define` in your `(keymap|keyboard)/config.h`.

| Define                    | Default       | Description                                                                                                              |
|---------------------------|---------------|--------------------------------------------------------------------------------------------------------------------------|
| `GESC_GR_IGNORED_MOD`     | *Not defined* | when defined mod keycode, will be passed mod when pressed <code>&#96;</code>, if mod is enabled                          |
| `GESC_GR_IGNORED_MOD_BIT` | *Not defined* | when defined mod bit, will be passed correspond mods when pressed <code>&#96;</code>, if any correspond mods are enabled |


#### example

* passed left Shift
    * `#define GESC_GR_IGNORED_MOD KC_LSFT`
* passed both GUI
    * `#define GESC_GR_IGNORED_MOD_BIT ( MOD_BIT( KC_LGUI ) | MOD_BIT( KC_RGUI ) )`
