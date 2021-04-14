"""Open a shell in the QMK Home directory
"""
import pty
import getpass
import pwd

from milc import cli


@cli.subcommand('Go to QMK Home')
def cd(cli):
    """Go to QMK Home
    """
    pty.spawn(pwd.getpwnam(getpass.getuser()).pw_shell)
