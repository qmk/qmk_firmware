#!/usr/bin/env python3
# coding=utf-8
"""MILC - A CLI Framework

PYTHON_ARGCOMPLETE_OK

MILC is an opinionated framework for writing CLI apps. It optimizes for the
most common unix tool pattern- small tools that are run from the command
line but generally do not feature any user interaction while they run.

For more details see the MILC documentation:

    <https://github.com/clueboard/milc/tree/master/docs>
"""
from __future__ import division, print_function, unicode_literals
import argparse
import logging
import os
import re
import shlex
import sys
from decimal import Decimal
from tempfile import NamedTemporaryFile
from time import sleep

try:
    from ConfigParser import RawConfigParser
except ImportError:
    from configparser import RawConfigParser

try:
    import thread
    import threading
except ImportError:
    thread = None

import argcomplete
import colorama
from appdirs import user_config_dir

# Disable logging until we can configure it how the user wants
logging.basicConfig(filename='/dev/null')

# Log Level Representations
EMOJI_LOGLEVELS = {
    'CRITICAL': '{bg_red}{fg_white}¬_¬{style_reset_all}',
    'ERROR': '{fg_red}☒{style_reset_all}',
    'WARNING': '{fg_yellow}⚠{style_reset_all}',
    'INFO': '{fg_blue}ℹ{style_reset_all}',
    'DEBUG': '{fg_cyan}☐{style_reset_all}',
    'NOTSET': '{style_reset_all}¯\\_(o_o)_/¯'
}
EMOJI_LOGLEVELS['FATAL'] = EMOJI_LOGLEVELS['CRITICAL']
EMOJI_LOGLEVELS['WARN'] = EMOJI_LOGLEVELS['WARNING']
UNICODE_SUPPORT = sys.stdout.encoding.lower().startswith('utf')

# ANSI Color setup
# Regex was gratefully borrowed from kfir on stackoverflow:
# https://stackoverflow.com/a/45448194
ansi_regex = r'\x1b(' \
             r'(\[\??\d+[hl])|' \
             r'([=<>a-kzNM78])|' \
             r'([\(\)][a-b0-2])|' \
             r'(\[\d{0,2}[ma-dgkjqi])|' \
             r'(\[\d+;\d+[hfy]?)|' \
             r'(\[;?[hf])|' \
             r'(#[3-68])|' \
             r'([01356]n)|' \
             r'(O[mlnp-z]?)|' \
             r'(/Z)|' \
             r'(\d+)|' \
             r'(\[\?\d;\d0c)|' \
             r'(\d;\dR))'
ansi_escape = re.compile(ansi_regex, flags=re.IGNORECASE)
ansi_styles = (
    ('fg', colorama.ansi.AnsiFore()),
    ('bg', colorama.ansi.AnsiBack()),
    ('style', colorama.ansi.AnsiStyle()),
)
ansi_colors = {}

for prefix, obj in ansi_styles:
    for color in [x for x in obj.__dict__ if not x.startswith('_')]:
        ansi_colors[prefix + '_' + color.lower()] = getattr(obj, color)


def format_ansi(text):
    """Return a copy of text with certain strings replaced with ansi.
    """
    # Avoid .format() so we don't have to worry about the log content
    for color in ansi_colors:
        text = text.replace('{%s}' % color, ansi_colors[color])
    return text + ansi_colors['style_reset_all']


class ANSIFormatter(logging.Formatter):
    """A log formatter that inserts ANSI color.
    """

    def format(self, record):
        msg = super(ANSIFormatter, self).format(record)
        return format_ansi(msg)


class ANSIEmojiLoglevelFormatter(ANSIFormatter):
    """A log formatter that makes the loglevel an emoji on UTF capable terminals.
    """

    def format(self, record):
        if UNICODE_SUPPORT:
            record.levelname = EMOJI_LOGLEVELS[record.levelname].format(**ansi_colors)
        return super(ANSIEmojiLoglevelFormatter, self).format(record)


