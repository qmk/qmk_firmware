<!--for translators, see first: zh-cn/reference_glossary.md#terms-of-zh-cn-translate -->
* 新手教程
  * [介绍](zh-cn/newbs.md)
  * [入门](zh-cn/newbs_getting_started.md)
  * [构建第一个固件](zh-cn/newbs_building_firmware.md)
  * [刷写固件](zh-cn/newbs_flashing.md)
  * [寻求帮助](zh-cn/support.md)
  * [其它资源](zh-cn/newbs_learn_more_resources.md)
  * [QMK大纲](zh-cn/syllabus.md)

* FAQ
  * [常规FAQ](zh-cn/faq_general.md)
  * [构建/编译QMK](zh-cn/faq_build.md)
  * [QMK问题排查](zh-cn/faq_misc.md)
  * [调试QMK](zh-cn/faq_debug.md)
  * [键映射FAQ](zh-cn/faq_keymap.md)
  * [充分利用AVR的存储空间](zh-cn/squeezing_avr.md)
  * [术语表](zh-cn/reference_glossary.md)

* 配置器(Configurator)
  * [总览](zh-cn/newbs_building_firmware_configurator.md)
  * [入门](zh-cn/configurator_step_by_step.md)
  * [问题排查](zh-cn/configurator_troubleshooting.md)
  * [框架](zh-cn/configurator_architecture.md)
  * QMK API
    * [总览](zh-cn/api_overview.md)
    * [API文档](zh-cn/api_docs.md)
    * [键盘支持](zh-cn/reference_configurator_support.md)
    * [添加默认键映射](zh-cn/configurator_default_keymaps.md)

* CLI
    * [总览](zh-cn/cli.md)
    * [配置](zh-cn/cli_configuration.md)
    * [命令](zh-cn/cli_commands.md)
    * [Tab补全](zh-cn/cli_tab_complete.md)

* 使用QMK
  * 导览
    * [功能定制](zh-cn/custom_quantum_functions.md)
    * [利用Zadig安装驱动](zh-cn/driver_installation_zadig.md)
    * [极简式制作](zh-cn/easy_maker.md)
    * [键映射总览](zh-cn/keymap.md)
    * 开发环境
      * [Docker指南](zh-cn/getting_started_docker.md)
      * [Vagrant指南](zh-cn/getting_started_vagrant.md)
    * 刷写(Flashing)
      * [刷写](zh-cn/flashing.md)
      * [刷写ATmega32A (ps2avrgb)](zh-cn/flashing_bootloadhid.md)
    * IDE
      * [在Eclipse中使用QMK](zh-cn/other_eclipse.md)
      * [在VSCode中使用QMK](zh-cn/other_vscode.md)
    * Git最佳实践
      * [介绍](zh-cn/newbs_git_best_practices.md)
      * [你自己的副本](zh-cn/newbs_git_using_your_master_branch.md)
      * [冲突合并](zh-cn/newbs_git_resolving_merge_conflicts.md)
      * [基于你的分支修复](zh-cn/newbs_git_resynchronize_a_branch.md)
    * 键盘组装
      * [飞线指南](zh-cn/hand_wire.md)
      * [ISP刷写指南](zh-cn/isp_flashing_guide.md)

  * 键码入门
    * [键码汇总](zh-cn/keycodes.md)
    * [基础键码](zh-cn/keycodes_basic.md)
    * [语言特定的键码](zh-cn/reference_keymap_extras.md)
    * [修饰键](zh-cn/feature_advanced_keycodes.md)
    * [原子键码](zh-cn/quantum_keycodes.md)
    * [Magic键码](zh-cn/keycodes_magic.md)

  * 键码进阶
    * [指令](zh-cn/feature_command.md)
    * [动态宏](zh-cn/feature_dynamic_macros.md)
    * [Grave Escape](zh-cn/feature_grave_esc.md)
    * [前导键](zh-cn/feature_leader_key.md)
    * [Mod-Tap](zh-cn/mod_tap.md)
    * [宏](zh-cn/feature_macros.md)
    * [鼠标键](zh-cn/feature_mouse_keys.md)
    * [Space Cadet Shift](zh-cn/feature_space_cadet.md)
    * [US ANSI上档键值](zh-cn/keycodes_us_ansi_shifted.md)

  * 软件特性
    * [自动Shift](zh-cn/feature_auto_shift.md)
    * [组合键](zh-cn/feature_combo.md)
    * [防抖API](zh-cn/feature_debounce_type.md)
    * [按键锁定](zh-cn/feature_key_lock.md)
    * [按键重定义](zh-cn/feature_key_overrides.md)
    * [层](zh-cn/feature_layers.md)
    * [粘滞键](zh-cn/one_shot_keys.md)
    * [光标设备](zh-cn/feature_pointing_device.md)
    * [原生HID](zh-cn/feature_rawhid.md)
    * [Sequencer](zh-cn/feature_sequencer.md)
    * [换手](zh-cn/feature_swap_hands.md)
    * [一键多用](zh-cn/feature_tap_dance.md)
    * [点按配置](zh-cn/tap_hold.md)
    * [Unicode](zh-cn/feature_unicode.md)
    * [用户空间](zh-cn/feature_userspace.md)
    * [WPM计算](zh-cn/feature_wpm.md)

  * 硬件特性
    * 显示
      * [HD44780 LCD控制器](zh-cn/feature_hd44780.md)
      * [ST7565 LCD驱动](zh-cn/feature_st7565.md)
      * [OLED驱动](zh-cn/feature_oled_driver.md)
    * 灯效
      * [背光](zh-cn/feature_backlight.md)
      * [LED矩阵](zh-cn/feature_led_matrix.md)
      * [RGB灯光](zh-cn/feature_rgblight.md)
      * [RGB矩阵](zh-cn/feature_rgb_matrix.md)
    * [音频](zh-cn/feature_audio.md)
    * [蓝牙](zh-cn/feature_bluetooth.md)
    * [Bootmagic Lite](zh-cn/feature_bootmagic.md)
    * [自定义矩阵](zh-cn/custom_matrix.md)
    * [Digitizer](zh-cn/feature_digitizer.md)
    * [拨动开关（DIP Switch）](zh-cn/feature_dip_switch.md)
    * [编码器（旋钮）](zh-cn/feature_encoders.md)
    * [触摸反馈](zh-cn/feature_haptic_feedback.md)
    * [摇杆](zh-cn/feature_joystick.md)
    * [LED指示](zh-cn/feature_led_indicators.md)
    * [MIDI](zh-cn/feature_midi.md)
    * [Proton C转换](zh-cn/proton_c_conversion.md)
    * [PS/2鼠标](zh-cn/feature_ps2_mouse.md)
    * [分体式键盘](zh-cn/feature_split_keyboard.md)
    * [速记](zh-cn/feature_stenography.md)
    * [热敏打印机](zh-cn/feature_thermal_printer.md)
    * [Velocikey](zh-cn/feature_velocikey.md)

