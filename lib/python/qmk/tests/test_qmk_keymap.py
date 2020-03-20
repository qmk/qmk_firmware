import qmk.keymap


def test_template_onekey_proton_c():
    templ = qmk.keymap.template('handwired/onekey/proton_c')
    assert templ == qmk.keymap.DEFAULT_KEYMAP_C


def test_template_onekey_proton_c_json():
    templ = qmk.keymap.template('handwired/onekey/proton_c', type='json')
    assert templ == {'keyboard': 'handwired/onekey/proton_c'}


def test_template_onekey_pytest():
    templ = qmk.keymap.template('handwired/onekey/pytest')
    assert templ == 'const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {__KEYMAP_GOES_HERE__};\n'


def test_template_onekey_pytest_json():
    templ = qmk.keymap.template('handwired/onekey/pytest', type='json')
    assert templ == {'keyboard': 'handwired/onekey/pytest'}


def test_generate_onekey_pytest():
    templ = qmk.keymap.generate('handwired/onekey/pytest', 'LAYOUT', [['KC_A']])
    assert templ == 'const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {	[0] = LAYOUT(KC_A)};\n'


def test_generate_onekey_pytest_json():
    templ = qmk.keymap.generate('handwired/onekey/pytest', 'LAYOUT', [['KC_A']], type='json')
    assert templ == {'keyboard': 'handwired/onekey/pytest', 'layout': 'LAYOUT', 'layers': [['KC_A']]}


# FIXME(skullydazed): Add a test for qmk.keymap.write that mocks up an FD.
