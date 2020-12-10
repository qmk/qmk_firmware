* [教程]
  * [介绍](zh-cn/newbs.md)
  * [入门](zh-cn/newbs_getting_started.md)
  * [构建你的第一个固件](zh-cn/newbs_building_firmware.md)
  * [烧录固件](zh-cn/newbs_flashing.md)
  * [测试和调试](zh-cn/newbs_testing_debugging.md)
  * [获取帮助/支持](zh-cn/support.md)
  * [其他资源](zh-cn/newbs_learn_more_resources.md)
  * [Syllabus](zh-cn/syllabus.md)

* [问题与解答](zh-cn/faq.md)
  * [一般问题](zh-cn/faq_general.md)
  * [构建/编译](zh-cn/faq_build.md)
  * [调试/故障排除](zh-cn/faq_debug.md)
  * [布局](zh-cn/faq_keymap.md)
  * [Zadig 驱动安装](zh-cn/driver_installation_zadig.md)

* 配置
  * [概述](zh-cn/newbs_building_firmware_configurator.md)
  * [一步一步](zh-cn/configurator_step_by_step.md)
  * [故障排除](zh-cn/configurator_troubleshooting.md)
  * QMK API
    * [概述](zh-cn/api_overview.md)
    * [API 文档](zh-cn/api_docs.md)
    * [键盘支持](zh-cn/reference_configurator_support.md)
    * [添加默认键盘映射](zh-cn/configurator_default_keymaps.md)

* 命令行工具(CLI)
    * [概述](zh-cn/cli.md)
    * [配置](zh-cn/cli_configuration.md)
    * [命令](zh-cn/cli_commands.md)

* 使用 QMK
  * 教程
    * [定制功能](zh-cn/custom_quantum_functions.md)
    * [使用 Zadig 安装驱动](zh-cn/driver_installation_zadig.md)
    * [键盘映射概述](zh-cn/keymap.md)
    * 开发环境
      * [Docker 教程](zh-cn/getting_started_docker.md)
      * [Vagrant 教程](zh-cn/getting_started_vagrant.md)
    * 烧录(Flashing)
      * [烧录](zh-cn/flashing.md)
      * [烧录 ATmega32A (ps2avrgb)](zh-cn/flashing_bootloadhid.md)
    * IDEs
      * [使用 Eclipse 开发 QMK](zh-cn/other_eclipse.md)
      * [使用 VSCode 开发 QMK](zh-cn/other_vscode.md)
    * [Git 最佳实践]
      * [介绍](zh-cn/newbs_git_best_practices.md)
      * [你的分叉(fork)](zh-cn/newbs_git_using_your_master_branch.md)
      * [解决合并冲突](zh-cn/newbs_git_resolving_merge_conflicts.md)
      * [修复分支](zh-cn/newbs_git_resynchronize_a_branch.md)
    * 键盘组装
      * [手工连线指南](zh-cn/hand_wire.md)
      * [ISP 烧录指南](zh-cn/isp_flashing_guide.md)

  * 基础键码
    * [全列表](zh-cn/keycodes.md)
    * [基础键码](zh-cn/keycodes_basic.md)
    * [特定语言键(Language-Specific Keycodes)](zh-cn/reference_extras.md)
    * [修饰键](zh-cn/feature_advanced_keycodes.md)
    * [QMK 键码](zh-cn/quantum_keycodes.md)

  * 进阶键码
    * [命令](zh-cn/feature_command.md)
    * [动态宏指令](zh-cn/feature_dynamic_macros.md)
    * [反引号和 Esc 复合键](zh-cn/feature_grave_esc.md)
    * [前缀键(Leader Key)](zh-cn/feature_leader_key.md)
    * [Mod-Tap](zh-cn/mod_tap.md)
    * [宏指令](zh-cn/feature_macros.md)
    * [Mouse Keys](feature_mouse_keys.md)
    * [Space Cadet Shift](zh-cn/feature_space_cadet.md)
    * [美国 ANSI 标准上档键码(US ANSI Shifted Keys)](zh-cn/keycodes_us_ansi_shifted.md)

  * 软件特性
    * [自动 Shift](zh-cn/feature_auto_shift.md)
    * [组合](zh-cn/feature_combo.md)
    * [去抖 API](zh-cn/feature_debounce_type.md)
    * [键盘锁定](zh-cn/feature_key_lock.md)
    * [Layers](zh-cn/feature_layers.md)
    * [One Shot Keys](zh-cn/one_shot_keys.md)
    * [Pointing Device](zh-cn/feature_pointing_device.md)
    * [原生 HID](zh-cn/feature_rawhid.md)
    * [音序器(Sequencer)](zh-cn/feature_sequencer.md)
    * [Swap Hands](zh-cn/feature_swap_hands.md)
    * [踢踏舞(Tap Dance)](zh-cn/feature_tap_dance.md)
    * [Tap-Hold Configuration](zh-cn/tap_hold.md)
    * [终端](zh-cn/feature_terminal.md)
    * [Unicode](zh-cn/feature_unicode.md)
    * [用户空间](zh-cn/feature_userspace.md)
    * [WPM 计算](zh-cn/feature_wpm.md)

  * 硬件特性
    * 显示
      * [HD44780 LCD 控制器](zh-cn/feature_hd44780.md)
      * [OLED 驱动](zh-cn/feature_oled_driver.md)
    * 灯光
      * [背光](zh-cn/feature_backlight.md)
      * [LED 矩阵](zh-cn/feature_led_matrix.md)
      * [RGB 灯光](zh-cn/feature_rgblight.md)
      * [RGB 矩阵](zh-cn/feature_rgb_matrix.md)
    * [音频](zh-cn/feature_audio.md)
    * [蓝牙](zh-cn/feature_bluetooth.md)
    * [热改键(Bootmagic)](zh-cn/feature_bootmagic.md)
    * [Custom Matrix](zh-cn/custom_matrix.md)
    * [拨码开关](zh-cn/feature_dip_switch.md)
    * [编码器（旋钮）](zh-cn/feature_encoders.md)
    * [振动反馈](zh-cn/feature_haptic_feedback.md)
    * [操纵杆](zh-cn/feature_joystick.md)
    * [LED 指示灯](zh-cn/feature_led_indicators.md)
    * [Proton C Conversion](zh-cn/proton_c_conversion.md)
    * [PS/2鼠标](zh-cn/feature_ps2_mouse.md)
    * [分体键盘](zh-cn/feature_split_keyboard.md)
    * [速录机](zh-cn/feature_stenography.md)
    * [热敏打印机](zh-cn/feature_thermal_printer.md)
    * [速度键](zh-cn/feature_velocikey.md)

