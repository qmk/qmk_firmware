"""Format C code according to QMK's style.
"""
import os
import subprocess

from milc import cli


@cli.argument('files', nargs='*', arg_only=True, help='Filename(s) to format.')
@cli.subcommand("Format C code according to QMK's style.")
def cformat(cli):
    """Format C code according to QMK's style.
    """
    clang_format = ['clang-format', '-i']

    # Find the list of files to format
    if not cli.args.files:
        for dir in ['drivers', 'quantum', 'tests', 'tmk_core']:
            for dirpath, dirnames, filenames in os.walk(dir):
                if 'tmk_core/protocol/usb_hid' in dirpath:
                    continue

                for name in filenames:
                    if name.endswith('.c') or name.endswith('.h') or name.endswith('.cpp'):
                        cli.args.files.append(os.path.join(dirpath, name))

    # Run clang-format on the files we've found
    try:
        subprocess.run(clang_format + cli.args.files, check=True)
        cli.log.info('Successfully formatted the C code.')

    except subprocess.CalledProcessError:
        cli.log.error('Error formatting C code!')
        return False
