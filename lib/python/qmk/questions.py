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
            The prompt to present to the user. Can include ANSI and format strings like milc's `cli.echo()`.

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
        cli.echo()
        answer = input(format_ansi(prompt % args))
        cli.echo()

        if not answer and prompt is not None:
            return default

        elif answer.lower() in ['y', 'yes']:
            return True

        elif answer.lower() in ['n', 'no']:
            return False


def question(prompt, *args, default=None, confirm=False, answer_type=str, validate=None, **kwargs):
    """Prompt the user to answer a question with a free-form input.

    Arguments:
        prompt
            The prompt to present to the user. Can include ANSI and format strings like milc's `cli.echo()`.

        default
            The value to return when the user doesn't enter any value. Use None to prompt until they enter a value.

        answer_type
            Specify a type function for the answer. Will re-prompt the user if the function raises any errors. Common choices here include int, float, and decimal.Decimal.

        validate
            This is an optional function that can be used to validate the answer. It should return True or False and have the following signature:

                def function_name(answer, *args, **kwargs):
    """
    if not args and kwargs:
        args = kwargs

    if default is not None:
        prompt = '%s [%s] ' % (prompt, default)

    while True:
        cli.echo()
        answer = input(format_ansi(prompt % args))
        cli.echo()

        if answer:
            if validate is not None and not validate(answer, *args, **kwargs):
                continue

            elif confirm:
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


def choice(prompt, options, *args, default=None, confirm=False, **kwargs):
    """Present the user with a list of options and let them pick one by numerical index.

    This will return the item from options they choose, not the index.

    Arguments:
        prompt
            The prompt to present to the user. Can include ANSI and format strings like milc's `cli.echo()`.

        options
            A sequence of items to choose from.

        default
            The value to return when the user doesn't enter any value. Use None to prompt until they enter a value.

        confirm
            Present the user with a confirmation dialog before accepting their answer.
    """
    if not args and kwargs:
        args = kwargs

    while True:
        # Prompt for an answer.
        cli.echo()
        cli.echo(prompt % args)
        cli.echo()
        for i, option in enumerate(options):
            cli.echo('\t{fg_cyan}%d.{fg_reset} %s', i+1, option)

        if default:
            answer = input(format_ansi('Please choose an option: [%s] ' % (default+1,)))
        else:
            answer = input(format_ansi('Please choose an option: '))
        cli.echo()

        # Massage the answer into a valid integer
        if answer = '' and default:
            answer = default
        else:
            try:
                answer = int(answer) - 1
            except Exception as e:
                cli.log.error('Could not convert answer (%s) to type int: %s', answer, str(e))
                continue

        # Validate the answer
        if answer > len(options) or answer < 0:
            cli.log.error('Invalid choice: %s', answer)
            continue

        if confirm and not yesno('Is the answer "%s" correct?', answer+1, default=True):
            continue

        # Return the answer they chose.
        return options[answer]
