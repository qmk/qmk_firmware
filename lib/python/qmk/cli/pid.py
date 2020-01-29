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

VID_regex = re.compile(r"""^#define\s+VENDOR_ID\s+(0x[0-9a-f]{4})$""", flags=re.IGNORECASE)
PID_regex = re.compile(r"""^#define\s+PRODUCT_ID\s+(0x[0-9a-f]{4})$""", flags=re.IGNORECASE)


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


def calculate_pid(config_path, data, max_tries=3):
    """Calculate a PID given the path to a config.h

    This function generates a unique PID for any config.h supplied.
    The PID is determined based on the SHA1 hexdigest of the path to the config file
    The first 4 characters (2 bytes) are used as the PID, unless those collide with
    an already assigned PID, in which case the process will be repeated with offset + 1

    Args:
        config_path (str): The path to the config file to process.
        data (dict):

            * PID (str): The parent folder of the config associated with the PID key

        max_tries (int): The maximum recursion level of this function.

    Returns:
        new_pid (str): The 4 characters of the 2 byte pid
    """
    m = hashlib.sha1()
    m.update(config_path.encode('utf-8'))
    digest = m.hexdigest()
    offset = 0
    while offset < max_tries:
        id_pid = digest[offset:offset+4].upper()

        if id_pid not in data['pids']:
            return id_pid
        else:
            offset += 1

    raise RecursionError(offset)


def atomic_dump(data, json_file):
    """Dumps a dict as a json file atomically

    This function should avoid data loss due to an error happening during
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
    with tempfile.NamedTemporaryFile(
            'w', dir=Path(json_file).parents[0], delete=False) as tf:
        json.dump(data, tf)
    os.replace(tf.name, json_file)


def init(pids_json_path):
    """On the first run of this script, write a skeleton json file"""
    Path(pids_json_path).parents[0].mkdir(parents=True)
    with open(pids_json_path, 'w') as jfile:
        json.dump({"pids": {}}, jfile)


def replace_pid(config_h, id_pid, pid_match):
    """Replace the PID in a config.h file

    Args:
        config_h (str): The config to replace the PID in. The file has to have a "#define PRODUCT_ID 0x0000" the value doesn't matter, but has to be 2 bytes
        id_pid (str): The PID to write in to the file
        pid_match (re.match): The full re match for the PID string
    """

    for line in fileinput.input(config_h, inplace=True):
        print(line.replace(pid_match.group(0), "{}{}".format(pid_match.group(0)[:-4], id_pid)), end='')


@cli.argument('config', nargs='+', arg_only=True, type=str, help='One or more configs to process')
@cli.argument('--commit', action='store_true', arg_only=True, help='Commit each change to git')
@cli.subcommand('Computes and applies a QMKPID for configs supplied. Intended for CI/CD use')
def pid(cli):
    """Generates and applies a PID for configs using 0x03A8 VID

    Main entry point of the script
    """

    pids_json_path = cli.config.pid.db_path if cli.config.pid.db_path else "quantum/usb_pids.json" # TODO: decide on default pids.json path
    qmk_vid = cli.config.pid.qmk_vid if cli.config.pid.qmk_vid else "0x03A8"

    if not Path(pids_json_path).is_file():
        init(pids_json_path)

    for config_h in cli.args.config:
        vid_match, pid_match = get_ids(config_h)
        keyboard = config_h.parent.stem

        if vid_match.group(1) != qmk_vid:
            cli.log.info("Keyboard does not use QMK VID ({} != {})".format(vid_match.group(1), qmk_vid))
            return True
        else:
            path = str(Path(config_h).parents[0])

            try:
                pid_new = calculate_pid(path, data)
            except RecursionError as e:
                cli.log.error("Too many PID collisions ({}). Aborting".format(e))
                return False

            with open(pids_json_path, 'r') as json_file:
                data = json.load(json_file)

                if path in data['pids'].values():
                    if pid_new != pid_match.group(1)[-4:]:
                        cli.log.warning("Keyboard already assigned a PID, but PID doesn't match. Re-applying")
                        replace_pid(config_h, pid_new, pid_match)
                    else:
                        cli.log.info("Keyboard already assigned a pid")
                    return True
                else:
                    replace_pid(config_h, pid_new, pid_match)
                    cli.log.info('Assigned PID 0x{} to')
                    data["pids"][pid_new] = config_h

            atomic_dump(data, pids_json_path)  # Save the new pids table
            if cli.config.pid.commit:
                try:  # Commit change to git
                    subprocess.run(
                        ['git', 'commit', '-am', '"Generated PID 0x{} for {}"'.format(pid_new, keyboard)],
                        timeout=5,
                        check=True,
                        stdout=PIPE,
                        stderr=STDOUT
                    )
                except subprocess.CalledProcessError as e:
                    cli.log.error('Committing to git failed. {} failed with: {}'.format(e.cmd, e.output))
                    return False
