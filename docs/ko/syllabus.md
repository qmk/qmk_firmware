# QMK 계획서

이 페이지는 기본 사항을 먼저 소개하여 QMK 지식을 쌓는 데 도움이 될 것이며 QMK에 능숙해지기 위해 알아야 할 모든 개념을 이해하도록 안내합니다.

# 초급 주제

아직 어떠한 것이라도 읽지 않았다면 이 절의 문서들을 읽어보도록 하세요. [튜토리얼](ko/newbs.md)을 읽은 뒤에 기본적인 키맵을 만들고, 컴파일하고, 키보드에 플래시하는 것을 알 수 있어야 합니다. 나머지 문서들이 이러한 기초 지식을 구체화할 것입니다. 

* **QMK 도구를 사용하는 방법 배우기**
    * [튜토리얼](ko/newbs.md)
    * [CLI](ko/cli.md)
    * [GIT](ko/newbs_git_best_practices.md)
* **키맵에 대해 배우기**
    * [레이어](ko/feature_layers.md)
    * [키코드](ko/keycodes.md)
        * 사용할 수 있는 전체 키코드 목록입니다. 몇가지는 중급 또는 상급 주제에서 찾아지는 지식이 요구될 수 있습니다.
* **IDE 구성** - 선택사항
    * [Eclipse](ko/other_eclipse.md)
    * [VS Code](ko/other_vscode.md)

# 중급 주제

이 주제들은 QMK가 지원하는 몇 가지 기능을 파헤치는 걸 시작할 수 있습니다. 이 문서들의 모든 것을 정독하지 않아도 되지만, 고급 주제 절 안의 일부 문서는 이 중 일부를 건너뛰는 경우 의미가 없을 수 있습니다.

* **기능 구성을 하는 방법 배우기**
    <!-- * Configuration Overview  FIXME(skullydazed/anyone): write this document -->
    * [오디오](ko/feature_audio.md)
    * 조명
        * [Backlight](ko/feature_backlight.md)
        * [LED Matrix](ko/feature_led_matrix.md)
        * [RGB Lighting](ko/feature_rgblight.md)
        * [RGB Matrix](ko/feature_rgb_matrix.md)
    * [Tap-Hold Configuration](ko/tap_hold.md)
    * [Squeezing Space from AVR](ko/squeezing_avr.md)
* **키맵에 대해 더 배우기**
    * [키맵](ko/keymap.md)
    * [사용자 정의 기능 및 키코드](ko/custom_quantum_functions.md)
    * 매크로
        * [Dynamic Macros](ko/feature_dynamic_macros.md)
        * [Compiled Macros](ko/feature_macros.md)
    * [Tap Dance](ko/feature_tap_dance.md)
    * [Combos](ko/feature_combo.md)
    * [Userspace](ko/feature_userspace.md)
    * [Key Overrides](ko/feature_key_overrides.md)

# 고급 주제

아래에 있는 모든 것들은 많은 기초 지식을 요구합니다. 고급 기능을 사용하여 키맵을 생성하는 것 외에도 `config.h`와 `rules.mk`를 사용하여 키보드의 옵션을 구성하는 데 익숙해져야 합니다.

* **QMK 내에서 키보드 유지 관리**
    * [Handwiring a Keyboard](ko/hand_wire.md)
    * [Keyboard Guidelines](ko/hardware_keyboard_guidelines.md)
    * [info.json Reference](ko/reference_info_json.md)
    * [Debounce API](ko/feature_debounce_type.md)
* **고급 기능들**
    * [Unicode](ko/feature_unicode.md)
    * [API](ko/api_overview.md)
    * [Bootmagic Lite](ko/feature_bootmagic.md)
* **하드웨어**
    * [How Keyboards Work](ko/how_keyboards_work.md)
    * [How A Keyboard Matrix Works](ko/how_a_matrix_works.md)
    * [Split Keyboards](ko/feature_split_keyboard.md)
    * [Stenography](ko/feature_stenography.md)
    * [Pointing Devices](ko/feature_pointing_device.md)
* **코어 개발**
    * [Coding Conventions](ko/coding_conventions_c.md)
    * [Compatible Microcontrollers](ko/compatible_microcontrollers.md)
    * [Custom Matrix](ko/custom_matrix.md)
    * [Understanding QMK](ko/understanding_qmk.md)
* **CLI 개발**
    * [Coding Conventions](ko/coding_conventions_python.md)
    * [CLI Development Overview](ko/cli_development.md)
