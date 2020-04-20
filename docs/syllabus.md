# QMK Syllabus

This page helps you build up your QMK knowledge by introducing the basics first and guiding you to understanding all the concepts you need to know to be proficient with QMK.

# Beginning Topics

If you read nothing else you should read the documents in this section. After reading the [Tutorial](newbs.md) you should be able to create a basic keymap, complie it, and flash it to your keyboard. The remaining documents will flesh out your knowledge of these basics.

* **Learn How To Use QMK Tools**
    * [Tutorial](newbs.md)
    * [CLI](cli.md)
    * [GIT](newbs_git_best_practices.md)
* **Learn About Keymaps**
    * [Layers](feature_layers.md)
    * [Keycodes](keycodes.md)
        * The full list of keycodes you can use. Note that some may require knowledge found in the Intermediate or Advanced Topics.
* **Configuring IDEs** - Optional
    * [Eclipse](other_eclipse.md)
    * [VSCode](other_vscode.md)

# Intermediate Topics

These topics start dig into some of the features that QMK supports. You don't have to read all of these documents, but some of the documents in the Advanced Topics section won't make sense if you skip over some of these.

* **Learn How To Configure Features**
    <!-- * Configuration Overview  FIXME(skullydazed/anyone): write this document -->
    * [Audio](feature_audio.md)
    * Lighting
        * [Backlight](feature_backlight.md)
        * [LED Matrix](feature_led_matrix.md)
        * [RGB Lighting](feature_rgblight.md)
        * [RGB Matrix](feature_rgb_matrix.md)
    * [Tap-Hold Configuration](tap_hold.md)
* **Learn More About Keymaps**
    * [Keymaps](keymap.md)
    * [Custom Functions and Keycodes](custom_quantum_functions.md)
    * Macros
        * [Dynamic Macros](feature_dynamic_macros.md)
        * [Compiled Macros](feature_macros.md)
    * [Tap Dance](feature_tap_dance.md)
    * [Combos](feature_combo.md)
    * [Userspace](feature_userspace.md)

# Advanced Topics

Everything below here requires a lot of foundational knowledge. Besides being able to create keymaps using advanced features you should be familiar with using both `config.h` and `rules.mk` to configure options for your keyboard.

* **Maintaining Keyboards Within QMK**
    * [Handwiring a Keyboard](hand_wire.md)
    * [Keyboard Guidelines](hardware_keyboard_guidelines.md)
    * [info.json Reference](reference_info_json.md)
    * [Debounce API](feature_debounce_type.md)
* **Advanced Features**
    * [Unicode](feature_unicode.md)
    * [API](api_overview.md)
    * [Bootmagic](feature_bootmagic.md)
* **Hardware**
    * [How Keyboards Work](how_keyboards_work.md)
    * [How A Keyboard Matrix Works](how_a_matrix_works.md)
    * [Split Keyboards](feature_split_keyboard.md)
    * [Stenography](feature_stenography.md)
    * [Pointing Devices](feature_pointing_device.md)
* **Core Development**
    * [Coding Conventions](coding_conventions_c.md)
    * [Compatible Microcontrolers](compatible_microcontrollers.md)
    * [Custom Matrix](custom_matrix.md)
    * [Understandnig QMK](understanding_qmk.md)
* **CLI Development**
    * [Coding Conventions](coding_conventions_python.md)
    * [CLI Development Overview](cli_development.md)