* QMK开发
  * [PR Checklist](zh-cn/pr_checklist.md)
  * 打破兼容的改动
    * [总览](zh-cn/breaking_changes.md)
    * [我的PR已打上标记](zh-cn/breaking_changes_instructions.md)
    * [近期的变更日志(Changelog)](zh-cn/ChangeLog/20210529.md "QMK v0.13.0 - 2021 May 29")
    * [更早期的不兼容改动](zh-cn/breaking_changes_history.md)

  * C语言开发
    * [ARM调试指引](zh-cn/arm_debugging.md)
    * [AVR处理器](zh-cn/hardware_avr.md)
    * [C编码规范](zh-cn/coding_conventions_c.md)
    * [兼容的微处理器](zh-cn/compatible_microcontrollers.md)
    * [驱动](zh-cn/hardware_drivers.md)
      * [ADC驱动](zh-cn/adc_driver.md)
      * [Audio驱动](zh-cn/audio_driver.md)
      * [I2C驱动](zh-cn/i2c_driver.md)
      * [SPI驱动](zh-cn/spi_driver.md)
      * [WS2812驱动](zh-cn/ws2812_driver.md)
      * [EEPROM驱动](zh-cn/eeprom_driver.md)
      * [串口驱动](zh-cn/serial_driver.md)
      * [UART驱动](zh-cn/uart_driver.md)
    * [操控GPIO](zh-cn/gpio_control.md)
    * [键盘开发指引](zh-cn/hardware_keyboard_guidelines.md)

  * Python开发
    * [编码规范](zh-cn/coding_conventions_python.md)
    * [QMK CLI开发](zh-cn/cli_development.md)

  * 配置器开发
    * QMK API
      * [开发环境](zh-cn/api_development_environment.md)
      * [架构总览](zh-cn/api_development_overview.md)

  * 硬件平台开发
    * Arm/ChibiOS
      * [选择MCU](zh-cn/platformdev_selecting_arm_mcu.md)
      * [启动引导](zh-cn/platformdev_chibios_earlyinit.md)

  * QMK参考信息
    * [参与到QMK](zh-cn/contributing.md)
    * [翻译QMK文档](zh-cn/translating.md)<!--but should we translate this? currently keep it fallback-->
    * [配置](zh-cn/config_options.md)
    * [数据驱动配置](zh-cn/data_driven_config.md)
    * [Make指引](zh-cn/getting_started_make_guide.md)
    * [编写文档的最佳实践](zh-cn/documentation_best_practices.md)
    * [文档模板](zh-cn/documentation_templates.md)
    * [贡献配列到社区](zh-cn/feature_layouts.md)
    * [单元测试](zh-cn/unit_testing.md)
    * [常用函数](zh-cn/ref_functions.md)
    * [info.json参考资料](zh-cn/reference_info_json.md)

  * 深入了解
    * [键盘工作原理](zh-cn/how_keyboards_work.md)
    * [键盘矩阵原理](zh-cn/how_a_matrix_works.md)
    * [了解QMK](zh-cn/understanding_qmk.md)

  * QMK内部细节 (编辑中)
    * [定义](zh-cn/internals/defines.md)
    * [输入回调的注册](zh-cn/internals/input_callback_reg.md)
    * [Midi设备](zh-cn/internals/midi_device.md)
    * [Midi设备驱动流程](zh-cn/internals/midi_device_setup_process.md)
    * [Midi辅助功能](zh-cn/internals/midi_util.md)
    * [发送函数](zh-cn/internals/send_functions.md)
    * [Sysex工具](zh-cn/internals/sysex_tools.md)
    
<!--fromen:20211014-12:00(GMT+8) commit 04cf161aa01fd433b5dae69d9fd31569ed5dca59-->
