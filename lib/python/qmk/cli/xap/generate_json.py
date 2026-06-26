"""This script generates the consolidated XAP protocol definitions.
"""
import hjson
from milc import cli
from qmk.xap.common import latest_xap_defs


@cli.subcommand('Generates the consolidated XAP protocol definitions.', hidden=False if cli.config.user.developer else True)
def xap_generate_json(cli):
    """Generates the consolidated XAP protocol definitions.
    """
    defs = latest_xap_defs()
    print(hjson.dumps(defs))
