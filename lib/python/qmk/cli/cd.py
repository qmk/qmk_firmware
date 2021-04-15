"""Open a shell in the QMK Home directory
"""
import os

from milc import cli

from qmk.path import under_qmk_firmware


@cli.subcommand('Go to QMK Home')
def cd(cli):
    """Go to QMK Home
    """
    if not under_qmk_firmware():
        # Only do anything if the user is not under qmk_firmware already
        # in order to reduce the possibility of starting multiple shells
        if not cli.platform.lower().startswith('windows'):
            # For Linux/Mac/etc
            # Check the user's login shell from 'passwd'
            # alternatively fall back to $SHELL env var
            # and finally to '/bin/bash'.
            import pty, getpass, pwd
            shell = pwd.getpwnam(getpass.getuser()).pw_shell
            if not shell:
                shell = os.environ.get('SHELL', '/bin/bash')
            pty.spawn(shell)
        else:
            # For Windows
            # We just start a new subshell using $SHELL and
            # fall back to '/usr/bin/bash'.
            from qmk.commands import run
            qmk_env = os.environ.copy()
            # Set the prompt for the new shell
            qmk_env['MSYS2_PS1'] = qmk_env['PS1']
            run([os.environ.get('SHELL', '/usr/bin/bash')], env=qmk_env)
