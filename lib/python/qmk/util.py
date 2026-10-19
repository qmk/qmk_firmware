"""Utility functions.
"""
import contextlib
import multiprocessing
import sys
import re
from pathlib import Path

from milc import cli

TRIPLET_PATTERN = re.compile(r'^(\d+)\.(\d+)\.(\d+)')

maybe_exit_should_exit = True
maybe_exit_reraise = False


# Controls whether or not early `exit()` calls should be made
def maybe_exit(rc):
    if maybe_exit_should_exit:
        sys.exit(rc)
    if maybe_exit_reraise:
        e = sys.exc_info()[1]
        if e:
            raise e


def maybe_exit_config(should_exit: bool = True, should_reraise: bool = False):
    global maybe_exit_should_exit
    global maybe_exit_reraise
    maybe_exit_should_exit = should_exit
    maybe_exit_reraise = should_reraise


def truthy(value, value_if_unknown=False):
    """Returns True if the value is truthy, False otherwise.

    Deals with:
        True: 1, true, t, yes, y, on
        False: 0, false, f, no, n, off
    """
    if value in {False, True}:
        return bool(value)

    test_value = str(value).strip().lower()

    if test_value in {"1", "true", "t", "yes", "y", "on"}:
        return True

    if test_value in {"0", "false", "f", "no", "n", "off"}:
        return False

    return value_if_unknown


@contextlib.contextmanager
def parallelize():
    """Returns a function that can be used in place of a map() call.

    Attempts to use `mpire`, falling back to `multiprocessing` if it's not
    available. If parallelization is not requested, returns the original map()
    function.
    """

    # Work out if we've already got a config value for parallel searching
    if cli.config.user.parallel_search is None:
        parallel_search = True
    else:
        parallel_search = cli.config.user.parallel_search

    # Non-parallel searches use `map()`
    if not parallel_search:
        yield map
        return

    # Prefer mpire's `WorkerPool` if it's available
    with contextlib.suppress(ImportError):
        from mpire import WorkerPool
        from mpire.utils import make_single_arguments
        with WorkerPool() as pool:

            def _worker(func, *args):
                # Ensure we don't unpack tuples -- mpire's `WorkerPool` tries to do so normally so we tell it not to.
                for r in pool.imap_unordered(func, make_single_arguments(*args, generator=False), progress_bar=True):
                    yield r

            yield _worker
        return

    # Otherwise fall back to multiprocessing's `Pool`
    with multiprocessing.Pool() as pool:
        yield pool.imap_unordered


def parallel_map(*args, **kwargs):
    """Effectively runs `map()` but executes it in parallel if necessary.
    """
    with parallelize() as map_fn:
        # This needs to be enclosed in a `list()` as some implementations return
        # a generator function, which means the scope of the pool is closed off
        # before the results are returned. Returning a list ensures results are
        # materialised before any worker pool is shut down.
        return list(map_fn(*args, **kwargs))


def is_valid_bcd_string(ver: str) -> bool:
    if ver:
        parts = ver.split('.')
        if len(parts) == 3 and all(part.isascii() and part.isdigit() for part in parts):
            major, minor, patch = map(int, parts)
            # Ensure that version is valid u32 bcd
            if major <= 99 and minor <= 99 and patch <= 9999:
                return True
    return False


def triplet_to_bcd(ver: str) -> str:
    if ver:
        m = TRIPLET_PATTERN.match(ver)
        if m and is_valid_bcd_string(m.expand(r'\1.\2.\3')):
            return f'0x{int(m.group(1)):02d}{int(m.group(2)):02d}{int(m.group(3)):04d}'
    return '0x00000000'


def _search_file_versions(parent: Path, ext: str = 'hjson', prefix: str = '', reverse: bool = False) -> dict[str, Path]:
    versions = {}
    found = parent.glob(f'{prefix}*.{ext}')
    for file in found:
        version = file.stem[len(prefix):] if prefix else file.stem
        if is_valid_bcd_string(version):
            versions[version] = file

    return dict(sorted(versions.items(), key=lambda item: tuple(map(int, item[0].split('.'))), reverse=reverse))


def list_file_versions(parent: Path, ext: str = 'hjson', prefix: str = '', reverse: bool = False) -> list[str]:
    return list(_search_file_versions(parent, ext=ext, prefix=prefix, reverse=reverse).keys())


def list_version_files(parent: Path, ext: str = 'hjson', prefix: str = '', reverse: bool = False) -> list[Path]:
    return list(_search_file_versions(parent, ext=ext, prefix=prefix, reverse=reverse).values())
