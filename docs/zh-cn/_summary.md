* [教程]
  * [介绍](zh-cn/newbs.md)
  * [入门](zh-cn/newbs_getting_started.md)
  * [构建你的第一个固件](zh-cn/newbs_building_firmware.md)
  * [刷新固件](zh-cn/newbs_flashing.md)
  * [测试和调试](zh-cn/newbs_testing_debugging.md)
  * [获取帮助/支持](zh-cn/support.md)
  * [其他资源](zh-cn/newbs_learn_more_resources.md)
  * [Syllabus](zh-cn/syllabus.md)

* [问题与解答](zh-cn/faq.md)
  * [一般问题](zh-cn/faq_general.md)
  * [构建/编译](zh-cn/faq_build.md)
  * [调试/故障排除](zh-cn/faq_debug.md)
  * [布局](zh-cn/faq_keymap.md)
  * [Zadig驱动安装](zh-cn/driver_installation_zadig.md)

* 配置
  * [概述](newbs_building_firmware_configurator.md)
  * [一步一步](configurator_step_by_step.md)
  * [故障排除](configurator_troubleshooting.md)
  * QMK API
    * [概述](api_overview.md)
    * [API 文档](api_docs.md)
    * [键盘支持](reference_configurator_support.md)
    * [添加默认键盘映射](configurator_default_keymaps.md)

* CLI
    * [概述](cli.md)
    * [配置](cli_configuration.md)
    * [命令](cli_commands.md)

* 使用 QMK
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
      * [使用 Eclipse 开发 QMK](zh-cn/other_eclipse.md)
      * [使用 VSCode 开发 QMK](zh-cn/other_vscode.md)
    * [Git最佳实践]
      * [介绍](zh-cn/newbs_git_best_practices.md)
      * [你的分叉(fork)](zh-cn/newbs_git_using_your_master_branch.md)
      * [解决合并冲突](zh-cn/newbs_git_resolving_merge_conflicts.md)
      * [修复分支](zh-cn/newbs_git_resynchronize_a_branch.md)
    * Keyboard Building
      * [Hand Wiring Guide](hand_wire.md)
      * [ISP Flashing Guide](isp_flashing_guide.md)

  * 基础键码
    * [Full List](keycodes.md)
    * [Basic Keycodes](keycodes_basic.md)
    * [Language-Specific Keycodes](reference_keymap_extras.md)
    * [Modifier Keys](feature_advanced_keycodes.md)
    * [Quantum Keycodes](quantum_keycodes.md)

  * 进阶键码
    * [Command](feature_command.md)
    * [Dynamic Macros](feature_dynamic_macros.md)
    * [Grave Escape](feature_grave_esc.md)
    * [Leader Key](feature_leader_key.md)
    * [Mod-Tap](mod_tap.md)
    * [Macros](feature_macros.md)
    * [Mouse Keys](feature_mouse_keys.md)
    * [Space Cadet Shift](feature_space_cadet.md)
    * [US ANSI Shifted Keys](keycodes_us_ansi_shifted.md)

  * 软件特性
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

  * 硬件特性
    * 显示
      * [HD44780 LCD 控制器](zh-cn/feature_hd44780.md)
      * [OLED 驱动](zh-cn/feature_oled_driver.md)
    * 灯光
      * [背光](zh-cn/feature_backlight.md)
      * [LED 矩阵](zh-cn/feature_led_matrix.md)
      * [RGB 灯光](zh-cn/feature_rgblight.md)
      * [RGB 阵列](zh-cn/feature_rgb_matrix.md)
    * [音频](zh-cn/feature_audio.md)
    * [蓝牙](zh-cn/feature_bluetooth.md)
    * [热改键(Bootmagic)](zh-cn/feature_bootmagic.md)
    * [Custom Matrix](zh-cn/custom_matrix.md)
    * [拨码开关](zh-cn/feature_dip_switch.md)
    * [编码器](zh-cn/feature_encoders.md)
    * [触摸反馈](zh-cn/feature_haptic_feedback.md)
    * [操纵杆](zh-cn/feature_joystick.md)
    * [LED 指示灯](zh-cn/feature_led_indicators.md)
    * [Proton C Conversion](zh-cn/proton_c_conversion.md)
    * [PS/2鼠标](zh-cn/feature_ps2_mouse.md)
    * [分体键盘](zh-cn/feature_split_keyboard.md)
    * [速录机](zh-cn/feature_stenography.md)
    * [热敏打印机](zh-cn/feature_thermal_printer.md)
    * [速度键](zh-cn/feature_velocikey.md)

