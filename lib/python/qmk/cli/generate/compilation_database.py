from milc import cli


@cli.argument('-kb', '--keyboard', help='[unused] The keyboard\'s name')
@cli.argument('-km', '--keymap', help='[unused] The keymap\'s name')
@cli.subcommand('[deprecated] Create a compilation database.')
def generate_compilation_database(cli):
    cli.log.error('This command is deprecated and has effectively been removed. Please use the `--compiledb` flag with `qmk compile` instead.')
    return False
