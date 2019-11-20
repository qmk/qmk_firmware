"""Functions to collect user input.
"""

from milc import cli, format_ansi


def yesno(prompt, *args, default=None, **kwargs):
    """Displays prompt to the user and gets a yes or no response.

    Returns True for a yes and False for a no.

    If you add `--yes` and `--no` arguments to your program the user can answer questions by passing command line flags.

        @add_argument('-y', '--yes', action='store_true', arg_only=True, help='Answer yes to all questions.')
        @add_argument('-n', '--no', action='store_true', arg_only=True, help='Answer no to all questions.')

    Arguments:
        prompt
            The prompt to present to the user. Can include ANSI and format strings like milc's `cli.print()`.

        default
            Whether to default to a Yes or No when the user presses enter.

            None- force the user to enter Y or N

            True- Default to yes

            False- Default to no
    """
    if not args and kwargs:
        args = kwargs

    if 'no' in cli.args and cli.args.no:
        return False

    if 'yes' in cli.args and cli.args.yes:
        return True

    if default is not None:
        if default:
            prompt = prompt + ' [Y/n] '
        else:
            prompt = prompt + ' [y/N] '

    while True:
        print()
        answer = input(format_ansi(prompt % args))
        print()

        if not answer and prompt is not None:
            return default

        elif answer.lower() in ['y', 'yes']:
            return True

        elif answer.lower() in ['n', 'no']:
            return False


def question(prompt, *args, default=None, confirm=False, answer_type=str, **kwargs):
    """Prompt the user to answer a question with a free-form input.

        prompt
            The prompt to present to the user. Can include ANSI and format strings like milc's `cli.print()`.

        default
            The value to return when the user doesn't enter any value. Use None to prompt until they enter a value.

        answer_type
            Specify a type function for the answer. Will re-prompt the user if the function raises any errors. Common choices here include int, float, and decimal.Decimal.
    """
    if not args and kwargs:
        args = kwargs

    if default is not None:
        prompt = '%s [%s] ' % (prompt, default)

    while True:
        print()
        answer = input(format_ansi(prompt % args))
        print()

        if answer:
            if confirm:
                if yesno('Is the answer "%s" correct?', answer, default=True):
                    try:
                        return answer_type(answer)
                    except Exception as e:
                        cli.log.error('Could not convert answer (%s) to type %s: %s', answer, answer_type.__name__, str(e))
            else:
                try:
                    return answer_type(answer)
                except Exception as e:
                    cli.log.error('Could not convert answer (%s) to type %s: %s', answer, answer_type.__name__, str(e))

        elif default is not None:
            return default
