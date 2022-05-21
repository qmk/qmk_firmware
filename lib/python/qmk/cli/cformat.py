"""Point people to the new command name.
"""
import sys
from pathlib import Path

from milc import cli


@cli.argument('-n', '--dry-run', arg_only=True, action='store_true', help="Flag only, don't automatically format.")
@cli.argument('-b', '--base-branch', default='origin/master', help='Branch to compare to diffs to.')
@cli.argument('-a', '--all-files', arg_only=True, action='store_true', help='Format all core files.')
@cli.argument('--core-only', arg_only=True, action='store_true', help='Format core files only.')
@cli.argument('files', nargs='*', arg_only=True, help='Filename(s) to format.')
@cli.subcommand('Pointer to the new command name: qmk format-c.', hidden=True)
def cformat(cli):
    """Pointer to the new command name: qmk format-c.
    """
    cli.log.warning('"qmk cformat" has been renamed to "qmk format-c". Please use the new command in the future.')
    argv = [sys.executable, *sys.argv]
    argv[argv.index('cformat')] = 'format-c'
    script_path = Path(argv[1])
    script_path_exe = Path(f'{argv[1]}.exe')

    if not script_path.exists() and script_path_exe.exists():
        # For reasons I don't understand ".exe" is stripped from the script name on windows.
        argv[1] = str(script_path_exe)

    return cli.run(argv, capture_output=False).returncode