class ANSIStrippingFormatter(ANSIFormatter):
    """A log formatter that strips ANSI.
    """

    def format(self, record):
        msg = super(ANSIStrippingFormatter, self).format(record)
        return ansi_escape.sub('', msg)


class Configuration(object):
    """Represents the running configuration.

    This class never raises IndexError, instead it will return None if a
    section or option does not yet exist.
    """

    def __contains__(self, key):
        return self._config.__contains__(key)

    def __iter__(self):
        return self._config.__iter__()

    def __len__(self):
        return self._config.__len__()

    def __repr__(self):
        return self._config.__repr__()

    def keys(self):
        return self._config.keys()

    def items(self):
        return self._config.items()

    def values(self):
        return self._config.values()

    def __init__(self, *args, **kwargs):
        self._config = {}

    def __getattr__(self, key):
        return self.__getitem__(key)

    def __getitem__(self, key):
        """Returns a config section, creating it if it doesn't exist yet.
        """
        if key not in self._config:
            self.__dict__[key] = self._config[key] = ConfigurationSection(self)

        return self._config[key]

    def __setitem__(self, key, value):
        self.__dict__[key] = value
        self._config[key] = value

    def __delitem__(self, key):
        if key in self.__dict__ and key[0] != '_':
            del self.__dict__[key]
        if key in self._config:
            del self._config[key]


class ConfigurationSection(Configuration):
    def __init__(self, parent, *args, **kwargs):
        super(ConfigurationSection, self).__init__(*args, **kwargs)
        self.parent = parent

    def __getitem__(self, key):
        """Returns a config value, pulling from the `user` section as a fallback.
        """
        if key in self._config:
            return self._config[key]

        elif key in self.parent.user:
            return self.parent.user[key]

        return None


def handle_store_boolean(self, *args, **kwargs):
    """Does the add_argument for action='store_boolean'.
    """
    disabled_args = None
    disabled_kwargs = kwargs.copy()
    disabled_kwargs['action'] = 'store_false'
    disabled_kwargs['dest'] = self.get_argument_name(*args, **kwargs)
    disabled_kwargs['help'] = 'Disable ' + kwargs['help']
    kwargs['action'] = 'store_true'
    kwargs['help'] = 'Enable ' + kwargs['help']

    for flag in args:
        if flag[:2] == '--':
            disabled_args = ('--no-' + flag[2:],)
            break

    self.add_argument(*args, **kwargs)
    self.add_argument(*disabled_args, **disabled_kwargs)

    return (args, kwargs, disabled_args, disabled_kwargs)


class SubparserWrapper(object):
    """Wrap subparsers so we can populate the normal and the shadow parser.
    """

    def __init__(self, cli, submodule, subparser):
        self.cli = cli
        self.submodule = submodule
        self.subparser = subparser

        for attr in dir(subparser):
            if not hasattr(self, attr):
                setattr(self, attr, getattr(subparser, attr))

    def completer(self, completer):
        """Add an arpcomplete completer to this subcommand.
        """
        self.subparser.completer = completer

    def add_argument(self, *args, **kwargs):
        if 'action' in kwargs and kwargs['action'] == 'store_boolean':
            return handle_store_boolean(self, *args, **kwargs)

        self.cli.acquire_lock()
        self.subparser.add_argument(*args, **kwargs)

        if 'default' in kwargs:
            del kwargs['default']
        if 'action' in kwargs and kwargs['action'] == 'store_false':
            kwargs['action'] == 'store_true'
        self.cli.subcommands_default[self.submodule].add_argument(*args, **kwargs)
        self.cli.release_lock()


