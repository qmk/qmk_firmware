# QMK Syllabus

Esta página o ajuda a construir seu conhecimento de QMK, introduzindo os fundamentos primeiro e orientando-o a compreender todos os conceitos que você precisa saber para ser proficiente com QMK.

# Tópicos iniciais

Se você não ler mais nada, deverá ler os documentos desta seção. Depois de ler o [Tutorial](newbs.md), você deve ser capaz de criar um mapa de teclado básico, compilá-lo e atualizá-lo para o seu teclado. Os documentos restantes aumentarão seu conhecimento desses princípios básicos.

* **Aprenda a usar as ferramentas QMK**
    * [Tutorial](newbs.md)
    * [CLI](cli.md)
    * [GIT](newbs_git_best_practices.md)
* **Saiba mais sobre mapas de teclado**
    * [Layers](feature_layers.md)
    * [Keycodes](keycodes.md)
        * A lista completa de códigos-chave que você pode usar. Observe que alguns podem exigir conhecimentos encontrados nos Tópicos Intermediários ou Avançados.
* **Configurando IDEs** - Opcional
    * [Eclipse](other_eclipse.md)
    * [Código VS](other_vscode.md)

# Tópicos intermediários

Esses tópicos começam a se aprofundar em alguns dos recursos que o QMK suporta. Você não precisa ler todos esses documentos, mas alguns dos documentos na seção Tópicos avançados não farão sentido se você pular alguns deles.

* ** Aprenda a configurar recursos **
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
    * [Key Overrides](feature_key_overrides.md)

# Tópicos Avançados

Tudo abaixo aqui requer muito conhecimento básico. Além de poder criar keymaps usando recursos avançados, você deve estar familiarizado com o uso de `config.h` e` rules.mk` para configurar opções para seu teclado.

* **Maintaining Keyboards Within QMK**
    * [Handwiring a Keyboard](hand_wire.md)
    * [Keyboard Guidelines](hardware_keyboard_guidelines.md)
    * [info.json Reference](reference_info_json.md)
    * [Debounce API](feature_debounce_type.md)
* **Advanced Features**
    * [Unicode](feature_unicode.md)
    * [API](api_overview.md)
    * [Bootmagic Lite](feature_bootmagic.md)
* **Hardware**
    * [How Keyboards Work](how_keyboards_work.md)
    * [How A Keyboard Matrix Works](how_a_matrix_works.md)
    * [Split Keyboards](feature_split_keyboard.md)
    * [Stenography](feature_stenography.md)
    * [Pointing Devices](feature_pointing_device.md)
* **Core Development**
    * [Coding Conventions](coding_conventions_c.md)
    * [Compatible Microcontrollers](compatible_microcontrollers.md)
    * [Custom Matrix](custom_matrix.md)
    * [Understanding QMK](understanding_qmk.md)
* **CLI Development**
    * [Coding Conventions](coding_conventions_python.md)
    * [CLI Development Overview](cli_development.md)