* Tutorial
  * [Introduction](newbs)
  * [Setup](newbs_getting_started)
  * [Building Your First Firmware](newbs_building_firmware)
  * [Flashing Firmware](newbs_flashing)
  * [Getting Help/Support](support)
  * [External Userspace](newbs_external_userspace)
  * [Other Resources](newbs_learn_more_resources)
  * [Syllabus](syllabus)

* FAQs
  * [General FAQ](faq_general)
  * [Build/Compile QMK](faq_build)
  * [Troubleshooting QMK](faq_misc)
  * [Debugging QMK](faq_debug)
  * [Keymap FAQ](faq_keymap)
  * [Squeezing Space from AVR](squeezing_avr)
  * [Glossary](reference_glossary)

* Configurator
  * [Overview](newbs_building_firmware_configurator)
  * [Step by Step](configurator_step_by_step)
  * [Troubleshooting](configurator_troubleshooting)
  * [Architecture](configurator_architecture)
  * QMK API
    * [Overview](api_overview)
    * [API Documentation](api_docs)
    * [Keyboard Support](reference_configurator_support)
    * [Adding Default Keymaps](configurator_default_keymaps)

* CLI
    * [Overview](cli)
    * [Configuration](cli_configuration)
    * [Commands](cli_commands)
    * [Tab Completion](cli_tab_complete)

* Using QMK
  * Guides
    * [Customizing Functionality](custom_quantum_functions)
    * [Driver Installation with Zadig](driver_installation_zadig)
    * [Keymap Overview](keymap)
    * Development Environments
      * [Docker Guide](getting_started_docker)
    * Flashing
      * [Flashing](flashing)
      * [Flashing ATmega32A (ps2avrgb)](flashing_bootloadhid.md)
    * IDEs
      * [Using Eclipse with QMK](other_eclipse)
      * [Using VSCode with QMK](other_vscode)
    * Git Best Practices
      * [Introduction](newbs_git_best_practices)
      * [Your Fork](newbs_git_using_your_master_branch)
      * [Merge Conflicts](newbs_git_resolving_merge_conflicts)
      * [Fixing Your Branch](newbs_git_resynchronize_a_branch)

  * Simple Keycodes
    * [Full List](keycodes)
    * [Basic Keycodes](keycodes_basic)
    * [Language-Specific Keycodes](reference_keymap_extras)
    * [Modifier Keys](feature_advanced_keycodes)
    * [Quantum Keycodes](quantum_keycodes)
    * [Magic Keycodes](keycodes_magic)

  * Advanced Keycodes
    * [Command](feature_command)
    * [Dynamic Macros](feature_dynamic_macros)
    * [Grave Escape](feature_grave_esc)
    * [Leader Key](feature_leader_key)
    * [Mod-Tap](mod_tap)
    * [Macros](feature_macros)
    * [Mouse Keys](feature_mouse_keys)
    * [Programmable Button](feature_programmable_button)
    * [Repeat Key](feature_repeat_key)
    * [Space Cadet Shift](feature_space_cadet)
    * [US ANSI Shifted Keys](keycodes_us_ansi_shifted)

  * Software Features
    * [Auto Shift](feature_auto_shift)
    * [Autocorrect](feature_autocorrect)
    * [Caps Word](feature_caps_word)
    * [Combos](feature_combo)
    * [Debounce API](feature_debounce_type)
    * [Digitizer](feature_digitizer)
    * [EEPROM](feature_eeprom)
    * [Key Lock](feature_key_lock)
    * [Key Overrides](feature_key_overrides)
    * [Layers](feature_layers)
    * [One Shot Keys](one_shot_keys)
    * [OS Detection](feature_os_detection)
    * [Raw HID](feature_rawhid)
    * [Secure](feature_secure)
    * [Send String](feature_send_string)
    * [Sequencer](feature_sequencer)
    * [Swap Hands](feature_swap_hands)
    * [Tap Dance](feature_tap_dance)
    * [Tap-Hold Configuration](tap_hold)
    * [Tri Layer](feature_tri_layer)
    * [Unicode](feature_unicode)
    * [Userspace](feature_userspace)
    * [WPM Calculation](feature_wpm)

  * Hardware Features
    * Displays
      * [Quantum Painter](quantum_painter)
        * [Quantum Painter LVGL Integration](quantum_painter_lvgl)
      * [HD44780 LCD Driver](feature_hd44780)
      * [ST7565 LCD Driver](feature_st7565)
      * [OLED Driver](feature_oled_driver)
    * Lighting
      * [Backlight](feature_backlight)
      * [LED Matrix](feature_led_matrix)
      * [RGB Lighting](feature_rgblight)
      * [RGB Matrix](feature_rgb_matrix)
    * [Audio](feature_audio)
    * [Bluetooth](feature_bluetooth)
    * [Bootmagic Lite](feature_bootmagic)
    * [Converters](feature_converters)
    * [Custom Matrix](custom_matrix)
    * [DIP Switch](feature_dip_switch)
    * [Encoders](feature_encoders)
    * [Haptic Feedback](feature_haptic_feedback)
    * [Joystick](feature_joystick)
    * [LED Indicators](feature_led_indicators)
    * [MIDI](feature_midi)
    * [Pointing Device](feature_pointing_device)
    * [PS/2 Mouse](feature_ps2_mouse)
    * [Split Keyboard](feature_split_keyboard)
    * [Stenography](feature_stenography)

  * Keyboard Building
    * [Easy Maker for One Offs](easy_maker)
    * [Porting Keyboards](porting_your_keyboard_to_qmk)
    * [Hand Wiring Guide](hand_wire)
    * [ISP Flashing Guide](isp_flashing_guide)