* QMK 开发
  * [PR 清单](zh-cn/pr_checklist.md)
  * 破坏性更改
    * [概述](zh-cn/breaking_changes.md)
    * [我的 PR 被标记了](zh-cn/breaking_changes_instructions.md)
    * 历史
      * [2020年11月28](ChangeLog/20201128.md)
      * [20208月29日](ChangeLog/20200829.md)
      * [20205月30日](ChangeLog/20200530.md)
      * [20202月29日](ChangeLog/20200229.md)
      * [20198月30日](ChangeLog/20190830.md)

  * C 开发
    * [ARM 调试指南](zh-cn/arm_debugging.md)
    * [AVR 处理器](zh-cn/hardware_avr.md)
    * [Coding Conventions](zh-cn/coding_conventions_c.md)
    * [兼容的单片机](zh-cn/compatible_microcontrollers.md)
    * [驱动](zh-cn/hardware_drivers.md)
      * [ADC Driver](zh-cn/adc_driver.md)
      * [I2C Driver](zh-cn/i2c_driver.md)
      * [SPI Driver](zh-cn/spi_driver.md)
      * [WS2812 Driver](zh-cn/ws2812_driver.md)
      * [EEPROM Driver](zh-cn/eeprom_driver.md)
      * ['serial' Driver](zh-cn/serial_driver.md)
    * [GPIO 控制](zh-cn/internals_gpio_control.md)
    * [键盘指南](zh-cn/hardware_keyboard_guidelines.md)

  * Python 开发
    * [代码书写规范](zh-cn/coding_conventions_python.md)
    * [QMK 命令行开发](zh-cn/cli_development.md)

  * 开发配置
    * QMK API
      * [开发环境](zh-cn/api_development_environment.md)
      * [Architecture Overview](zh-cn/api_development_overview.md)

  * H硬件平台开发
    * Arm/ChibiOS
      * [Selecting an MCU](zh-cn/platformdev_selecting_arm_mcu.md)
      * [Early initialization](zh-cn/platformdev_chibios_earlyinit.md)
  
  * QMK 参考
    * [为 QMK 做贡献](zh-cn/contributing.md)
    * [翻译 QMK 文档](zh-cn/translating.md)
    * [配置文档](zh-cn/config_options.md)
    * [Make 文档](zh-cn/getting_started_make_guide.md)
    * [文档最佳实践](zh-cn/documentation_best_practices.md)
    * [文档模板](zh-cn/documentation_templates.md)
    * [社区布局(Community Layouts)](zh-cn/feature_layouts.md)
    * [单元测试](zh-cn/unit_testing.md)
    * [实用函数](zh-cn/ref_functions.md)
    * [info.json 格式](zh-cn/reference_info_json.md)
  
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

<!--fromen:20201129-4:01AM(GMT+8)-->
<!--cn:20200526-10:43AM(GMT+8)-->
