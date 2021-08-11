"""This script generates the XAP protocol documentation.
"""
from milc import cli
from qmk.xap.gen_docs.generator import generate_docs


@cli.subcommand('Generates the XAP protocol documentation.', hidden=False if cli.config.user.developer else True)
def xap_generate_docs(cli):
    """Generates the XAP protocol documentation by merging the definitions files, and producing the corresponding Markdown document under `/docs/`.
    """
    generate_docs()