* QMK 开发
  * [PR 清单](pr_checklist.md)
  * 破坏性更改
    * [概述](breaking_changes.md)
    * [我的 PR 被标记了](breaking_changes_instructions.md)
    * 历史
      * [2020年11月28](ChangeLog/20201128.md)
      * [20208月29日](ChangeLog/20200829.md)
      * [20205月30日](ChangeLog/20200530.md)
      * [20202月29日](ChangeLog/20200229.md)
      * [20198月30日](ChangeLog/20190830.md)

  * C 开发
    * [ARM 调试指南](arm_debugging.md)
    * [AVR 处理器](hardware_avr.md)
    * [Coding Conventions](coding_conventions_c.md)
    * [兼容的单片机](compatible_microcontrollers.md)
    * [驱动](hardware_drivers.md)
      * [ADC Driver](adc_driver.md)
      * [I2C Driver](i2c_driver.md)
      * [SPI Driver](spi_driver.md)
      * [WS2812 Driver](ws2812_driver.md)
      * [EEPROM Driver](eeprom_driver.md)
      * ['serial' Driver](serial_driver.md)
    * [GPIO 控制](internals_gpio_control.md)
    * [键盘指南](hardware_keyboard_guidelines.md)

  * Python 开发
    * [代码书写规范](coding_conventions_python.md)
    * [QMK 命令行开发](zh-cn/cli_development.md)

  * 开发配置
    * QMK API
      * [开发环境](api_development_environment.md)
      * [Architecture Overview](api_development_overview.md)

  * H硬件平台开发
    * Arm/ChibiOS
      * [Selecting an MCU](platformdev_selecting_arm_mcu.md)
      * [Early initialization](platformdev_chibios_earlyinit.md)
  
  * QMK 参考
    * [为 QMK 做贡献](contributing.md)
    * [翻译 QMK 文档](translating.md)
    * [配置文档](config_options.md)
    * [Make 文档](getting_started_make_guide.md)
    * [文档最佳实践](documentation_best_practices.md)
    * [文档模板](documentation_templates.md)
    * [社区布局(Community Layouts)](feature_layouts.md)
    * [单元测试](unit_testing.md)
    * [实用函数](ref_functions.md)
    * [info.json 格式](reference_info_json.md)
  
  * 深入了解
    * [键盘工作原理](zh-cn/how_keyboards_work.md)
    * [Matrix 工作原理](zh-cn/how_a_matrix_works.md)
    * [深入了解 QMK](zh-cn/understanding_qmk.md)
  
  * QMK 内构 (正在编写)
    * [定义](zh-cn/internals_defines.md)
    * [输入回调寄存器](zh-cn/internals_input_callback_reg.md)
    * [Midi设备](zh-cn/internals_midi_device.md)
    * [Midi设备配置过程](zh-cn/internals_midi_device_setup_process.md)
    * [Midi工具库](zh-cn/internals_midi_util.md)
    * [发送函数](zh-cn/internals_send_functions.md)
    * [Sysex工具](zh-cn/internals_sysex_tools.md)

* [QMK基础](zh-cn/README.md)
  * [QMK简介](zh-cn/getting_started_introduction.md)
  * [QMK命令行工具](zh-cn/cli.md)
  * [QMK命令行工具配置](zh-cn/cli_configuration.md)
  * [向QMK贡献代码](zh-cn/contributing.md)
  * [如何使用GitHub](zh-cn/getting_started_github.md)
  * [获得帮助](zh-cn/getting_started_getting_help.md)

* [非兼容性修改](zh-cn/breaking_changes.md)
  * [我的PR已经被标记为非兼容性修改](zh-cn/breaking_changes_instructions.md)
  * [2019年8月30日](zh-cn/ChangeLog/20190830.md)


