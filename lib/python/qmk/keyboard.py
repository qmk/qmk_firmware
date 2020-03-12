"""Functions that help you work with QMK keyboards
"""

import os
import re
import hashlib
import tempfile
from pathlib import Path

import json

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

    Raises:
        RecursionError: If more than the generated pid clashes more than max_tries times
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


    Args:
        data (dict):

            * PID (str): The parrent folder of the config associated with the PID key

        json_file (str): The file to dump to
    """

    try:
        with tempfile.NamedTemporaryFile('w', dir=str(Path(json_file).parents[0]), delete=True) as tf:
            json.dump(data, tf)
            os.replace(tf.name, json_file)
    except FileNotFoundError:
        """ The file is moved by os.replace,
        but delete=True is required for cleanup in case an error occurs.
        """
        pass
