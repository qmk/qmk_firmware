"""Convert raw KLE to JSON
"""
import json
import os
from pathlib import Path

from milc import cli
from kle2xy import KLE2xy

from qmk.converter import kle2qmk
from qmk.json_encoders import InfoJSONEncoder


@cli.argument('filename', help='The KLE raw txt to convert')
@cli.argument('-f', '--force', action='store_true', help='Flag to overwrite current info.json')
@cli.subcommand('Convert a KLE layout to a Configurator JSON', hidden=False if cli.config.user.developer else True)
def kle2json(cli):
    """Convert a KLE layout to QMK's layout format.
    """  # If filename is a path
    if cli.args.filename.startswith("/") or cli.args.filename.startswith("./"):
        file_path = Path(cli.args.filename)
    # Otherwise assume it is a file name
    else:
        file_path = Path(os.environ['ORIG_CWD'], cli.args.filename)
    # Check for valid file_path for more graceful failure
    if not file_path.exists():
        cli.log.error('File {fg_cyan}%s{style_reset_all} was not found.', file_path)
        return False
    out_path = file_path.parent
    raw_code = file_path.read_text(encoding='utf-8')
    # Check if info.json exists, allow overwrite with force
    if Path(out_path, "info.json").exists() and not cli.args.force:
        cli.log.error('File {fg_cyan}%s/info.json{style_reset_all} already exists, use -f or --force to overwrite.', out_path)
        return False
    try:
        # Convert KLE raw to x/y coordinates (using kle2xy package from skullydazed)
        kle = KLE2xy(raw_code)
    except Exception as e:
        cli.log.error('Could not parse KLE raw data: %s', raw_code)
        cli.log.exception(e)
        return False
    keyboard = {
        'keyboard_name': kle.name,
        'url': '',
        'maintainer': 'qmk',
        'width': kle.columns,
        'height': kle.rows,
        'layouts': {
            'LAYOUT': {
                'layout': kle2qmk(kle)
            }
        },
    }

    # Write our info.json
    keyboard = json.dumps(keyboard, indent=4, separators=(', ', ': '), sort_keys=False, cls=InfoJSONEncoder)
    info_json_file = out_path / 'info.json'

    info_json_file.write_text(keyboard)
    cli.log.info('Wrote out {fg_cyan}%s/info.json', out_path)
