import qmk.keymap


def test_template_c_pytest_basic():
    templ = qmk.keymap.template_c('handwired/pytest/basic')
    assert templ == qmk.keymap.DEFAULT_KEYMAP_C


def test_template_json_pytest_basic():
    templ = qmk.keymap.template_json('handwired/pytest/basic')
    assert templ == {'keyboard': 'handwired/pytest/basic'}


def test_template_c_pytest_has_template():
    templ = qmk.keymap.template_c('handwired/pytest/has_template')
    assert templ == '#include QMK_KEYBOARD_H\nconst uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {__KEYMAP_GOES_HERE__};\n'


def test_template_json_pytest_has_template():
    templ = qmk.keymap.template_json('handwired/pytest/has_template')
    assert templ == {'keyboard': 'handwired/pytest/has_template', "documentation": "This file is a keymap.json file for handwired/pytest/has_template"}


def test_generate_c_pytest_has_template():
    keymap_json = {
        'keyboard': 'handwired/pytest/has_template',
        'layout': 'LAYOUT',
        'layers': [['KC_A']],
        'macros': None,
    }
    templ = qmk.keymap.generate_c(keymap_json)
    assert templ == '#include QMK_KEYBOARD_H\nconst uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {\t[0] = LAYOUT(KC_A)};\n'


def test_generate_json_pytest_has_template():
    templ = qmk.keymap.generate_json('default', 'handwired/pytest/has_template', 'LAYOUT', [['KC_A']])
    assert templ == {"keyboard": "handwired/pytest/has_template", "documentation": "This file is a keymap.json file for handwired/pytest/has_template", "keymap": "default", "layout": "LAYOUT", "layers": [["KC_A"]]}


def test_parse_keymap_c():
    parsed_keymap_c = qmk.keymap.parse_keymap_c('keyboards/handwired/pytest/basic/keymaps/default/keymap.c')
    assert parsed_keymap_c == {'layers': [{'name': '0', 'layout': 'LAYOUT_ortho_1x1', 'keycodes': ['KC_A']}]}


# FIXME(skullydazed): Add a test for qmk.keymap.write that mocks up an FD.
