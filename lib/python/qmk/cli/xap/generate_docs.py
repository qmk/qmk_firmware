"""This script generates the XAP protocol documentation.
"""
import hjson

from milc import cli

from qmk.constants import QMK_FIRMWARE
from qmk.path import normpath
from qmk.commands import dump_lines
from qmk.keyboard import keyboard_completer, keyboard_folder
from qmk.xap.common import get_xap_definition_files, update_xap_definitions, merge_xap_defs, render_xap_output


def _patch_spec_for_docs(spec):
    # Inject dummy bits for unspecified response flags
    for n in range(0, 8):
        if str(n) not in spec['response_flags']['bits']:
            spec['response_flags']['bits'][str(n)] = {'name': '', 'description': '', 'define': '-'}


@cli.subcommand('Generates the XAP protocol documentation.', hidden=False if cli.config.user.developer else True)
def xap_generate_docs(cli):
    """Generates the XAP protocol documentation by merging the definitions files, and producing the corresponding Markdown document under `/docs/`.
    """
    versions = []

    overall = None
    for file in get_xap_definition_files():
        overall = update_xap_definitions(overall, hjson.load(file.open(encoding='utf-8')))

        _patch_spec_for_docs(overall)

        output_doc = QMK_FIRMWARE / "docs" / f"{file.stem}.md"
        versions.append(overall['version'])
        output = render_xap_output('docs', 'docs.md.j2', overall)
        with open(output_doc, "w", encoding='utf-8') as out_file:
            out_file.write(output)

    output_doc = QMK_FIRMWARE / "docs" / "xap_protocol.md"
    output = render_xap_output('docs', 'versions.md.j2', overall, versions=versions)
    with open(output_doc, "w", encoding='utf-8') as out_file:
        out_file.write(output)


@cli.argument('-o', '--output', arg_only=True, type=normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.argument('-km', '--keymap', help='The keymap\'s name - "default" if not specified')
@cli.argument('-kb', '--keyboard', required=True, type=keyboard_folder, completer=keyboard_completer, help='Name of the keyboard')
@cli.subcommand('Generates the XAP protocol documentation for a given keyboard/keymap.', hidden=False if cli.config.user.developer else True)
def xap_generate_keyboard_docs(cli):
    """Generates the XAP protocol documentation for a given keyboard/keymap and producing the corresponding Markdown.
    """
    spec = merge_xap_defs(cli.args.keyboard, cli.args.keymap or 'default')

    _patch_spec_for_docs(spec)

    output = render_xap_output('docs', 'docs.md.j2', spec)
    dump_lines(cli.args.output, output.split('\n'), cli.args.quiet)
