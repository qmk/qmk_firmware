import re
from pathlib import Path
from milc import cli

licenses = [
    ('GPL-2.0-or-later',
        ["""
        This program is free software; you can redistribute it and/or
        modify it under the terms of the GNU General Public License
        as published by the Free Software Foundation; either version 2
        of the License, or (at your option) any later version.
        ""","""
        This program is free software; you can redistribute it and/or
        modify it under the terms of the GNU General Public License
        as published by the Free Software Foundation; either version 2
        of the License, or any later version.
        """]),
    ('GPL-2.0-only',
        ["""
        This program is free software; you can redistribute it and/or
        modify it under the terms of the GNU General Public License as
        published by the Free Software Foundation; version 2.
        """])
]

lparen = re.compile(r'\(\[\{\<')
rparen = re.compile(r'\)\]\}\>')
punctuation = re.compile(r'[\.,;:]+')
trash_prefix = re.compile(r'^(\s|/|\*|#)+')
trash_suffix = re.compile(r'(\s|/|\*|#|\\)+$')
spaces = re.compile(r'\s+')

def _simplify_text(input):
    lines = input.split('\n')
    lines = [l.lower() for l in lines]
    lines = [punctuation.sub('', l) for l in lines]
    lines = [trash_prefix.sub('', l) for l in lines]
    lines = [trash_suffix.sub('', l) for l in lines]
    lines = [spaces.sub(' ', l) for l in lines]
    lines = [lparen.sub('(', l) for l in lines]
    lines = [rparen.sub(')', l) for l in lines]
    lines = [l.strip() for l in lines]
    lines = [l for l in lines if l is not None and l != '']
    return ' '.join(lines)

@cli.argument('filename', arg_only=True, type=Path, help='Input file')
@cli.subcommand('File license check.', hidden=False if cli.config.user.developer else True)
def license_check(cli):
    data = cli.args.filename.read_text()
    if 'SPDX-License-Identifier:' in data:

        res = data.split('SPDX-License-Identifier:')
        license = re.split(r'\s|//|\*', res[1].strip())[0].strip()
        cli.log.info(f'{{fg_cyan}}{cli.args.filename}{{fg_reset}} -- license found: {license} (SPDX License Identifier)')
        return True

    else:

        linear_text = _simplify_text(data)

        for short_license, long_licenses in licenses:
            for long_license in long_licenses:
                license_text = _simplify_text(long_license)
                if license_text in linear_text:
                    cli.log.info(f'{{fg_cyan}}{cli.args.filename}{{fg_reset}} -- license found: {short_license} (Raw text)')
                    return True

    cli.log.error(f'{{fg_cyan}}{cli.args.filename}{{fg_reset}} -- no license found, or unknown license!')
    return False
