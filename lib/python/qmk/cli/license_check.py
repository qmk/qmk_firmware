import re
from pathlib import Path
from milc import cli

LICENSE_TEXTS = [
    (
        'GPL-2.0-or-later', [
            """\
        This program is free software; you can redistribute it and/or
        modify it under the terms of the GNU General Public License
        as published by the Free Software Foundation; either version 2
        of the License, or (at your option) any later version.
        """, """\
        This program is free software; you can redistribute it and/or
        modify it under the terms of the GNU General Public License
        as published by the Free Software Foundation; either version 2
        of the License, or any later version.
        """
        ]
    ),
    ('GPL-2.0-only', ["""\
        This program is free software; you can redistribute it and/or
        modify it under the terms of the GNU General Public License as
        published by the Free Software Foundation; version 2.
        """]),
    (
        'GPL-3.0-or-later', [
            """\
        This program is free software: you can redistribute it and/or
        modify it under the terms of the GNU General Public License as
        published by the Free Software Foundation, either version 3 of
        the License, or (at your option) any later version.
        """, """\
        This program is free software: you can redistribute it and/or
        modify it under the terms of the GNU General Public License as
        published by the Free Software Foundation, either version 3 of
        the License, or any later version.
        """
        ]
    ),
    ('GPL-3.0-only', ["""\
        This program is free software: you can redistribute it and/or
        modify it under the terms of the GNU General Public License as
        published by the Free Software Foundation, version 3.
        """]),
    ('Apache-2.0', ["""\
        Licensed under the Apache License, Version 2.0 (the "License");
        you may not use this file except in compliance with the License.
        """]),
]

L_PAREN = re.compile(r'\(\[\{\<')
R_PAREN = re.compile(r'\)\]\}\>')
PUNCTUATION = re.compile(r'[\.,;:]+')
TRASH_PREFIX = re.compile(r'^(\s|/|\*|#)+')
TRASH_SUFFIX = re.compile(r'(\s|/|\*|#|\\)+$')
SPACE = re.compile(r'\s+')
SUFFIXES = ['.c', '.h', '.cpp', '.cxx', '.hpp', '.hxx', '.py']  # , '.def', '.mk']  # ?


def _simplify_text(input):
    lines = input.lower().split('\n')
    lines = [PUNCTUATION.sub('', line) for line in lines]
    lines = [TRASH_PREFIX.sub('', line) for line in lines]
    lines = [TRASH_SUFFIX.sub('', line) for line in lines]
    lines = [SPACE.sub(' ', line) for line in lines]
    lines = [L_PAREN.sub('(', line) for line in lines]
    lines = [R_PAREN.sub(')', line) for line in lines]
    lines = [line.strip() for line in lines]
    lines = [line for line in lines if line is not None and line != '']
    return ' '.join(lines)


def _detect_license_from_file_contents(filename, absolute=False):
    data = filename.read_text(encoding='utf-8', errors='ignore')
    filename_out = str(filename.absolute()) if absolute else str(filename)

    if 'SPDX-License-Identifier:' in data:
        res = data.split('SPDX-License-Identifier:')
        license = re.split(r'\s|//|\*', res[1].strip())[0].strip()
        found = False
        for short_license, _ in LICENSE_TEXTS:
            if license.lower() == short_license.lower():
                license = short_license
                found = True
                break

        if not found:
            if cli.args.short:
                print(f'{filename_out} UNKNOWN')
            else:
                cli.log.error(f'{{fg_cyan}}{filename_out}{{fg_reset}} -- unknown license, or no license detected!')
            return False

        if cli.args.short:
            print(f'{filename_out} {license}')
        else:
            cli.log.info(f'{{fg_cyan}}{filename_out}{{fg_reset}} -- license detected: {license} (SPDX License Identifier)')
        return True

    else:
        simple_text = _simplify_text(data)
        for short_license, long_licenses in LICENSE_TEXTS:
            for long_license in long_licenses:
                if long_license in simple_text:
                    if cli.args.short:
                        print(f'{filename_out} {short_license}')
                    else:
                        cli.log.info(f'{{fg_cyan}}{filename_out}{{fg_reset}} -- license detected: {short_license} (Full text)')
                    return True

        if cli.args.short:
            print(f'{filename_out} UNKNOWN')
        else:
            cli.log.error(f'{{fg_cyan}}{filename_out}{{fg_reset}} -- unknown license, or no license detected!')

    return False


@cli.argument('filenames', nargs='*', arg_only=True, type=Path, help='Input files')
@cli.argument('-s', '--short', action='store_true', help='Short output')
@cli.argument('-a', '--absolute', action='store_true', help='Print absolute paths')
@cli.subcommand('File license check.', hidden=False if cli.config.user.developer else True)
def license_check(cli):
    # Pre-format all the licenses
    for _, long_licenses in LICENSE_TEXTS:
        for i in range(len(long_licenses)):
            long_licenses[i] = _simplify_text(long_licenses[i])

    check_list = set()
    for filename in sorted(cli.args.filenames):
        if filename.is_dir():
            for file in sorted(filename.rglob('*')):
                if file.is_file() and file.suffix in SUFFIXES:
                    check_list.add(file)
        elif filename.is_file():
            if filename.suffix in SUFFIXES:
                check_list.add(filename)

    failed = False
    for filename in sorted(check_list):
        if not _detect_license_from_file_contents(filename, absolute=cli.args.absolute):
            failed = True

    if failed:
        return False
