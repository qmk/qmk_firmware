from pathlib import Path
from tempfile import TemporaryDirectory
from unittest.mock import patch

from qmk import keycodes


def test_list_versions_orders_multi_digit_versions_and_ignores_fragments():
    with TemporaryDirectory() as temporary:
        path = Path(temporary)
        for version in ('0.0.9', '0.0.10', '0.1.0'):
            (path / f'keycodes_{version}.hjson').write_text('{}')
        (path / 'keycodes_0.0.10_quantum.hjson').write_text('{}')
        (path / 'keycodes_invalid.hjson').write_text('{}')
        with patch.object(keycodes, 'KEYCODES_PATH', path):
            assert keycodes.list_versions() == ['0.1.0', '0.0.10', '0.0.9']


def test_list_language_versions_supports_multi_digit_patch_versions():
    with TemporaryDirectory() as temporary:
        path = Path(temporary)
        (path / 'keycodes_us_international_0.0.9.hjson').write_text('{}')
        (path / 'keycodes_us_international_0.0.10.hjson').write_text('{}')
        (path / 'keycodes_us_0.0.11.hjson').write_text('{}')
        with patch.object(keycodes, 'EXTRAS_PATH', path):
            assert keycodes.list_versions('us_international') == ['0.0.10', '0.0.9']


def test_list_languages_keeps_full_names_and_multi_digit_versions():
    with TemporaryDirectory() as temporary:
        path = Path(temporary)
        (path / 'keycodes_us_international_0.0.10.hjson').write_text('{}')
        (path / 'keycodes_french_0.0.9.hjson').write_text('{}')
        (path / 'keycodes_french_0.0.10_quantum.hjson').write_text('{}')
        with patch.object(keycodes, 'EXTRAS_PATH', path):
            assert keycodes.list_languages() == {'us_international', 'french'}