* Developing QMK
  * [PR Checklist](pr_checklist)
  * Breaking Changes
    * [Overview](breaking_changes)
    * [My Pull Request Was Flagged](breaking_changes_instructions)
    * [Most Recent ChangeLog](ChangeLog/20240225.md "QMK v0.24.0 - 2024 Feb 25")
    * [Past Breaking Changes](breaking_changes_history)

  * C Development
    * [ARM Debugging Guide](arm_debugging)
    * [Coding Conventions](coding_conventions_c)
    * [Compatible Microcontrollers](compatible_microcontrollers)
    * [Drivers](hardware_drivers)
      * [ADC Driver](adc_driver)
      * [APA102 Driver](apa102_driver)
      * [Audio Driver](audio_driver)
      * [I2C Driver](i2c_driver)
      * [SPI Driver](spi_driver)
      * [WS2812 Driver](ws2812_driver)
      * [EEPROM Driver](eeprom_driver)
      * [Flash Driver](flash_driver)
      * ['serial' Driver](serial_driver)
      * [UART Driver](uart_driver)
    * [GPIO Controls](gpio_control)
    * [Keyboard Guidelines](hardware_keyboard_guidelines)

  * Python Development
    * [Coding Conventions](coding_conventions_python)
    * [QMK CLI Development](cli_development)

  * Configurator Development
    * QMK API
      * [Development Environment](api_development_environment)
      * [Architecture Overview](api_development_overview)

  * Hardware Platform Development
    * Arm/ChibiOS
      * [Selecting an MCU](platformdev_selecting_arm_mcu)
      * [Early initialization](platformdev_chibios_earlyinit)
      * [Raspberry Pi RP2040](platformdev_rp2040)
      * [Proton C](platformdev_proton_c)
      * [WeAct Blackpill F4x1](platformdev_blackpill_f4x1)

  * QMK Reference
    * [Contributing to QMK](contributing)
    * [Config Options](config_options)
    * [Data Driven Configuration](data_driven_config)
    * [Make Documentation](getting_started_make_guide)
    * [Documentation Best Practices](documentation_best_practices)
    * [Documentation Templates](documentation_templates)
    * [Community Layouts](feature_layouts)
    * [Unit Testing](unit_testing)
    * [Useful Functions](ref_functions)
    * [info.json Format](reference_info_json)

  * For a Deeper Understanding
    * [How Keyboards Work](how_keyboards_work)
    * [How a Matrix Works](how_a_matrix_works)
    * [Understanding QMK](understanding_qmk)
