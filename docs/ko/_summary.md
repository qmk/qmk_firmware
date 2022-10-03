* 튜토리얼
  * [소개](ko/newbs.md)
  * [설정](ko/newbs_getting_started.md)
  * [첫 펌웨어 빌드](ko/newbs_building_firmware.md)
  * [펌웨어 플래시](ko/newbs_flashing.md)
  * [도움/지원 받기](ko/support.md)
  * [다른 리소스들](ko/newbs_learn_more_resources.md)
  * [계획서](ko/syllabus.md)

* FAQs
  * [General FAQ](ko/faq_general.md)
  * [Build/Compile QMK](ko/faq_build.md)
  * [Troubleshooting QMK](ko/faq_misc.md)
  * [Debugging QMK](ko/faq_debug.md)
  * [Keymap FAQ](ko/faq_keymap.md)
  * [Squeezing Space from AVR](ko/squeezing_avr.md)
  * [Glossary](ko/reference_glossary.md)

* Configurator
  * [개요](ko/newbs_building_firmware_configurator.md)
  * [Step by Step](ko/configurator_step_by_step.md)
  * [Troubleshooting](ko/configurator_troubleshooting.md)
  * [아키텍처](ko/configurator_architecture.md)
  * QMK API
    * [개요](ko/api_overview.md)
    * [API 문서](ko/api_docs.md)
    * [키보드 지원](ko/reference_configurator_support.md)
    * [기본 키맵 추가하기](ko/configurator_default_keymaps.md)

* CLI
    * [Overview](ko/cli.md)
    * [Configuration](ko/cli_configuration.md)
    * [Commands](ko/cli_commands.md)
    * [Tab Completion](ko/cli_tab_complete.md)

* Using QMK
  * Guides
    * [Customizing Functionality](ko/custom_quantum_functions.md)
    * [Driver Installation with Zadig](ko/driver_installation_zadig.md)
    * [Keymap Overview](ko/keymap.md)
    * Development Environments
      * [Docker Guide](ko/getting_started_docker.md)
      * [Vagrant Guide](ko/getting_started_vagrant.md)
    * Flashing
      * [Flashing](ko/flashing.md)
      * [Flashing ATmega32A (ps2avrgb)](ko/flashing_bootloadhid.md)
    * IDEs
      * [Using Eclipse with QMK](ko/other_eclipse.md)
      * [Using VSCode with QMK](ko/other_vscode.md)
    * Git Best Practices
      * [Introduction](ko/newbs_git_best_practices.md)
      * [Your Fork](ko/newbs_git_using_your_master_branch.md)
      * [Merge Conflicts](ko/newbs_git_resolving_merge_conflicts.md)
      * [Fixing Your Branch](ko/newbs_git_resynchronize_a_branch.md)

  * Simple Keycodes
    * [Full List](ko/keycodes.md)
    * [Basic Keycodes](ko/keycodes_basic.md)
    * [Language-Specific Keycodes](ko/reference_keymap_extras.md)
    * [Modifier Keys](ko/feature_advanced_keycodes.md)
    * [Quantum Keycodes](ko/quantum_keycodes.md)
    * [Magic Keycodes](ko/keycodes_magic.md)

  * Advanced Keycodes
    * [Command](ko/feature_command.md)
    * [Dynamic Macros](ko/feature_dynamic_macros.md)
    * [Grave Escape](ko/feature_grave_esc.md)
    * [Leader Key](ko/feature_leader_key.md)
    * [Mod-Tap](ko/mod_tap.md)
    * [Macros](ko/feature_macros.md)
    * [Mouse Keys](ko/feature_mouse_keys.md)
    * [Programmable Button](ko/feature_programmable_button.md)
    * [Space Cadet Shift](ko/feature_space_cadet.md)
    * [US ANSI Shifted Keys](ko/keycodes_us_ansi_shifted.md)

  * Software Features
    * [Auto Shift](ko/feature_auto_shift.md)
    * [Combos](ko/feature_combo.md)
    * [Debounce API](ko/feature_debounce_type.md)
    * [Key Lock](ko/feature_key_lock.md)
    * [Key Overrides](ko/feature_key_overrides.md)
    * [Layers](ko/feature_layers.md)
    * [One Shot Keys](ko/one_shot_keys.md)
    * [Pointing Device](ko/feature_pointing_device.md)
    * [Raw HID](ko/feature_rawhid.md)
    * [Sequencer](ko/feature_sequencer.md)
    * [Swap Hands](ko/feature_swap_hands.md)
    * [Tap Dance](ko/feature_tap_dance.md)
    * [Tap-Hold Configuration](ko/tap_hold.md)
    * [Terminal](ko/feature_terminal.md)
    * [Unicode](ko/feature_unicode.md)
    * [Userspace](ko/feature_userspace.md)
    * [WPM Calculation](ko/feature_wpm.md)

  * Hardware Features
    * Displays
      * [HD44780 LCD Controller](ko/feature_hd44780.md)
      * [ST7565 LCD Driver](ko/feature_st7565.md)
      * [OLED Driver](ko/feature_oled_driver.md)
    * Lighting
      * [Backlight](ko/feature_backlight.md)
      * [LED Matrix](ko/feature_led_matrix.md)
      * [RGB Lighting](ko/feature_rgblight.md)
      * [RGB Matrix](ko/feature_rgb_matrix.md)
    * [Audio](ko/feature_audio.md)
    * [Bluetooth](ko/feature_bluetooth.md)
    * [Bootmagic Lite](ko/feature_bootmagic.md)
    * [Custom Matrix](ko/custom_matrix.md)
    * [Digitizer](ko/feature_digitizer.md)
    * [DIP Switch](ko/feature_dip_switch.md)
    * [Encoders](ko/feature_encoders.md)
    * [Haptic Feedback](ko/feature_haptic_feedback.md)
    * [Joystick](ko/feature_joystick.md)
    * [LED Indicators](ko/feature_led_indicators.md)
    * [MIDI](ko/feature_midi.md)
    * [Proton C Conversion](ko/proton_c_conversion.md)
    * [PS/2 Mouse](ko/feature_ps2_mouse.md)
    * [Split Keyboard](ko/feature_split_keyboard.md)
    * [Stenography](ko/feature_stenography.md)
    * [Thermal Printer](ko/feature_thermal_printer.md)
    * [Velocikey](ko/feature_velocikey.md)

  * Keyboard Building
    * [Easy Maker for One Offs](ko/easy_maker.md)
    * [Porting Keyboards](ko/porting_your_keyboard_to_qmk.md)
    * [Hand Wiring Guide](ko/hand_wire.md)
    * [ISP Flashing Guide](ko/isp_flashing_guide.md)