class MILC(object):
    """MILC - An Opinionated Batteries Included Framework
    """

    def __init__(self):
        """Initialize the MILC object.
        """
        # Setup a lock for thread safety
        self._lock = threading.RLock() if thread else None

        # Define some basic info
        self.acquire_lock()
        self._description = None
        self._entrypoint = None
        self._inside_context_manager = False
        self.ansi = ansi_colors
        self.arg_only = []
        self.config = Configuration()
        self.config_file = None
        self.version = os.environ.get('QMK_VERSION', 'unknown')
        self.release_lock()

        # Figure out our program name
        self.prog_name = sys.argv[0][:-3] if sys.argv[0].endswith('.py') else sys.argv[0]
        self.prog_name = self.prog_name.split('/')[-1]

        # Initialize all the things
        self.initialize_argparse()
        self.initialize_logging()

    @property
    def description(self):
        return self._description

    @description.setter
    def description(self, value):
        self._description = self._arg_parser.description = self._arg_defaults.description = value

    def echo(self, text, *args, **kwargs):
        """Print colorized text to stdout.

        ANSI color strings (such as {fg-blue}) will be converted into ANSI
        escape sequences, and the ANSI reset sequence will be added to all
        strings.

        If *args or **kwargs are passed they will be used to %-format the strings.
        """
        if args and kwargs:
            raise RuntimeError('You can only specify *args or **kwargs, not both!')

        args = args or kwargs
        text = format_ansi(text)

        print(text % args)

    def initialize_argparse(self):
        """Prepare to process arguments from sys.argv.
        """
        kwargs = {
            'fromfile_prefix_chars': '@',
            'conflict_handler': 'resolve',
        }

        self.acquire_lock()
        self.subcommands = {}
        self.subcommands_default = {}
        self._subparsers = None
        self._subparsers_default = None
        self.argwarn = argcomplete.warn
        self.args = None
        self._arg_defaults = argparse.ArgumentParser(**kwargs)
        self._arg_parser = argparse.ArgumentParser(**kwargs)
        self.set_defaults = self._arg_parser.set_defaults
        self.print_usage = self._arg_parser.print_usage
        self.print_help = self._arg_parser.print_help
        self.release_lock()

    def completer(self, completer):
        """Add an argcomplete completer to this subcommand.
        """
        self._arg_parser.completer = completer

    def add_argument(self, *args, **kwargs):
        """Wrapper to add arguments to both the main and the shadow argparser.
        """
        if 'action' in kwargs and kwargs['action'] == 'store_boolean':
            return handle_store_boolean(self, *args, **kwargs)

        if kwargs.get('add_dest', True) and args[0][0] == '-':
            kwargs['dest'] = 'general_' + self.get_argument_name(*args, **kwargs)
        if 'add_dest' in kwargs:
            del kwargs['add_dest']

        self.acquire_lock()
        self._arg_parser.add_argument(*args, **kwargs)

        # Populate the shadow parser
        if 'default' in kwargs:
            del kwargs['default']
        if 'action' in kwargs and kwargs['action'] == 'store_false':
            kwargs['action'] == 'store_true'
        self._arg_defaults.add_argument(*args, **kwargs)
        self.release_lock()

    def initialize_logging(self):
        """Prepare the defaults for the logging infrastructure.
        """
        self.acquire_lock()
        self.log_file = None
        self.log_file_mode = 'a'
        self.log_file_handler = None
        self.log_print = True
        self.log_print_to = sys.stderr
        self.log_print_level = logging.INFO
        self.log_file_level = logging.DEBUG
        self.log_level = logging.INFO
        self.log = logging.getLogger(self.__class__.__name__)
        self.log.setLevel(logging.DEBUG)
        logging.root.setLevel(logging.DEBUG)
        self.release_lock()

        self.add_argument('-V', '--version', version=self.version, action='version', help='Display the version and exit')
        self.add_argument('-v', '--verbose', action='store_true', help='Make the logging more verbose')
        self.add_argument('--datetime-fmt', default='%Y-%m-%d %H:%M:%S', help='Format string for datetimes')
        self.add_argument('--log-fmt', default='%(levelname)s %(message)s', help='Format string for printed log output')
        self.add_argument('--log-file-fmt', default='[%(levelname)s] [%(asctime)s] [file:%(pathname)s] [line:%(lineno)d] %(message)s', help='Format string for log file.')
        self.add_argument('--log-file', help='File to write log messages to')
        self.add_argument('--color', action='store_boolean', default=True, help='color in output')
        self.add_argument('-c', '--config-file', help='The config file to read and/or write')
        self.add_argument('--save-config', action='store_true', help='Save the running configuration to the config file')

    def add_subparsers(self, title='Sub-commands', **kwargs):
        if self._inside_context_manager:
            raise RuntimeError('You must run this before the with statement!')

        self.acquire_lock()
        self._subparsers_default = self._arg_defaults.add_subparsers(title=title, dest='subparsers', **kwargs)
        self._subparsers = self._arg_parser.add_subparsers(title=title, dest='subparsers', **kwargs)
        self.release_lock()

    def acquire_lock(self):
        """Acquire the MILC lock for exclusive access to properties.
        """
        if self._lock:
            self._lock.acquire()

    def release_lock(self):
        """Release the MILC lock.
        """
        if self._lock:
            self._lock.release()

    def find_config_file(self):
        """Locate the config file.
        """
        if self.config_file:
            return self.config_file

        if self.args and self.args.general_config_file:
            return self.args.general_config_file

        return os.path.join(user_config_dir(appname='qmk', appauthor='QMK'), '%s.ini' % self.prog_name)

    def get_argument_name(self, *args, **kwargs):
        """Takes argparse arguments and returns the dest name.
        """
        try:
            return self._arg_parser._get_optional_kwargs(*args, **kwargs)['dest']
        except ValueError:
            return self._arg_parser._get_positional_kwargs(*args, **kwargs)['dest']

    def argument(self, *args, **kwargs):
        """Decorator to call self.add_argument or self.<subcommand>.add_argument.
        """
        if self._inside_context_manager:
            raise RuntimeError('You must run this before the with statement!')

        def argument_function(handler):
            if 'arg_only' in kwargs and kwargs['arg_only']:
                arg_name = self.get_argument_name(*args, **kwargs)
                self.arg_only.append(arg_name)
                del kwargs['arg_only']

            if handler is self._entrypoint:
                self.add_argument(*args, **kwargs)

            elif handler.__name__ in self.subcommands:
                self.subcommands[handler.__name__].add_argument(*args, **kwargs)

            else:
                raise RuntimeError('Decorated function is not entrypoint or subcommand!')

            return handler

        return argument_function

    def arg_passed(self, arg):
        """Returns True if arg was passed on the command line.
        """
        return self.args_passed[arg] in (None, False)

    def parse_args(self):
        """Parse the CLI args.
        """
        if self.args:
            self.log.debug('Warning: Arguments have already been parsed, ignoring duplicate attempt!')
            return

        argcomplete.autocomplete(self._arg_parser)

        self.acquire_lock()
        self.args = self._arg_parser.parse_args()
        self.args_passed = self._arg_defaults.parse_args()

        if 'entrypoint' in self.args:
            self._entrypoint = self.args.entrypoint

        if self.args.general_config_file:
            self.config_file = self.args.general_config_file

        self.release_lock()

    def read_config(self):
        """Parse the configuration file and determine the runtime configuration.
        """
        self.acquire_lock()
        self.config_file = self.find_config_file()

        if self.config_file and os.path.exists(self.config_file):
            config = RawConfigParser(self.config)
            config.read(self.config_file)

            # Iterate over the config file options and write them into self.config
            for section in config.sections():
                for option in config.options(section):
                    value = config.get(section, option)

                    # Coerce values into useful datatypes
                    if value.lower() in ['1', 'yes', 'true', 'on']:
                        value = True
                    elif value.lower() in ['0', 'no', 'false', 'none', 'off']:
                        value = False
                    elif value.replace('.', '').isdigit():
                        if '.' in value:
                            value = Decimal(value)
                        else:
                            value = int(value)

                    self.config[section][option] = value

        # Fold the CLI args into self.config
        for argument in vars(self.args):
            if argument in ('subparsers', 'entrypoint'):
                continue

            if '_' in argument:
                section, option = argument.split('_', 1)
            else:
                section = self._entrypoint.__name__
                option = argument

            if option not in self.arg_only:
                if hasattr(self.args_passed, argument):
                    arg_value = getattr(self.args, argument)
                    if arg_value:
                        self.config[section][option] = arg_value
                else:
                    if option not in self.config[section]:
                        self.config[section][option] = getattr(self.args, argument)

        self.release_lock()

    def save_config(self):
        """Save the current configuration to the config file.
        """
        self.log.debug("Saving config file to '%s'", self.config_file)

        if not self.config_file:
            self.log.warning('%s.config_file file not set, not saving config!', self.__class__.__name__)
            return

        self.acquire_lock()

        config = RawConfigParser()
        config_dir = os.path.dirname(self.config_file)

        for section_name, section in self.config._config.items():
            config.add_section(section_name)
            for option_name, value in section.items():
                if section_name == 'general':
                    if option_name in ['save_config']:
                        continue
                config.set(section_name, option_name, str(value))

        if not os.path.exists(config_dir):
            os.makedirs(config_dir)

        with NamedTemporaryFile(mode='w', dir=config_dir, delete=False) as tmpfile:
            config.write(tmpfile)

        # Move the new config file into place atomically
        if os.path.getsize(tmpfile.name) > 0:
            os.rename(tmpfile.name, self.config_file)
        else:
            self.log.warning('Config file saving failed, not replacing %s with %s.', self.config_file, tmpfile.name)

        self.release_lock()
        cli.log.info('Wrote configuration to %s', shlex.quote(self.config_file))

    def __call__(self):
        """Execute the entrypoint function.
        """
        if not self._inside_context_manager:
            # If they didn't use the context manager use it ourselves
            with self:
                return self.__call__()

        if not self._entrypoint:
            raise RuntimeError('No entrypoint provided!')

        return self._entrypoint(self)

    def entrypoint(self, description):
        """Set the entrypoint for when no subcommand is provided.
        """
        if self._inside_context_manager:
            raise RuntimeError('You must run this before cli()!')

        self.acquire_lock()
        self.description = description
        self.release_lock()

        def entrypoint_func(handler):
            self.acquire_lock()
            self._entrypoint = handler
            self.release_lock()

            return handler

        return entrypoint_func

    def add_subcommand(self, handler, description, name=None, **kwargs):
        """Register a subcommand.

        If name is not provided we use `handler.__name__`.
        """
        if self._inside_context_manager:
            raise RuntimeError('You must run this before the with statement!')

        if self._subparsers is None:
            self.add_subparsers()

        if not name:
            name = handler.__name__

        self.acquire_lock()
        kwargs['help'] = description
        self.subcommands_default[name] = self._subparsers_default.add_parser(name, **kwargs)
        self.subcommands[name] = SubparserWrapper(self, name, self._subparsers.add_parser(name, **kwargs))
        self.subcommands[name].set_defaults(entrypoint=handler)

        if name not in self.__dict__:
            self.__dict__[name] = self.subcommands[name]
        else:
            self.log.debug("Could not add subcommand '%s' to attributes, key already exists!", name)

        self.release_lock()

        return handler

    def subcommand(self, description, **kwargs):
        """Decorator to register a subcommand.
        """

        def subcommand_function(handler):
            return self.add_subcommand(handler, description, **kwargs)

        return subcommand_function

    def setup_logging(self):
        """Called by __enter__() to setup the logging configuration.
        """
        if len(logging.root.handlers) != 0:
            # MILC is the only thing that should have root log handlers
            logging.root.handlers = []

        self.acquire_lock()

        if self.config['general']['verbose']:
            self.log_print_level = logging.DEBUG

        self.log_file = self.config['general']['log_file'] or self.log_file
        self.log_file_format = self.config['general']['log_file_fmt']
        self.log_file_format = ANSIStrippingFormatter(self.config['general']['log_file_fmt'], self.config['general']['datetime_fmt'])
        self.log_format = self.config['general']['log_fmt']

        if self.config.general.color:
            self.log_format = ANSIEmojiLoglevelFormatter(self.args.general_log_fmt, self.config.general.datetime_fmt)
        else:
            self.log_format = ANSIStrippingFormatter(self.args.general_log_fmt, self.config.general.datetime_fmt)

        if self.log_file:
            self.log_file_handler = logging.FileHandler(self.log_file, self.log_file_mode)
            self.log_file_handler.setLevel(self.log_file_level)
            self.log_file_handler.setFormatter(self.log_file_format)
            logging.root.addHandler(self.log_file_handler)

        if self.log_print:
            self.log_print_handler = logging.StreamHandler(self.log_print_to)
            self.log_print_handler.setLevel(self.log_print_level)
            self.log_print_handler.setFormatter(self.log_format)
            logging.root.addHandler(self.log_print_handler)

        self.release_lock()

    def __enter__(self):
        if self._inside_context_manager:
            self.log.debug('Warning: context manager was entered again. This usually means that self.__call__() was called before the with statement. You probably do not want to do that.')
            return

        self.acquire_lock()
        self._inside_context_manager = True
        self.release_lock()

        colorama.init()
        self.parse_args()
        self.read_config()
        self.setup_logging()

        if 'save_config' in self.config.general and self.config.general.save_config:
            self.save_config()
            exit(0)

        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.acquire_lock()
        self._inside_context_manager = False
        self.release_lock()

        if exc_type is not None and not isinstance(SystemExit(), exc_type):
            print(exc_type)
            logging.exception(exc_val)
            exit(255)


