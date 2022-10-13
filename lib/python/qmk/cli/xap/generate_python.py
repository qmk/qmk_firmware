"""This script generates the python XAP client.
"""
from qmk.constants import QMK_FIRMWARE, GPL2_HEADER_SH_LIKE, GENERATED_HEADER_SH_LIKE

from qmk.xap.common import latest_xap_defs, render_xap_output
from qmk.commands import dump_lines

from milc import cli


@cli.subcommand('Generates the python XAP client.', hidden=False if cli.config.user.developer else True)
def xap_generate_python(cli):
    defs = latest_xap_defs()

    parent = QMK_FIRMWARE / 'lib' / 'python' / 'xap_client'
    for name in ['types.py', 'routes.py', 'constants.py']:
        lines = [GPL2_HEADER_SH_LIKE, GENERATED_HEADER_SH_LIKE]

        output = render_xap_output('client/python', f'{name}.j2', defs)
        lines += output.split('\n')

        dump_lines(parent / name, lines)
