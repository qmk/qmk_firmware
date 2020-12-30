"""Functions to collect user input.
"""

from milc import cli

try:
    from milc import format_ansi
except ImportError:
    from milc.ansi import format_ansi


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
        cli.echo('')
        answer = input(format_ansi(prompt % args))
        cli.echo('')

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

        confirm
            Present the user with a confirmation dialog before accepting their answer.

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
        cli.echo('')
        answer = input(format_ansi(prompt % args))
        cli.echo('')

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


def choice(heading, options, *args, default=None, confirm=False, prompt='Please enter your choice: ', **kwargs):
    """Present the user with a list of options and let them pick one.

    Users can enter either the number or the text of their choice.

    This will return the value of the item they choose, not the numerical index.

    Arguments:
        heading
            The text to place above the list of options.

        options
            A sequence of items to choose from.

        default
            The index of the item to return when the user doesn't enter any value. Use None to prompt until they enter a value.

        confirm
            Present the user with a confirmation dialog before accepting their answer.

        prompt
            The prompt to present to the user. Can include ANSI and format strings like milc's `cli.echo()`.
    """
    if not args and kwargs:
        args = kwargs

    if prompt and default:
        prompt = prompt + ' [%s] ' % (default + 1,)

    while True:
        # Prompt for an answer.
        cli.echo('')
        cli.echo(heading % args)
        cli.echo('')
        for i, option in enumerate(options, 1):
            cli.echo('\t{fg_cyan}%d.{fg_reset} %s', i, option)

        cli.echo('')
        answer = input(format_ansi(prompt))
        cli.echo('')

        # If the user types in one of the options exactly use that
        if answer in options:
            return answer

        # Massage the answer into a valid integer
        if answer == '' and default:
            answer = default
        else:
            try:
                answer = int(answer) - 1
            except Exception:
                # Normally we would log the exception here, but in the interest of clean UI we do not.
                cli.log.error('Invalid choice: %s', answer + 1)
                continue

        # Validate the answer
        if answer >= len(options) or answer < 0:
            cli.log.error('Invalid choice: %s', answer + 1)
            continue

        if confirm and not yesno('Is the answer "%s" correct?', answer + 1, default=True):
            continue

        # Return the answer they chose.
        return options[answer]
