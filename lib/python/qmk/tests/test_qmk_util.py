from pathlib import Path
from tempfile import TemporaryDirectory

from qmk import util


def test_triplet_to_bcd_formats_version_components():
    assert util.triplet_to_bcd('1.2.3') == '0x01020003'
    assert util.triplet_to_bcd('12.34.5678') == '0x12345678'


def test_triplet_to_bcd_accepts_suffix_after_version():
    assert util.triplet_to_bcd('1.2.3-4-gabcdef') == '0x01020003'


def test_triplet_to_bcd_returns_zero_for_non_matching_version():
    assert util.triplet_to_bcd('invalid') == '0x00000000'
    assert util.triplet_to_bcd(None) == '0x00000000'
    assert util.triplet_to_bcd('') == '0x00000000'
    assert util.triplet_to_bcd('1.2') == '0x00000000'
    # assert util.triplet_to_bcd('1.2.3.4') == '0x00000000'
    assert util.triplet_to_bcd('1.-2.3') == '0x00000000'
    assert util.triplet_to_bcd('\uff11.2.3') == '0x00000000'
    assert util.triplet_to_bcd('1.2.a') == '0x00000000'
    assert util.triplet_to_bcd('0.0.10000') == '0x00000000'
    assert util.triplet_to_bcd('0.100.0') == '0x00000000'
    assert util.triplet_to_bcd('100.0.0') == '0x00000000'


def test_is_valid_bcd_string():
    assert util.is_valid_bcd_string('1.2.3')
    assert util.is_valid_bcd_string('12.34.5678')


def test_is_valid_bcd_string_returns_zero_for_non_matching_version():
    assert not util.is_valid_bcd_string(None)
    assert not util.is_valid_bcd_string('')
    assert not util.is_valid_bcd_string('1.2')
    assert not util.is_valid_bcd_string('1.2.3.4')
    assert not util.is_valid_bcd_string('1.-2.3')
    assert not util.is_valid_bcd_string('\uff11.2.3')
    assert not util.is_valid_bcd_string('1.2.a')
    assert not util.is_valid_bcd_string('0.0.10000')
    assert not util.is_valid_bcd_string('0.100.0')
    assert not util.is_valid_bcd_string('100.0.0')


def test_list_versions_orders_multi_digit_versions():
    with TemporaryDirectory() as temporary:
        path = Path(temporary)
        for version in ('0.0.9', '0.0.10', '0.1.0'):
            (path / f'{version}.hjson').touch()
        assert util.list_file_versions(path) == ['0.0.9', '0.0.10', '0.1.0']


def test_list_versions_can_reverse_order():
    with TemporaryDirectory() as temporary:
        path = Path(temporary)
        for version in ('0.0.9', '0.0.10', '0.1.0'):
            (path / f'{version}.hjson').touch()
        assert util.list_file_versions(path, reverse=True) == ['0.1.0', '0.0.10', '0.0.9']


def test_list_versions_supports_custom_extension():
    with TemporaryDirectory() as temporary:
        path = Path(temporary)
        (path / '0.0.1.json').touch()
        (path / '0.0.2.hjson').touch()
        assert util.list_file_versions(path, ext='json') == ['0.0.1']


def test_list_versions_ignores_non_version_files():
    with TemporaryDirectory() as temporary:
        path = Path(temporary)
        (path / '0.0.1.hjson').touch()
        (path / 'invalid.hjson').touch()
        assert util.list_file_versions(path) == ['0.0.1']


def test_list_versions_ignores_suffixes():
    with TemporaryDirectory() as temporary:
        path = Path(temporary)
        (path / '0.0.1.hjson').touch()
        (path / '0.0.1_quantum.hjson').touch()
        assert util.list_file_versions(path) == ['0.0.1']


def test_list_versions_ignores_too_large_bcd():
    with TemporaryDirectory() as temporary:
        path = Path(temporary)
        for version in ('99.99.9999', '0.0.10000', '0.100.0', '100.0.0'):
            (path / f'{version}.hjson').touch()
        assert util.list_file_versions(path) == ['99.99.9999']


def test_list_versions_ignores_invalid_bcd():
    with TemporaryDirectory() as temporary:
        path = Path(temporary)
        for version in ('1.2', '1.2.3.4', '1.-2.3', '\uff11.2.3', '1.2.a'):
            (path / f'{version}.hjson').touch()
        assert util.list_file_versions(path) == []


def test_list_versions_finds_only_with_prefix():
    with TemporaryDirectory() as temporary:
        path = Path(temporary)
        (path / 'keycodes_0.0.1.hjson').touch()
        (path / 'keycodes_us_0.0.2.hjson').touch()
        assert util.list_file_versions(path, prefix='keycodes_') == ['0.0.1']


def test_list_version_files_orders_multi_digit_versions():
    with TemporaryDirectory() as temporary:
        path = Path(temporary)
        for version in ('0.0.9', '0.0.10', '0.1.0'):
            (path / f'{version}.hjson').touch()
        assert util.list_version_files(path) == [
            path / '0.0.9.hjson',
            path / '0.0.10.hjson',
            path / '0.1.0.hjson',
        ]


def test_list_version_files_forwards_args():
    with TemporaryDirectory() as temporary:
        path = Path(temporary)
        (path / 'keycodes_0.0.9.json').touch()
        (path / 'keycodes_0.0.10.json').touch()
        (path / 'keycodes_0.1.0.hjson').touch()
        (path / 'other_0.1.0.json').touch()
        assert util.list_version_files(path, ext='json', prefix='keycodes_', reverse=True) == [
            path / 'keycodes_0.0.10.json',
            path / 'keycodes_0.0.9.json',
        ]
