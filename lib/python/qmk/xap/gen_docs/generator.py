"""This script generates the XAP protocol documentation.
"""
import hjson
from qmk.constants import QMK_FIRMWARE
from qmk.xap.common import get_xap_definition_files, update_xap_definitions


def _update_type_docs(overall):
    defs = overall['type_docs']

    type_docs = []
    for (k, v) in sorted(defs.items(), key=lambda x: x[0]):
        type_docs.append(f'| _{k}_ | {v} |')

    desc_str = "\n".join(type_docs)

    overall['documentation']['!type_docs!'] = f'''\
| Name | Definition |
| -- | -- |
{desc_str}
'''


def _update_term_definitions(overall):
    defs = overall['term_definitions']

    term_descriptions = []
    for (k, v) in sorted(defs.items(), key=lambda x: x[0]):
        term_descriptions.append(f'| _{k}_ | {v} |')

    desc_str = "\n".join(term_descriptions)

    overall['documentation']['!term_definitions!'] = f'''\
| Name | Definition |
| -- | -- |
{desc_str}
'''


def _update_response_flags(overall):
    flags = overall['response_flags']['bits']
    for n in range(0, 8):
        if str(n) not in flags:
            flags[str(n)] = {"name": "-", "description": "-"}

    header = '| ' + " | ".join([f'Bit {n}' for n in range(7, -1, -1)]) + ' |'
    dividers = '|' + "|".join(['--' for n in range(7, -1, -1)]) + '|'
    bit_names = '| ' + " | ".join([flags[str(n)]['name'] for n in range(7, -1, -1)]) + ' |'

    bit_descriptions = ''
    for n in range(7, -1, -1):
        bit_desc = flags[str(n)]
        if bit_desc['name'] != '-':
            desc = bit_desc['description']
            bit_descriptions = bit_descriptions + f'\n* `Bit {n}`: {desc}'

    overall['documentation']['!response_flags!'] = f'''\
{header}
{dividers}
{bit_names}
{bit_descriptions}
'''


def generate_docs():
    """Generates the XAP protocol documentation by merging the definitions files, and producing the corresponding Markdown document under `/docs/`.
    """
    docs_list = []

    overall = None
    for file in get_xap_definition_files():

        overall = update_xap_definitions(overall, hjson.load(file.open(encoding='utf-8')))

        try:
            if 'type_docs' in overall:
                _update_type_docs(overall)
            if 'term_definitions' in overall:
                _update_term_definitions(overall)
            if 'response_flags' in overall:
                _update_response_flags(overall)
        except:
            print(hjson.dumps(overall))
            exit(1)

        output_doc = QMK_FIRMWARE / "docs" / f"{file.stem}.md"
        docs_list.append(output_doc)

        with open(output_doc, "w", encoding='utf-8') as out_file:
            for e in overall['documentation']['order']:
                out_file.write(overall['documentation'][e].strip())
                out_file.write('\n\n')

    output_doc = QMK_FIRMWARE / "docs" / f"xap_protocol.md"
    with open(output_doc, "w", encoding='utf-8') as out_file:
        out_file.write('''\
# XAP Protocol Reference

''')

        for file in reversed(sorted(docs_list)):
            ver = file.stem[4:]
            out_file.write(f'* [XAP Version {ver}]({file.name})\n')
