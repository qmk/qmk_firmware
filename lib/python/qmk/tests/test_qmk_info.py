from qmk.info import info_json
from qmk.json_schema import deep_update


def test_deep_update_child_overrides_parent():
    """Test that deep_update gives priority to newdict values.
    """
    parent = {'keyboard_name': 'parent', 'usb': {'vid': '0x1234', 'pid': '0x0001'}}
    child = {'keyboard_name': 'child', 'usb': {'pid': '0x0002'}}
    result = deep_update(parent, child)
    assert result['keyboard_name'] == 'child'
    assert result['usb']['vid'] == '0x1234'
    assert result['usb']['pid'] == '0x0002'


def test_deep_update_preserves_parent_only_keys():
    """Test that keys only in the parent are preserved after deep_update.
    """
    parent = {'a': 1, 'b': 2}
    child = {'b': 3, 'c': 4}
    result = deep_update(parent, child)
    assert result == {'a': 1, 'b': 3, 'c': 4}


def test_info_json_child_overrides_parent():
    """Test that child keyboard.json values override parent info.json values.

    handwired/pytest/override/keyboard.json sets keyboard_name to 'pytest_override'
    while the parent handwired/pytest/info.json sets keyboard_name to 'pytest'.
    The child value should win.
    """
    info_data = info_json('handwired/pytest/override')
    assert info_data['keyboard_name'] == 'pytest_override'
    assert info_data['manufacturer'] == 'test_override'


def test_info_json_child_overrides_nested_parent():
    """Test that child keyboard.json overrides nested parent values while preserving siblings.

    handwired/pytest/override/keyboard.json sets usb.pid to '0x0000'
    while the parent handwired/pytest/info.json sets usb.vid to '0xFEED' and usb.pid to '0x6465'.
    The child pid should win and the parent vid should be preserved.
    """
    info_data = info_json('handwired/pytest/override')
    assert info_data['usb']['pid'] == '0x0000'
    assert info_data['usb']['vid'] == '0xFEED'


def test_info_json_parent_values_used_when_child_does_not_override():
    """Test that parent values are used when the child does not override them.

    handwired/pytest/basic/keyboard.json does not set keyboard_name,
    so the parent value 'pytest' from handwired/pytest/info.json should be used.
    """
    info_data = info_json('handwired/pytest/basic')
    assert info_data['keyboard_name'] == 'pytest'
    assert info_data['processor'] == 'atmega32u4'
