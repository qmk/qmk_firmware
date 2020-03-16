"""This script creates a starting point for a keyboard's VIA support.
"""

from pathlib import Path
import json

from qmk.path import is_keyboard
import qmk.keymap
from qmk.errors import KeymapAlreadyExistsError, NoSuchKeyboardError

from milc import cli


@cli.argument('-kb', '--keyboard', required=True, help='Specify keyboard name. Example: 1upkeyboards/1up60hse')
@cli.subcommand('Creates a new VIA keymap for the keyboard of your choosing')
def via_keymap(cli):
    if is_keyboard(cli.config.via_keymap.keyboard):
        try:
            qmk.keymap.via_keymap(cli.config.via_keymap.keyboard)

            via_json = Path('%s_via.json' % cli.config.via_keymap.keyboard.replace('/', '_'))
            try:
                config_h = qmk.keymap.parse_config_h(cli.config.via_keymap.keyboard)
                json_content = { 'name': config_h['name'], 'vendorId': config_h['vid'], 'productId': config_h['pid'], 'lighting': { 'extends': 'none' }, 'matrix': { 'rows': config_h['rows'], 'cols': config_h['cols'] }, 'layouts': { 'keymap': ["https://caniusevia.com/docs/layouts"] }}
                via_json.write_text(json.dumps(json_content))
            except NoSuchKeyboardError as e:
                cli.log.error('%s is not a valid QMK keyboard.', cli.config.via_keymap.keyboard)
        except KeymapAlreadyExistsError as e:
            cli.log.error(e)
    else:
        cli.log.error('%s is not a valid QMK keyboard.', cli.config.via_keymap.keyboard)
