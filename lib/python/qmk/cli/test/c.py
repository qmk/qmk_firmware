import fnmatch
import re
from subprocess import DEVNULL

from milc import cli

from qmk.commands import find_make, get_make_parallel_args, build_environment


@cli.argument('-j', '--parallel', type=int, default=1, help="Set the number of parallel make jobs; 0 means unlimited.")
@cli.argument('-e', '--env', arg_only=True, action='append', default=[], help="Set a variable to be passed to make. May be passed multiple times.")
@cli.argument('-c', '--clean', arg_only=True, action='store_true', help="Remove object files before compiling.")
@cli.argument('-l', '--list', arg_only=True, action='store_true', help='List available tests.')
@cli.argument('-t', '--test', arg_only=True, action='append', default=[], help="Test to run from the available list. Supports wildcard globs. May be passed multiple times.")
@cli.subcommand("QMK C Unit Tests.", hidden=False if cli.config.user.developer else True)
def test_c(cli):
    """Run native unit tests.
    """
    list_tests = cli.run([find_make(), 'list-tests', 'SILENT=true'])
    available_tests = sorted(list_tests.stdout.strip().split())

    if cli.args.list:
        return print("\n".join(available_tests))

    # expand any wildcards
    filtered_tests = set()
    for test in cli.args.test:
        regex = re.compile(fnmatch.translate(test))
        filtered_tests |= set(filter(regex.match, available_tests))

    for invalid in filtered_tests - set(available_tests):
        cli.log.warning(f'Invalid test provided: {invalid}')

    # convert test names to build targets
    targets = list(map(lambda x: f'test:{x}', filtered_tests or ['all']))

    if cli.args.clean:
        targets.insert(0, 'clean')

    # Add in the environment vars
    for key, value in build_environment(cli.args.env).items():
        targets.append(f'{key}={value}')

    command = [find_make(), *get_make_parallel_args(cli.config.test_c.parallel), *targets]

    cli.log.info('Compiling tests with {fg_cyan}%s', ' '.join(command))
    return cli.run(command, capture_output=False, stdin=DEVNULL).returncode
