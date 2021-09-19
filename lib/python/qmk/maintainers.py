from pathlib import Path

from qmk.json_schema import json_load


def maintainers(file):
    """Yields maintainers for a file.
    """
    maintainers = 'qmk'
    file_dir = file if file.is_dir() else file.parent

    cur_path = Path('.')

    for path_part in file_dir.parts:
        cur_path = cur_path / path_part
        info_file = cur_path / 'info.json'
        if info_file.exists():
            new_info_data = json_load(info_file)
            maintainers = new_info_data.get('maintainer', maintainers)

    for maintainer in maintainers.replace(',', ' ').split():
        yield 'qmk/collaborators' if maintainer == 'qmk' else maintainer