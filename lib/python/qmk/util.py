"""Utility functions.
"""
import contextlib
import functools
import multiprocessing


@contextlib.contextmanager
def parallelize(do_parallel):
    """Returns a function that can be used in place of a map() call.

    Attempts to use `mpire`, falling back to `multiprocessing` if it's not
    available. If parallelization is not requested, returns the original map()
    function.
    """
    if not do_parallel:
        yield map
        return

    with contextlib.suppress(ImportError):
        from mpire import WorkerPool
        with WorkerPool() as pool:
            yield functools.partial(pool.imap_unordered, progress_bar=True)
        return

    with multiprocessing.Pool() as pool:
        yield pool.imap_unordered
