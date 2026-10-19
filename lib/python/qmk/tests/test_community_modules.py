from pathlib import Path
from tempfile import TemporaryDirectory
from unittest.mock import patch

from qmk import community_modules


def test_list_supports_multi_digit_patch_versions():
    with TemporaryDirectory() as temporary:
        path = Path(temporary)
        (path / '0.0.9.hjson').write_text('{}')
        (path / '0.0.10.hjson').write_text('{}')

        with patch.object(community_modules, 'HOOKS_PATH', path):
            _data, version, _minor, _major, _patch = community_modules.module_api_list()
            assert version == '0.0.10'
