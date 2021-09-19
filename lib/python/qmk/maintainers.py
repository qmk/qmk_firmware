from pathlib import Path

from codeowners import CodeOwners

from qmk.json_schema import json_load

codeowners_file = Path('CODEOWNERS')
codeowners = CodeOwners(codeowners_file.read_text())


def maintainers(file):
    """Yields maintainers for a file.
    """
    maintainers = [owner[1] for owner in codeowners.of(str(file))]
    file_dir = file if file.is_dir() else file.parent

    cur_path = Path('.')

    for path_part in file_dir.parts:
        cur_path = cur_path / path_part
        info_file = cur_path / 'info.json'
        if info_file.exists():
            new_info_data = json_load(info_file)
            maintainers = new_info_data.get('maintainer').replace(',', ' ').split()
            maintainers = ['@' + maintainer for maintainer in maintainers]

    for maintainer in maintainers:
        yield '@qmk/collaborators' if maintainer == 'qmk' else maintainer
