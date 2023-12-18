"""Removes C/C++ style comments from text.

Gratefully adapted from https://stackoverflow.com/a/241506
"""
import re

comment_pattern = re.compile(r'//.*?$|/\*.*?\*/|\'(?:\\.|[^\\\'])*\'|"(?:\\.|[^\\"])*"', re.DOTALL | re.MULTILINE)


def _comment_stripper(match):
    """Removes C/C++ style comments from a regex match.
    """
    s = match.group(0)
    return ' ' if s.startswith('/') else s


def comment_remover(text):
    """Remove C/C++ style comments from text.
    """
    return re.sub(comment_pattern, _comment_stripper, text)