* 详细指南
  * [安装构建工具](zh-cn/getting_started_build_tools.md)
  * [vagrant指南](zh-cn/getting_started_vagrant.md)
  * [构建/编译指南](zh-cn/getting_started_make_guide.md)
  * [刷新固件](zh-cn/flashing.md)
  * [定制功能](zh-cn/custom_quantum_functions.md)
  * [布局概述](zh-cn/keymap.md)



* [特性](zh-cn/features.md)
  * [基本键码](zh-cn/keycodes_basic.md)
  * [US ANSI控制码](zh-cn/keycodes_us_ansi_shifted.md)
  * [量子键码](zh-cn/quantum_keycodes.md)
  * [高级键码](zh-cn/feature_advanced_keycodes.md)
  * [音频](zh-cn/feature_audio.md)
  * [自动shift](zh-cn/feature_auto_shift.md)
  * [背光](zh-cn/feature_backlight.md)
  * [蓝牙](zh-cn/feature_bluetooth.md)
  * [热改键](zh-cn/feature_bootmagic.md)
  * [组合](zh-cn/feature_combo)
  * [命令](zh-cn/feature_command.md)
  * [消抖 API](zh-cn/feature_debounce_type.md)
  * [拨动开关](zh-cn/feature_dip_switch.md)
  * [动态宏指令](zh-cn/feature_dynamic_macros.md)
  * [编码器](zh-cn/feature_encoders.md)
  * [重音号Esc复合键](zh-cn/feature_grave_esc.md)
  * [触摸反馈](zh-cn/feature_haptic_feedback.md)
  * [HD44780 LCD控制器](zh-cn/feature_hd44780.md)
  * [自锁键](zh-cn/feature_key_lock.md)
  * [布局](zh-cn/feature_layouts.md)
  * [前导键](zh-cn/feature_leader_key.md)
  * [LED阵列](zh-cn/feature_led_matrix.md)
  * [宏指令](zh-cn/feature_macros.md)
  * [鼠标键](zh-cn/feature_mouse_keys.md)
  * [OLED驱动](zh-cn/feature_oled_driver.md)
  * [一键功能](zh-cn/one_shot_keys.md)
  * [指针设备](zh-cn/feature_pointing_device.md)
  * [PS/2鼠标](zh-cn/feature_ps2_mouse.md)
  * [RGB灯光](zh-cn/feature_rgblight.md)
  * [RGB矩阵](zh-cn/feature_rgb_matrix.md)
  * [空格候补换挡](zh-cn/feature_space_cadet.md)
  * [分体键盘](zh-cn/feature_split_keyboard.md)
  * [速录机](zh-cn/feature_stenography.md)
  * [换手](zh-cn/feature_swap_hands.md)
  * [多击键](zh-cn/feature_tap_dance.md)
  * [终端](zh-cn/feature_terminal.md)
  * [热敏打印机](zh-cn/feature_thermal_printer.md)
  * [Unicode](zh-cn/feature_unicode.md)
  * [用户空间](zh-cn/feature_userspace.md)
  * [速度键](zh-cn/feature_velocikey.md)

* 制造和定制者指南
  * [手工连线指南](zh-cn/hand_wire.md)
  * [ISP刷新指南](zh-cn/isp_flashing_guide.md)
  * [ARM调试指南](zh-cn/arm_debugging.md)
  * [ADC设备](zh-cn/adc_driver.md)
  * [I2C设备](zh-cn/i2c_driver.md)
  * [SPI设备](zh-cn/spi_driver.md)
  * [WS2812设备](zh-cn/ws2812_driver.md)
  * [EEPROM设备](zh-cn/eeprom_driver.md)
  * [GPIO控制](zh-cn/internals_gpio_control.md)
  * [自定义键盘矩阵](zh-cn/custom_matrix.md)
  * [Proton C转换](zh-cn/proton_c_conversion.md)

<!--fromen:20200126-6:03AM(GMT+8)-->
<!--cn:20200211-11:04AM(GMT+8)-->
