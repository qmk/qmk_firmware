"""Format C code according to QMK's style.
"""
import os
import subprocess
from shutil import which

from milc import cli


@cli.argument('files', nargs='*', arg_only=True, help='Filename(s) to format.')
@cli.subcommand("Format C code according to QMK's style.")
def cformat(cli):
    """Format C code according to QMK's style.
    """
    # Determine which version of clang-format to use
    clang_format = ['clang-format', '-i']
    for clang_version in [10, 9, 8, 7]:
        binary = 'clang-format-%d' % clang_version
        if which(binary):
            clang_format[0] = binary
            break

    # Find the list of files to format
    if cli.args.files:
        cli.args.files = [os.path.join(os.environ['ORIG_CWD'], file) for file in cli.args.files]
    else:
        ignores = ['tmk_core/protocol/usb_hid', 'quantum/template']
        for dir in ['drivers', 'quantum', 'tests', 'tmk_core']:
            for dirpath, dirnames, filenames in os.walk(dir):
                if any(i in dirpath for i in ignores):
                    dirnames.clear()

                for name in filenames:
                    if name.endswith(('.c', '.h', '.cpp')):
                        cli.args.files.append(os.path.join(dirpath, name))

    # Run clang-format on the files we've found
    try:
        subprocess.run(clang_format + cli.args.files, check=True)
        cli.log.info('Successfully formatted the C code.')

    except subprocess.CalledProcessError:
        cli.log.error('Error formatting C code!')
        return False
