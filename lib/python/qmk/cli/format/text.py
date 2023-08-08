"""Ensure text files have the proper line endings.
"""
from itertools import islice

from milc import cli

from . import qmk_formatter


def _get_chunks(it, size):
    """Break down a collection into smaller parts
    """
    it = iter(it)
    return iter(lambda: tuple(islice(it, size)), ())


def dos2unix_run(file):
    """Spawn multiple dos2unix subprocess avoiding too long commands on formatting everything
    """
    # for chunk in _get_chunks(files, 10):
    dos2unix = cli.run(['dos2unix', file])

    if dos2unix.returncode:
        return False


@qmk_formatter
def format_text(cli, file):
    """
    Ensure a single text file has the proper line endings.
    Itrating over target files is handled in decorator.
    """

    return dos2unix_run(file)
