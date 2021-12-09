* 教程
  * [导语](zh-cn/newbs.md)
  * [环境设置](zh-cn/newbs_getting_started.md)
  * [构建你的第一个固件](zh-cn/newbs_building_firmware.md)
  * [刷固件](zh-cn/newbs_flashing.md)
  * [支持页](zh-cn/support.md)
  * [学习材料](zh-cn/newbs_learn_more_resources.md)
  * [大纲](zh-cn/syllabus.md)

* 问题与解答
  * [一般问题](zh-cn/faq_general.md)
  * [构建/编译](zh-cn/faq_build.md)
  * [Troubleshooting QMK](zh-cn/faq_misc.md)
  * [调试/故障排除](zh-cn/faq_debug.md)
  * [布局](zh-cn/faq_keymap.md)
  * [Squeezing Space from AVR](zh-cn/squeezing_avr.md)
  * [用语](zh-cn/reference_glossary.md)

* Configurator
  * [Overview](zh-cn/newbs_building_firmware_configurator.md)
  * [Step by Step](zh-cn/configurator_step_by_step.md)
  * [Troubleshooting](zh-cn/configurator_troubleshooting.md)
  * [Architecture](zh-cn/configurator_architecture.md)
  * QMK API
    * [Overview](zh-cn/api_overview.md)
    * [API Documentation](zh-cn/api_docs.md)
    * [键盘支持](zh-cn/reference_configurator_support.md)
    * [Adding Default Keymaps](zh-cn/configurator_default_keymaps.md)

* 命令行工具
    * [总览](zh-cn/cli.md)
    * [QMK命令行工具配置](zh-cn/cli_configuration.md)
    * [QMK命令行工具命令](zh-cn/cli_commands.md)
    * [Tab Completion](zh-cn/cli_tab_complete.md)

* 使用 QMK
  * 教程
    * [定制功能](zh-cn/custom_quantum_functions.md)
    * [Zadig驱动安装](zh-cn/driver_installation_zadig.md)
    * [Easy Maker for One Offs](zh-cn/easy_maker.md)
    * [布局概述](zh-cn/keymap.md)
    * Development Environments
      * [Docker Guide](zh-cn/getting_started_docker.md)
      * [vagrant指南](zh-cn/getting_started_vagrant.md)
    * Flashing
      * [刷固件](zh-cn/flashing.md)
      * [Flashing ATmega32A (ps2avrgb)](zh-cn/flashing_bootloadhid.md)
    * IDE
      * [使用Eclipse开发QMK](zh-cn/other_eclipse.md)
      * [使用VSCode开发QMK](zh-cn/other_vscode.md)
    * Git最佳用法
      * [导语](zh-cn/newbs_git_best_practices.md)
      * [你的fork](zh-cn/newbs_git_using_your_master_branch.md)
      * [解决合并冲突](zh-cn/newbs_git_resolving_merge_conflicts.md)
      * [重新同步一个分支](zh-cn/newbs_git_resynchronize_a_branch.md)
    * 制造键盘
      * [手工连线指南](zh-cn/hand_wire.md)
      * [刷ISP指南](zh-cn/isp_flashing_guide.md)

  * Simple Keycodes
    * [键码](zh-cn/keycodes.md)
    * [基本键码](zh-cn/keycodes_basic.md)
    * [Language-Specific Keycodes](zh-cn/reference_keymap_extras.md)
    * [Modifier Keys](zh-cn/feature_advanced_keycodes.md)
    * [量子键码](zh-cn/quantum_keycodes.md)
    * [Magic Keycodes](zh-cn/keycodes_magic.md)

  * Advanced Keycodes
    * [Command](zh-cn/feature_command.md)
    * [Dynamic Macros](zh-cn/feature_dynamic_macros.md)
    * [Grave Escape](zh-cn/feature_grave_esc.md)
    * [Leader Key](zh-cn/feature_leader_key.md)
    * [Mod-Tap](zh-cn/mod_tap.md)
    * [宏指令](zh-cn/feature_macros.md)
    * [鼠标键](zh-cn/feature_mouse_keys.md)
    * [Programmable Button](zh-cn/feature_programmable_button.md)
    * [Space Cadet Shift](zh-cn/feature_space_cadet.md)
    * [US ANSI Shifted Keys](zh-cn/keycodes_us_ansi_shifted.md)

  * Software Features
    * [自动shift](zh-cn/feature_auto_shift.md)
    * [组合](zh-cn/feature_combo)
    * [去抖动 API](zh-cn/feature_debounce_type.md)
    * [Key Lock](zh-cn/feature_key_lock.md)
    * [Key Overrides](zh-cn/feature_key_overrides.md)
    * [Layers](zh-cn/feature_layers.md)
    * [One Shot Keys](zh-cn/one_shot_keys.md)
    * [Pointing Device](zh-cn/feature_pointing_device.md)
    * [Raw HID](zh-cn/feature_rawhid.md)
    * [Sequencer](zh-cn/feature_sequencer.md)
    * [Swap Hands](zh-cn/feature_swap_hands.md)
    * [Tap Dance](zh-cn/feature_tap_dance.md)
    * [Tap-Hold Configuration](zh-cn/tap_hold.md)
    * [Terminal](zh-cn/feature_terminal.md)
    * [Unicode](zh-cn/feature_unicode.md)
    * [用户空间](zh-cn/feature_userspace.md)
    * [WPM Calculation](zh-cn/feature_wpm.md)

  * 硬件功能
    * 显示器
      * [HD44780 LCD控制器](zh-cn/feature_hd44780.md)
      * [ST7565 LCD Driver](zh-cn/feature_st7565.md)
      * [OLED驱动](zh-cn/feature_oled_driver.md)
    * 照明
      * [背光](zh-cn/feature_backlight.md)
      * [LED阵列](zh-cn/feature_led_matrix.md)
      * [RGB灯光](zh-cn/feature_rgblight.md)
      * [RGB阵列](zh-cn/feature_rgb_matrix.md)
    * [音频](zh-cn/feature_audio.md)
    * [蓝牙](zh-cn/feature_bluetooth.md)
    * [Bootmagic Lite](zh-cn/feature_bootmagic.md)
    * [自定义键盘矩阵](zh-cn/custom_matrix.md)
    * [Digitizer](zh-cn/feature_digitizer.md)
    * [拨动开关](zh-cn/feature_dip_switch.md)
    * [旋钮](zh-cn/feature_encoders.md)
    * [触摸反馈](zh-cn/feature_haptic_feedback.md)
    * [Joystick](zh-cn/feature_joystick.md)
    * [LED Indicators](zh-cn/feature_led_indicators.md)
    * [MIDI](zh-cn/feature_midi.md)
    * [Proton C转换](zh-cn/proton_c_conversion.md)
    * [PS/2鼠标](zh-cn/feature_ps2_mouse.md)
    * [分体键盘](zh-cn/feature_split_keyboard.md)
    * [速录机](zh-cn/feature_stenography.md)
    * [热敏打印机](zh-cn/feature_thermal_printer.md)
    * [Velocikey](zh-cn/feature_velocikey.md)

