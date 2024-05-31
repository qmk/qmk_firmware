# QMK Syllabus

This page helps you build up your QMK knowledge by introducing the basics first and guiding you to understanding all the concepts you need to know to be proficient with QMK.

# Beginning Topics

If you read nothing else you should read the documents in this section. After reading the [Tutorial](newbs) you should be able to create a basic keymap, compile it, and flash it to your keyboard. The remaining documents will flesh out your knowledge of these basics.

* **Learn How To Use QMK Tools**
    * [Tutorial](newbs)
    * [CLI](cli)
    * [GIT](newbs_git_best_practices)
* **Learn About Keymaps**
    * [Layers](feature_layers)
    * [Keycodes](keycodes)
        * The full list of keycodes you can use. Note that some may require knowledge found in the Intermediate or Advanced Topics.
* **Configuring IDEs** - Optional
    * [Eclipse](other_eclipse)
    * [VS Code](other_vscode)

# Intermediate Topics

These topics start to dig into some of the features that QMK supports. You don't have to read all of these documents, but some of the documents in the Advanced Topics section won't make sense if you skip over some of these.

* **Learn How To Configure Features**
    <!-- * Configuration Overview  FIXME(skullydazed/anyone): write this document -->
    * [Audio](feature_audio)
    * Lighting
        * [Backlight](feature_backlight)
        * [LED Matrix](feature_led_matrix)
        * [RGB Lighting](feature_rgblight)
        * [RGB Matrix](feature_rgb_matrix)
    * [Tap-Hold Configuration](tap_hold)
    * [Squeezing Space from AVR](squeezing_avr)
* **Learn More About Keymaps**
    * [Keymaps](keymap)
    * [Custom Functions and Keycodes](custom_quantum_functions)
    * Macros
        * [Dynamic Macros](feature_dynamic_macros)
        * [Compiled Macros](feature_macros)
    * [Tap Dance](feature_tap_dance)
    * [Combos](feature_combo)
    * [Userspace](feature_userspace)
    * [Key Overrides](feature_key_overrides)

# Advanced Topics

Everything below here requires a lot of foundational knowledge. Besides being able to create keymaps using advanced features you should be familiar with using both `config.h` and `rules.mk` to configure options for your keyboard.

* **Maintaining Keyboards Within QMK**
    * [Handwiring a Keyboard](hand_wire)
    * [Keyboard Guidelines](hardware_keyboard_guidelines)
    * [info.json Reference](reference_info_json)
    * [Debounce API](feature_debounce_type)
* **Advanced Features**
    * [Unicode](feature_unicode)
    * [API](api_overview)
    * [Bootmagic Lite](feature_bootmagic)
* **Hardware**
    * [How Keyboards Work](how_keyboards_work)
    * [How A Keyboard Matrix Works](how_a_matrix_works)
    * [Split Keyboards](feature_split_keyboard)
    * [Stenography](feature_stenography)
    * [Pointing Devices](feature_pointing_device)
* **Core Development**
    * [Coding Conventions](coding_conventions_c)
    * [Compatible Microcontrollers](compatible_microcontrollers)
    * [Custom Matrix](custom_matrix)
    * [Understanding QMK](understanding_qmk)
* **CLI Development**
    * [Coding Conventions](coding_conventions_python)
    * [CLI Development Overview](cli_development)
