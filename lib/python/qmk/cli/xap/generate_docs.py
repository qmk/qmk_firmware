"""This script generates the XAP protocol documentation.
"""
import hjson

from milc import cli

from qmk.constants import QMK_FIRMWARE
from qmk.xap.common import get_xap_definition_files, update_xap_definitions, render_xap_output


@cli.subcommand('Generates the XAP protocol documentation.', hidden=False if cli.config.user.developer else True)
def xap_generate_docs(cli):
    """Generates the XAP protocol documentation by merging the definitions files, and producing the corresponding Markdown document under `/docs/`.
    """
    versions = []

    overall = None
    for file in get_xap_definition_files():
        overall = update_xap_definitions(overall, hjson.load(file.open(encoding='utf-8')))

        # Inject dummy bits for unspecified response flags
        for n in range(0, 8):
            if str(n) not in overall['response_flags']['bits']:
                overall['response_flags']['bits'][str(n)] = {'name': '', 'description': '', 'define': '-'}

        output_doc = QMK_FIRMWARE / "docs" / f"{file.stem}.md"
        versions.append(overall['version'])
        output = render_xap_output('docs', 'docs.md.j2', overall)
        with open(output_doc, "w", encoding='utf-8') as out_file:
            out_file.write(output)

    output_doc = QMK_FIRMWARE / "docs" / "xap_protocol.md"
    output = render_xap_output('docs', 'versions.md.j2', overall, versions=versions)
    with open(output_doc, "w", encoding='utf-8') as out_file:
        out_file.write(output)
