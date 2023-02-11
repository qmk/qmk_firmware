"""Functions to work with dates and times in a uniform way.

The results of these functions are cached for 5 seconds to provide uniform time strings across short running processes. Long running processes that need more precise timekeeping should not use these functions.
"""
from time import gmtime, strftime

from qmk.constants import DATE_FORMAT, DATETIME_FORMAT, TIME_FORMAT
from qmk.decorators import lru_cache


@lru_cache(timeout=5)
def current_date():
    """Returns the current time in UTZ as a formatted string.
    """
    return strftime(DATE_FORMAT, gmtime())


@lru_cache(timeout=5)
def current_datetime():
    """Returns the current time in UTZ as a formatted string.
    """
    return strftime(DATETIME_FORMAT, gmtime())


@lru_cache(timeout=5)
def current_time():
    """Returns the current time in UTZ as a formatted string.
    """
    return strftime(TIME_FORMAT, gmtime())
