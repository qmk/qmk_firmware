"""Format C code according to QMK's style.
"""
import os
import subprocess

from milc import cli


@cli.entrypoint("Format C code according to QMK's style.")
def main(cli):
    """Format C code according to QMK's style.
    """
    clang_format = ['clang-format', '-i']
    code_files = []
    for dir in ['drivers', 'quantum', 'tests', 'tmk_core']:
        for dirpath, dirnames, filenames in os.walk(dir):
            if 'tmk_core/protocol/usb_hid' in dirpath:
                continue
            for name in filenames:
                if name.endswith('.c') or name.endswith('.h') or name.endswith('.cpp'):
                    code_files.append(os.path.join(dirpath, name))

    try:
        subprocess.run(clang_format + code_files, check=True)
        cli.log.info('Successfully formatted the C code.')
    except subprocess.CalledProcessError:
        cli.log.error('Error formatting C code!')
