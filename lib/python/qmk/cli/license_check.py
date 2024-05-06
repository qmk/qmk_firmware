# Copyright 2023 Nick Brassel (@tzarc)
# SPDX-License-Identifier: GPL-2.0-or-later
import re
from milc import cli
from qmk.constants import LICENSE_TEXTS
from qmk.path import normpath

L_PAREN = re.compile(r'\(\[\{\<')
R_PAREN = re.compile(r'\)\]\}\>')
PUNCTUATION = re.compile(r'[\.,;:]+')
TRASH_PREFIX = re.compile(r'^(\s|/|\*|#)+')
TRASH_SUFFIX = re.compile(r'(\s|/|\*|#|\\)+$')
SPACE = re.compile(r'\s+')
SUFFIXES = ['.c', '.h', '.cpp', '.cxx', '.hpp', '.hxx']


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


def _preformat_license_texts():
    # Pre-format all the licenses
    for _, long_licenses in LICENSE_TEXTS:
        for i in range(len(long_licenses)):
            long_licenses[i] = _simplify_text(long_licenses[i])


def _determine_suffix_condition(extensions):
    def _default_suffix_condition(s):
        return s in SUFFIXES

    conditional = _default_suffix_condition

    if extensions is not None and len(extensions) > 0:
        suffixes = [f'.{s}' if not s.startswith('.') else s for s in extensions]

        def _specific_suffix_condition(s):
            return s in suffixes

        conditional = _specific_suffix_condition

    return conditional


def _determine_file_list(inputs, conditional):
    check_list = set()
    for filename in inputs:
        if filename.is_dir():
            for file in sorted(filename.rglob('*')):
                if file.is_file() and conditional(file.suffix):
                    check_list.add(file)
        elif filename.is_file():
            if conditional(filename.suffix):
                check_list.add(filename)

    return list(sorted(check_list))


def _detect_license_from_file_contents(filename, absolute=False, short=False):
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
            if short:
                print(f'{filename_out} UNKNOWN')
            else:
                cli.log.error(f'{{fg_cyan}}{filename_out}{{fg_reset}} -- unknown license, or no license detected!')
            return False

        if short:
            print(f'{filename_out} {license}')
        else:
            cli.log.info(f'{{fg_cyan}}{filename_out}{{fg_reset}} -- license detected: {license} (SPDX License Identifier)')
        return True

    else:
        simple_text = _simplify_text(data)
        for short_license, long_licenses in LICENSE_TEXTS:
            for long_license in long_licenses:
                if long_license in simple_text:
                    if short:
                        print(f'{filename_out} {short_license}')
                    else:
                        cli.log.info(f'{{fg_cyan}}{filename_out}{{fg_reset}} -- license detected: {short_license} (Full text)')
                    return True

        if short:
            print(f'{filename_out} UNKNOWN')
        else:
            cli.log.error(f'{{fg_cyan}}{filename_out}{{fg_reset}} -- unknown license, or no license detected!')

    return False


@cli.argument('inputs', nargs='*', arg_only=True, type=normpath, help='List of input files or directories.')
@cli.argument('-s', '--short', action='store_true', help='Short output.')
@cli.argument('-a', '--absolute', action='store_true', help='Print absolute paths.')
@cli.argument('-e', '--extension', arg_only=True, action='append', default=[], help='Override list of extensions. Can be specified multiple times for multiple extensions.')
@cli.subcommand('File license check.', hidden=False if cli.config.user.developer else True)
def license_check(cli):
    _preformat_license_texts()

    conditional = _determine_suffix_condition(cli.args.extension)
    check_list = _determine_file_list(cli.args.inputs, conditional)

    failed = False
    for filename in sorted(check_list):
        if not _detect_license_from_file_contents(filename, absolute=cli.args.absolute, short=cli.args.short):
            failed = True

    if failed:
        return False
