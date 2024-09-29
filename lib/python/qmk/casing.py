"""This script handles conversion between snake and camel casing.
"""
import re

_words_expr = re.compile(r"([a-zA-Z][^A-Z0-9]*|[0-9]+)")
_lower_snake_case_expr = re.compile(r'^[a-z][a-z0-9_]*$')
_upper_snake_case_expr = re.compile(r'^[A-Z][A-Z0-9_]*$')


def _is_snake_case(str):
    """Checks if the supplied string is already in snake case.
    """
    match = _lower_snake_case_expr.match(str)
    if match:
        return True
    match = _upper_snake_case_expr.match(str)
    if match:
        return True
    return False


def _split_snake_case(str):
    """Splits up a string based on underscores, if it's in snake casing.
    """
    if _is_snake_case(str):
        return [s.lower() for s in str.split("_")]
    return str


def _split_camel_case(str):
    """Splits up a string based on capitalised camel casing.
    """
    return _words_expr.findall(str)


def _split_cased_words(str):
    return _split_snake_case(str) if _is_snake_case(str) else _split_camel_case(str)


def to_snake(str):
    str = "_".join([word.strip().lower() for word in _split_cased_words(str)])

    # Fix acronyms
    str = str.replace('i_d', 'id')
    str = str.replace('x_a_p', 'xap')
    str = str.replace('q_m_k', 'qmk')

    return str


def to_upper_snake(str):
    return to_snake(str).upper()


def to_camel(str):
    def _acronym(w):
        if w.strip().lower() == 'qmk':
            return 'QMK'
        elif w.strip().lower() == 'xap':
            return 'XAP'
        elif w.strip().lower() == 'id':
            return 'ID'
        return w.title()

    return "".join([_acronym(word) for word in _split_cased_words(str)])
