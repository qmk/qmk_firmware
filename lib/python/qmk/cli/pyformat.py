"""Point people to the new command name.
"""
import sys
from pathlib import Path

from milc import cli


@cli.argument('-n', '--dry-run', arg_only=True, action='store_true', help="Don't actually format.")
@cli.subcommand('Pointer to the new command name: qmk format-python.', hidden=False if cli.config.user.developer else True)
def pyformat(cli):
    """Pointer to the new command name: qmk format-python.
    """
    cli.log.warning('"qmk pyformat" has been renamed to "qmk format-python". Please use the new command in the future.')
    argv = [sys.executable, *sys.argv]
    argv[argv.index('pyformat')] = 'format-python'
    script_path = Path(argv[1])
    script_path_exe = Path(f'{argv[1]}.exe')

    if not script_path.exists() and script_path_exe.exists():
        # For reasons I don't understand ".exe" is stripped from the script name on windows.
        argv[1] = str(script_path_exe)

    return cli.run(argv, capture_output=False).returncode
