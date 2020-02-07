"""Generate and apply a QMK PID

Generates a PID and replaces the one in the provided config.h files if VID is 0x03A8
"""

import os
import fileinput
import tempfile
import subprocess
from pathlib import Path

import re
import hashlib
import json

from milc import cli

VID_regex = re.compile(r"^#define\s+VENDOR_ID\s+(0x[0-9a-f]{4})(\s+/[/|*].*)*$", flags=re.IGNORECASE)
PID_regex = re.compile(r"^(#define\s+PRODUCT_ID\s+)\S+(\s+/[/|*].*)?$")


def get_ids(config_file):
    """Gets the VID and PID, if any, in the supplied config file.

    Args:
        config_file (str): The path to the config file to process.

    Returns:
        (tuple):

            * VID (re.Match): VID found in the config. None if none in the config
            * PID (re.Match): PID found in the config. None if none in the config
    """
    id_vid = None
    id_pid = None
    with open(config_file) as cf:
        for line in cf:
            if id_vid is None:
                id_vid = re.match(VID_regex, line)
            if id_pid is None:
                id_pid = re.match(PID_regex, line)
            if id_vid is not None and id_pid is not None:
                break
    return id_vid, id_pid


def calculate_pid(config_path, data, max_tries=10):
    """Calculate a PID given the path to a config.h

    This function generates a unique PID for any config.h supplied.
    The PID is determined based on the SHA1 hexdigest of the path to the config file
    The first 4 characters (2 bytes) are used as the PID, unless those collide with
    an already assigned PID. If a collision happens the process will be repeated with offset + 1

    Args:
        config_path (str): The path to the config file to process.
        data (dict):

            * PID (str): The parent folder of the config associated with the PID key

        max_tries (int): The maximum amount of attempts to get around collisions

    Returns:
        new_pid (str): The 4 characters of the 2 byte pid
    """
    m = hashlib.sha1()
    m.update(config_path.encode('utf-8'))
    digest = m.hexdigest()
    offset = 0
    while offset < max_tries:
        id_pid = digest[offset:offset + 4].upper()

        if id_pid not in data['pids']:
            return id_pid
        else:
            offset += 1

    raise RecursionError(offset)


def atomic_dump(data, json_file):
    """Dumps a dict as a json file atomically

    This function should avoid data loss caused by an error happening during
    file writing.
    It accomplishes this by writing the new json file to a temporary file,
    then using os.replace() to overwrite the old file with the new file.
    os.replace() is atomic as long as the two files are on the same filesystem.
    In case of an error before os.replace() the temp file isn't removed.

    Args:
        data (dict):

            * PID (str): The parrent folder of the config associated with the PID key

        json_file (str): The file to dump to
    """
    with tempfile.NamedTemporaryFile('w', dir=str(Path(json_file).parents[0]), delete=False) as tf:
        json.dump(data, tf)
    os.replace(tf.name, json_file)


def replace_pid(config_h, id_pid, pid_match):
    """Replace the PID in a config.h file

    Args:
        config_h (str): The config to replace the PID in. The file has to have a "#define PRODUCT_ID 0x0000" the value doesn't matter, but has to be 2 bytes
        id_pid (str): The PID to write in to the file as 4 characters
        pid_match (re.match): The full regex match for the PID string
    """

    comment = pid_match.group(2) if pid_match.group(2) is not None else ''
    for line in fileinput.input(config_h, inplace=True):
        print(line.replace(pid_match.group(0), "{}{}{}".format(pid_match.group(1), id_pid, comment)), end='')


def init(json_path):
    """Generates a skeleton pids json file.

    Generates a skeleton jsonfile for this script. If the parent folders in the configured path don't exist, these will also be created.

    Args:
        json_path (str): The path to create the json skeleton file at
    """

    Path(json_path).parents[0].mkdir(parents=True, exist_ok=True)
    with open(json_path, 'w') as jfile:
        json.dump({"pids": {}}, jfile)
    if cli.args.commit:
        subprocess.run(
            ['git', 'add', json_path],
            timeout=5,
            check=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT
        )


def lchop(source_string, chop):
    """Chops off chop from thestring from the left

        Args:
            source_string (str): The string to check
            chop (str): The string to remove from source_string
    """

    if source_string.startswith(chop):
        return source_string[len(chop):]
    return source_string


def process_config(cli, config_path, pids_json_path, pid_match):
    """Generates PID for a config. Optionally applies and commits it

        Args:
            cli: The milc CLI. Used for logging output
            config_path (str): The path to the config.h file to process
            pids_json_path (str): The path to the json file storing all assigned PIDs
            pid_match (re.Match): The full regex match of the product id define
    """

    config_path_lchop = cli.config.pid.path_lchop if cli.config.pid.path_lchop else "keyboards/"

    chopped_config_path = lchop(config_path, config_path_lchop)
    keyboard = str(Path(config_path).parent.stem)

    with open(pids_json_path, 'r') as json_file:
        data = json.load(json_file)

    try:
        pid_new = calculate_pid(chopped_config_path, data)
    except RecursionError as e:
        cli.log.error("Too many PID collisions (%s) when generating PID for %s. Aborting", e, keyboard)
        return False

    if chopped_config_path in data['pids'].values():
        if pid_new != pid_match.group(2):
            cli.log.warning("{} already assigned {}, but PID doesn't match.".format(keyboard, pid_new))
            if cli.args.apply:
                replace_pid(config_path, pid_new, pid_match)
                cli.log.warning('\tRe-applying {} to {}'.format(pid_new, keyboard))
        else:
            cli.log.info('{} already assigned pid 0x{}'.format(keyboard, pid_new))
            return True
    else:
        cli.log.info('Assigned PID 0x{} to {}'.format(pid_new, keyboard))
        if cli.args.apply:
            cli.log.info('\tApplying PID')
            replace_pid(config_path, pid_new, pid_match)
            data["pids"][pid_new] = chopped_config_path

    atomic_dump(data, pids_json_path)  # Save the new pids table
    if cli.args.commit:
        try:
            cli.log.info('\tCommitting changes to git')
            subprocess.run(
                ['git', 'commit', '-am', '"Generated PID 0x{} for {}"'.format(pid_new, keyboard)],
                timeout=5,
                check=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT
            )
        except subprocess.CalledProcessError as e:
            cli.log.error('Committing to git failed. {} failed with: {}'.format(e.cmd, e.output))
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
        try:
            init(pids_json_path)
        except subprocess.CalledProcessError as e:
            cli.log.error('Adding json to git failed. {} failed with: {}'.format(e.cmd, e.output))
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
            if not process_config(cli, config_h, pids_json_path, pid_match):
                return False
    return True
