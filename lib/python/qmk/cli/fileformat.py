"""Point people to the new command name.
"""
import sys
from pathlib import Path

from milc import cli


@cli.subcommand('Pointer to the new command name: qmk format-text.', hidden=True)
def fileformat(cli):
    """Pointer to the new command name: qmk format-text.
    """
    cli.log.warning('"qmk fileformat" has been renamed to "qmk format-text". Please use the new command in the future.')
    argv = [sys.executable, *sys.argv]
    argv[argv.index('fileformat')] = 'format-text'
    script_path = Path(argv[1])
    script_path_exe = Path(f'{argv[1]}.exe')

    if not script_path.exists() and script_path_exe.exists():
        # For reasons I don't understand ".exe" is stripped from the script name on windows.
        argv[1] = str(script_path_exe)

    return cli.run(argv, capture_output=False).returncode