cli = MILC()

if __name__ == '__main__':

    @cli.argument('-c', '--comma', help='comma in output', default=True, action='store_boolean')
    @cli.entrypoint('My useful CLI tool with subcommands.')
    def main(cli):
        comma = ',' if cli.config.general.comma else ''
        cli.log.info('{bg_green}{fg_red}Hello%s World!', comma)

    @cli.argument('-n', '--name', help='Name to greet', default='World')
    @cli.subcommand('Description of hello subcommand here.')
    def hello(cli):
        comma = ',' if cli.config.general.comma else ''
        cli.log.info('{fg_blue}Hello%s %s!', comma, cli.config.hello.name)

    def goodbye(cli):
        comma = ',' if cli.config.general.comma else ''
        cli.log.info('{bg_red}Goodbye%s %s!', comma, cli.config.goodbye.name)

    @cli.argument('-n', '--name', help='Name to greet', default='World')
    @cli.subcommand('Think a bit before greeting the user.')
    def thinking(cli):
        comma = ',' if cli.config.general.comma else ''
        spinner = cli.spinner(text='Just a moment...', spinner='earth')
        spinner.start()
        sleep(2)
        spinner.stop()

        with cli.spinner(text='Almost there!', spinner='moon'):
            sleep(2)

        cli.log.info('{fg_cyan}Hello%s %s!', comma, cli.config.thinking.name)

    @cli.subcommand('Show off our ANSI colors.')
    def pride(cli):
        cli.echo('{bg_red}                    ')
        cli.echo('{bg_lightred_ex}                    ')
        cli.echo('{bg_lightyellow_ex}                    ')
        cli.echo('{bg_green}                    ')
        cli.echo('{bg_blue}                    ')
        cli.echo('{bg_magenta}                    ')

    # You can register subcommands using decorators as seen above, or using functions like like this:
    cli.add_subcommand(goodbye, 'This will show up in --help output.')
    cli.goodbye.add_argument('-n', '--name', help='Name to bid farewell to', default='World')

    cli()  # Automatically picks between main(), hello() and goodbye()
