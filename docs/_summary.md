* Tutorial
  * [Introduction](newbs.md)
  * [Setup](newbs_getting_started.md)
  * [Building Your First Firmware](newbs_building_firmware.md)
  * [Flashing Firmware](newbs_flashing.md)
  * [Getting Help/Support](support.md)
  * [Other Resources](newbs_learn_more_resources.md)
  * [Syllabus](syllabus.md)

* FAQs
  * [General FAQ](faq_general.md)
  * [Build/Compile QMK](faq_build.md)
  * [Troubleshooting QMK](faq_misc.md)
  * [Debugging QMK](faq_debug.md)
  * [Keymap FAQ](faq_keymap.md)
  * [Glossary](reference_glossary.md)

* Configurator
  * [Overview](newbs_building_firmware_configurator.md)
  * [Step by Step](configurator_step_by_step.md)
  * [Troubleshooting](configurator_troubleshooting.md)
  * QMK API
    * [Overview](api_overview.md)
    * [API Documentation](api_docs.md)
    * [Keyboard Support](reference_configurator_support.md)
    * [Adding Default Keymaps](configurator_default_keymaps.md)

* CLI
    * [Overview](cli.md)
    * [Configuration](cli_configuration.md)
    * [Commands](cli_commands.md)

* Using QMK
  * Guides
    * [Customizing Functionality](custom_quantum_functions.md)
    * [Driver Installation with Zadig](driver_installation_zadig.md)
    * [Keymap Overview](keymap.md)
    * Development Environments
      * [Docker Guide](getting_started_docker.md)
      * [Vagrant Guide](getting_started_vagrant.md)
    * Flashing
      * [Flashing](flashing.md)
      * [Flashing ATmega32A (ps2avrgb)](flashing_bootloadhid.md)
    * IDEs
      * [Using Eclipse with QMK](other_eclipse.md)
      * [Using VSCode with QMK](other_vscode.md)
    * Git Best Practices
      * [Introduction](newbs_git_best_practices.md)
      * [Your Fork](newbs_git_using_your_master_branch.md)
      * [Merge Conflicts](newbs_git_resolving_merge_conflicts.md)
      * [Fixing Your Branch](newbs_git_resynchronize_a_branch.md)
    * Keyboard Building
      * [Hand Wiring Guide](hand_wire.md)
      * [ISP Flashing Guide](isp_flashing_guide.md)

  * Simple Keycodes
    * [Full List](keycodes.md)
    * [Basic Keycodes](keycodes_basic.md)
    * [Language-Specific Keycodes](reference_keymap_extras.md)
    * [Modifier Keys](feature_advanced_keycodes.md)
    * [Quantum Keycodes](quantum_keycodes.md)

  * Advanced Keycodes
    * [Command](feature_command.md)
    * [Dynamic Macros](feature_dynamic_macros.md)
    * [Grave Escape](feature_grave_esc.md)
    * [Leader Key](feature_leader_key.md)
    * [Mod-Tap](mod_tap.md)
    * [Macros](feature_macros.md)
    * [Mouse Keys](feature_mouse_keys.md)
    * [Space Cadet Shift](feature_space_cadet.md)
    * [US ANSI Shifted Keys](keycodes_us_ansi_shifted.md)

  * Software Features
    * [Auto Shift](feature_auto_shift.md)
    * [Combos](feature_combo.md)
    * [Debounce API](feature_debounce_type.md)
    * [Key Lock](feature_key_lock.md)
    * [Layers](feature_layers.md)
    * [One Shot Keys](one_shot_keys.md)
    * [Pointing Device](feature_pointing_device.md)
    * [Raw HID](feature_rawhid.md)
    * [Sequencer](feature_sequencer.md)
    * [Swap Hands](feature_swap_hands.md)
    * [Tap Dance](feature_tap_dance.md)
    * [Tap-Hold Configuration](tap_hold.md)
    * [Terminal](feature_terminal.md)
    * [Unicode](feature_unicode.md)
    * [Userspace](feature_userspace.md)
    * [WPM Calculation](feature_wpm.md)

  * Hardware Features
    * Displays
      * [HD44780 LCD Controller](feature_hd44780.md)
      * [OLED Driver](feature_oled_driver.md)
    * Lighting
      * [Backlight](feature_backlight.md)
      * [LED Matrix](feature_led_matrix.md)
      * [RGB Lighting](feature_rgblight.md)
      * [RGB Matrix](feature_rgb_matrix.md)
    * [Audio](feature_audio.md)
    * [Bluetooth](feature_bluetooth.md)
    * [Bootmagic](feature_bootmagic.md)
    * [Custom Matrix](custom_matrix.md)
    * [DIP Switch](feature_dip_switch.md)
    * [Encoders](feature_encoders.md)
    * [Haptic Feedback](feature_haptic_feedback.md)
    * [Joystick](feature_joystick.md)
    * [LED Indicators](feature_led_indicators.md)
    * [Proton C Conversion](proton_c_conversion.md)
    * [PS/2 Mouse](feature_ps2_mouse.md)
    * [Split Keyboard](feature_split_keyboard.md)
    * [Stenography](feature_stenography.md)
    * [Thermal Printer](feature_thermal_printer.md)
    * [Velocikey](feature_velocikey.md)

