"""Generate and apply a QMK PID

Generates a PID and replaces the one in the provided config.h files if VID is 0x03A8
"""

import os
import fileinput
import subprocess
from pathlib import Path

import json

from milc import cli
from qmk.keyboard import get_ids, calculate_pid, atomic_dump


def replace_pid(config_h, id_pid, pid_match):
    """Replace the PID in a config.h file

    Args:
        config_h (str): The config to replace the PID in. The file has to have a "#define PRODUCT_ID 0x0000". The hex value doesn't matter.
        id_pid (str): The PID to write in to the file as 4 characters
        pid_match (re.match): The full regex match for the PID string
    """

    comment = pid_match.group(2) if pid_match.group(2) is not None else ''
    for line in fileinput.input(config_h, inplace=True):
        print(line.replace(pid_match.group(0), "%s0x%s%s" % (pid_match.group(1), id_pid, comment)), end='')


def process_config(cli, config_path, pids_json_path, pid_match):
    """Generates PID for a config. Optionally applies and commits it

        Args:
            cli: The milc CLI. Used for logging output
            config_path (str): The path to the config.h file to process
            pids_json_path (str): The path to the json file storing all assigned PIDs
            pid_match (re.Match): The full regex match of the product id define
    """

    chopped_config_path = '/'.join(config_path.parts[1:])
    keyboard = '/'.join(config_path.parts[1:-1])

    with open(pids_json_path, 'r') as json_file:
        data = json.load(json_file)

    try:
        pid_new = calculate_pid(chopped_config_path, data)
    except RecursionError as e:
        cli.log.error("Too many PID collisions (%s) when generating PID for %s. Aborting", e, keyboard)
        return False

    if chopped_config_path in data['pids'].values():
        if pid_new != pid_match.group(2):
            cli.log.warning("%s already assigned %s, but PID doesn't match.", keyboard, pid_new)
            if cli.args.apply:
                replace_pid(str(config_path), pid_new, pid_match)
                cli.log.warning('\tRe-applying %s to %s', pid_new, keyboard)
        else:
            cli.log.info('%s already assigned pid 0x%s', keyboard, pid_new)
            return True
    else:
        cli.log.info('Assigned PID 0x%s to %s', pid_new, keyboard)
        if cli.args.apply:
            cli.log.info('\tApplying PID')
            replace_pid(str(config_path), pid_new, pid_match)
            data["pids"][pid_new] = chopped_config_path

    atomic_dump(data, pids_json_path)  # Save the new pids table
    if cli.args.commit:
        try:
            cli.log.info('\tCommitting changes to git')
            subprocess.run(
                ['git', 'commit', '-am', 'Generated PID 0x%s for %s' % (pid_new, keyboard)],
                timeout=5,
                check=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT
            )
        except subprocess.CalledProcessError as e:
            cli.log.error('Committing to git failed. %s failed with: %s', e.cmd, e.output)
            return False
    return True


@cli.argument('config', nargs='+', arg_only=True, type=str, help='One or more configs to process')
@cli.argument('--commit', action='store_true', arg_only=True, help='Commit each change to git')
@cli.argument('--apply', action='store_true', arg_only=True, help='Set this if you want to apply the PIDs to the supplied configs')
@cli.subcommand('Computes and applies a QMKPID for configs supplied. Intended for CI/CD use')
def pid(cli):
    """Generates and applies a PID for configs using the 0x03A8 VID

    Main entry point of the script
    """
    if cli.args.commit and not cli.args.apply:
        cli.log.error("Can't commit changes if changes aren't applied, please use --apply with --commit. This option is only intended for CI/CD")
        return False

    pids_json_path = cli.config.pid.db_path if cli.config.pid.db_path else "quantum/usb_pids.json"
    qmk_vid = cli.config.pid.qmk_vid if cli.config.pid.qmk_vid else "0x03A8"

    # Make a skeleton json file on first run
    if not Path(pids_json_path).is_file():
        cli.log.error('Assigned pids file not found %s', pids_json_path)
        return False

    for config_h in cli.args.config:
        vid_match, pid_match = get_ids(config_h)

        if vid_match is None:
            cli.log.info('%s is not a keyboard config', config_h)
            continue

        # If vid_match is not none, but pid_match is:
        if pid_match is None:
            cli.log.error('No product ID placeholder defined in config!')
            return False

        if vid_match.group(1) != qmk_vid:
            cli.log.info("Keyboard does not use QMK VID, or it's not a keyboard config. (%s != %s in %s)", vid_match.group(1), qmk_vid, config_h)
            continue
        else:
            if not process_config(cli, Path(config_h), pids_json_path, pid_match):
                return False
    return True