* Developing QMK
  * [PR Checklist](zh-cn/pr_checklist.md)
  * 非兼容性修改
    * [总览](zh-cn/breaking_changes.md)
    * [我的PR已经被标记为非兼容性修改](zh-cn/breaking_changes_instructions.md)
    * [Most Recent ChangeLog](zh-cn/ChangeLog/20211127.md "QMK v0.15.0 - 2021 Nov 27")
    * [Past Breaking Changes](zh-cn/breaking_changes_history.md)

  * C Development
    * [ARM调试指南](zh-cn/arm_debugging.md)
    * [AVR处理器](zh-cn/hardware_avr.md)
    * [代码书写规范 - C](zh-cn/coding_conventions_c.md)
    * [兼容的微处理器](zh-cn/compatible_microcontrollers.md)
    * [驱动](zh-cn/hardware_drivers.md)
      * [ADC驱动](zh-cn/adc_driver.md)
      * [音频驱动](zh-cn/audio_driver.md)
      * [I2C驱动](zh-cn/i2c_driver.md)
      * [SPI驱动](zh-cn/spi_driver.md)
      * [WS2812驱动](zh-cn/ws2812_driver.md)
      * [EEPROM驱动](zh-cn/eeprom_driver.md)
      * ['serial' Driver](zh-cn/serial_driver.md)
      * [UART Driver](zh-cn/uart_driver.md)
    * [GPIO控制](zh-cn/internals_gpio_control.md)
    * [键盘规则](zh-cn/hardware_keyboard_guidelines.md)

  * Python Development
    * [代码书写规范](zh-cn/coding_conventions_python.md)
    * [QMK 命令行开发](zh-cn/cli_development.md)

  * Configurator Development
    * QMK API
      * [Development Environment](zh-cn/api_development_environment.md)
      * [Architecture Overview](zh-cn/api_development_overview.md)

  * Hardware Platform Development
    * Arm/ChibiOS
      * [Selecting an MCU](zh-cn/platformdev_selecting_arm_mcu.md)
      * [Early initialization](zh-cn/platformdev_chibios_earlyinit.md)

  * QMK Reference
    * [向QMK贡献代码](zh-cn/contributing.md)
    * [翻译QMK文档](zh-cn/translating.md)
    * [配置选项](zh-cn/config_options.md)
    * [Data Driven Configuration](zh-cn/data_driven_config.md)
    * [构建/编译指南](zh-cn/getting_started_make_guide.md)
    * [文档书写规范](zh-cn/documentation_best_practices.md)
    * [文档模板](zh-cn/documentation_templates.md)
    * [社群布局](zh-cn/feature_layouts.md)
    * [单元测试](zh-cn/unit_testing.md)
    * [实用函数](zh-cn/ref_functions.md)
    * [info.json 格式](zh-cn/reference_info_json.md)

  * 深入了解
    * [键盘工作原理](zh-cn/how_keyboards_work.md)
    * [How a Matrix Works](zh-cn/how_a_matrix_works.md)
    * [深入了解QMK](zh-cn/understanding_qmk.md)

  * QMK 内构 (正在编写)
    * [定义](zh-cn/internals_defines.md)
    * [输入回调寄存器](zh-cn/internals_input_callback_reg.md)
    * [Midi设备](zh-cn/internals_midi_device.md)
    * [Midi设备配置过程](zh-cn/internals_midi_device_setup_process.md)
    * [Midi工具库](zh-cn/internals_midi_util.md)
    * [发送函数](zh-cn/internals_send_functions.md)
    * [Sysex工具](zh-cn/internals_sysex_tools.md)