* Developing QMK
  * [PR Checklist](pr_checklist.md)
  * Breaking Changes
    * [Overview](breaking_changes.md)
    * [My Pull Request Was Flagged](breaking_changes_instructions.md)
    * [Most Recent ChangeLog](ChangeLog/20210227.md "QMK v0.12.0 - 2021 Feb 27")
    * [Past Breaking Changes](breaking_changes_history.md)

  * C Development
    * [ARM Debugging Guide](arm_debugging.md)
    * [AVR Processors](hardware_avr.md)
    * [Coding Conventions](coding_conventions_c.md)
    * [Compatible Microcontrollers](compatible_microcontrollers.md)
    * [Drivers](hardware_drivers.md)
      * [ADC Driver](adc_driver.md)
      * [Audio Driver](audio_driver.md)
      * [I2C Driver](i2c_driver.md)
      * [SPI Driver](spi_driver.md)
      * [WS2812 Driver](ws2812_driver.md)
      * [EEPROM Driver](eeprom_driver.md)
      * ['serial' Driver](serial_driver.md)
      * [UART Driver](uart_driver.md)
    * [GPIO Controls](internals_gpio_control.md)
    * [Keyboard Guidelines](hardware_keyboard_guidelines.md)

  * Python Development
    * [Coding Conventions](coding_conventions_python.md)
    * [QMK CLI Development](cli_development.md)

  * Configurator Development
    * QMK API
      * [Development Environment](api_development_environment.md)
      * [Architecture Overview](api_development_overview.md)

  * Hardware Platform Development
    * Arm/ChibiOS
      * [Selecting an MCU](platformdev_selecting_arm_mcu.md)
      * [Early initialization](platformdev_chibios_earlyinit.md)

  * QMK Reference
    * [Contributing to QMK](contributing.md)
    * [Translating the QMK Docs](translating.md)
    * [Config Options](config_options.md)
    * [Data Driven Configuration](data_driven_config.md)
    * [Make Documentation](getting_started_make_guide.md)
    * [Documentation Best Practices](documentation_best_practices.md)
    * [Documentation Templates](documentation_templates.md)
    * [Community Layouts](feature_layouts.md)
    * [Unit Testing](unit_testing.md)
    * [Useful Functions](ref_functions.md)
    * [info.json Format](reference_info_json.md)

  * For a Deeper Understanding
    * [How Keyboards Work](how_keyboards_work.md)
    * [How a Matrix Works](how_a_matrix_works.md)
    * [Understanding QMK](understanding_qmk.md)

  * QMK Internals (In Progress)
    * [Defines](internals_defines.md)
    * [Input Callback Reg](internals_input_callback_reg.md)
    * [Midi Device](internals_midi_device.md)
    * [Midi Device Setup Process](internals_midi_device_setup_process.md)
    * [Midi Util](internals_midi_util.md)
    * [Send Functions](internals_send_functions.md)
    * [Sysex Tools](internals_sysex_tools.md)