* Developing QMK
  * [PR Checklist](ko/pr_checklist.md)
  * Breaking Changes
    * [Overview](ko/breaking_changes.md)
    * [My Pull Request Was Flagged](ko/breaking_changes_instructions.md)
    * [Most Recent ChangeLog](ko/ChangeLog/20220226.md "QMK v0.16.0 - 2022 Feb 26")
    * [Past Breaking Changes](ko/breaking_changes_history.md)

  * C Development
    * [ARM Debugging Guide](ko/arm_debugging.md)
    * [Coding Conventions](ko/coding_conventions_c.md)
    * [Compatible Microcontrollers](ko/compatible_microcontrollers.md)
    * [Drivers](ko/hardware_drivers.md)
      * [ADC Driver](ko/adc_driver.md)
      * [Audio Driver](ko/audio_driver.md)
      * [I2C Driver](ko/i2c_driver.md)
      * [SPI Driver](ko/spi_driver.md)
      * [WS2812 Driver](ko/ws2812_driver.md)
      * [EEPROM Driver](ko/eeprom_driver.md)
      * ['serial' Driver](ko/serial_driver.md)
      * [UART Driver](ko/uart_driver.md)
    * [GPIO Controls](ko/internals_gpio_control.md)
    * [Keyboard Guidelines](ko/hardware_keyboard_guidelines.md)

  * Python Development
    * [Coding Conventions](ko/coding_conventions_python.md)
    * [QMK CLI Development](ko/cli_development.md)

  * Configurator Development
    * QMK API
      * [Development Environment](ko/api_development_environment.md)
      * [Architecture Overview](ko/api_development_overview.md)

  * Hardware Platform Development
    * Arm/ChibiOS
      * [Selecting an MCU](ko/platformdev_selecting_arm_mcu.md)
      * [Early initialization](ko/platformdev_chibios_earlyinit.md)

  * QMK Reference
    * [Contributing to QMK](ko/contributing.md)
    * [QMK 문서 번역](ko/translating.md)
    * [Config Options](ko/config_options.md)
    * [Data Driven Configuration](ko/data_driven_config.md)
    * [Make Documentation](ko/getting_started_make_guide.md)
    * [Documentation Best Practices](ko/documentation_best_practices.md)
    * [Documentation Templates](ko/documentation_templates.md)
    * [Community Layouts](ko/feature_layouts.md)
    * [Unit Testing](ko/unit_testing.md)
    * [Useful Functions](ko/ref_functions.md)
    * [info.json Format](ko/reference_info_json.md)

  * For a Deeper Understanding
    * [How Keyboards Work](ko/how_keyboards_work.md)
    * [How a Matrix Works](ko/how_a_matrix_works.md)
    * [Understanding QMK](ko/understanding_qmk.md)

  * QMK Internals (ko/In Progress)
    * [Defines](ko/internals_defines.md)
    * [Input Callback Reg](ko/internals_input_callback_reg.md)
    * [Midi Device](ko/internals_midi_device.md)
    * [Midi Device Setup Process](ko/internals_midi_device_setup_process.md)
    * [Midi Util](ko/internals_midi_util.md)
    * [Send Functions](ko/internals_send_functions.md)
    * [Sysex Tools](ko/internals_sysex_tools.md)
