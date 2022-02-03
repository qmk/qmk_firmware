"""Open a shell in the QMK Home directory
"""
import sys
import os

from milc import cli

from qmk.path import under_qmk_firmware


@cli.subcommand('Go to QMK Home')
def cd(cli):
    """Go to QMK Home
    """
    if not sys.stdout.isatty():
        cli.log.error("This command is for interactive usage only. For non-interactive usage, 'cd $(qmk env QMK_HOME)' is more robust.")
        sys.exit(1)

    if not under_qmk_firmware():
        # Only do anything if the user is not under qmk_firmware already
        # in order to reduce the possibility of starting multiple shells
        cli.log.info("Spawning a subshell in your QMK_HOME directory.")
        cli.log.info("Type 'exit' to get back to the parent shell.")
        if not cli.platform.lower().startswith('windows'):
            # For Linux/Mac/etc
            # Check the user's login shell from 'passwd'
            # alternatively fall back to $SHELL env var
            # and finally to '/bin/bash'.
            import getpass
            import pwd
            shell = pwd.getpwnam(getpass.getuser()).pw_shell
            if not shell:
                shell = os.environ.get('SHELL', '/bin/bash')
            # Start the new subshell
            os.execl(shell, shell)
        else:
            # For Windows
            # Check the $SHELL env var
            # and fall back to '/usr/bin/bash'.
            qmk_env = os.environ.copy()
            # Set the prompt for the new shell
            qmk_env['MSYS2_PS1'] = qmk_env['PS1']
            # Start the new subshell
            cli.run([os.environ.get('SHELL', '/usr/bin/bash')], env=qmk_env)
    else:
        cli.log.info("Already within qmk_firmware directory.")
