"""Used by the make system to generate files for community modules unit tests.
"""
from pathlib import Path
from milc import cli

import qmk.path
from qmk.commands import dump_lines
from qmk.community_modules import module_api_list
from qmk.constants import GPL2_HEADER_SH_LIKE, GENERATED_HEADER_SH_LIKE

from qmk.cli.generate.community_modules import (
    generate_community_modules_h_lines,
    generate_community_modules_c_lines,
    _generate_modules_rules_from_list,
    _generate_include_per_module_from_list,
)


@cli.argument('-o', '--output-dir', arg_only=True, type=qmk.path.normpath, required=True, help='Directory to write generated files to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.argument('-m', '--modules', arg_only=True, required=True, help='Space-separated list of community modules to enable')
@cli.subcommand('Creates community modules files for testing.')
def generate_test_community_modules(cli):
    """Creates community_modules.h, community_modules.c, community_rules.mk, and introspection files for unit testing.
    """
    output_dir = cli.args.output_dir
    modules = list(dict.fromkeys(cli.args.modules.split()))

    if not modules:
        cli.log.error("No modules specified.")
        return False

    # Check for duplicate module names.
    seen = set()
    for module in modules:
        module_slug = Path(module).name.lower()
        if module_slug in seen:
            duplicates = list(filter(lambda m: Path(m).name.lower() == module_slug, modules))
            cli.log.error(f'Duplicate module name detected: "{module_slug}" - {duplicates}')
            return False
        seen.add(module_slug)

    output_dir.mkdir(parents=True, exist_ok=True)

    api_list, api_version, ver_major, ver_minor, ver_patch = module_api_list()

    # Generate community_rules.mk.
    rules_lines = [GPL2_HEADER_SH_LIKE, GENERATED_HEADER_SH_LIKE]
    rules_lines.extend(_generate_modules_rules_from_list(modules))
    rules_lines.append('# Generated module wrappers compiled into the test suite')
    rules_lines.append(f'SRC += {qmk.path.unix_style_path(output_dir)}/community_modules.c')
    dump_lines(output_dir / 'community_rules.mk', rules_lines, cli.args.quiet)

    # Generate community_modules.h.
    h_lines = generate_community_modules_h_lines(modules)
    dump_lines(output_dir / 'community_modules.h', h_lines, cli.args.quiet, remove_repeated_newlines=True)

    # Generate community_modules.c.
    c_lines = generate_community_modules_c_lines(modules)
    dump_lines(output_dir / 'community_modules.c', c_lines, cli.args.quiet, remove_repeated_newlines=True)

    # Generate community_modules_introspection.h.
    introspection_h_lines = _generate_include_per_module_from_list(modules, 'introspection.h')
    dump_lines(output_dir / 'community_modules_introspection.h', introspection_h_lines, cli.args.quiet, remove_repeated_newlines=True)

    # Generate community_modules_introspection.c.
    introspection_c_lines = _generate_include_per_module_from_list(modules, 'introspection.c')
    dump_lines(output_dir / 'community_modules_introspection.c', introspection_c_lines, cli.args.quiet, remove_repeated_newlines=True)

    # Generate led_matrix_community_modules.inc.
    led_matrix_lines = _generate_include_per_module_from_list(modules, 'led_matrix_module.inc')
    dump_lines(output_dir / 'led_matrix_community_modules.inc', led_matrix_lines, cli.args.quiet, remove_repeated_newlines=True)

    # Generate rgb_matrix_community_modules.inc.
    rgb_matrix_lines = _generate_include_per_module_from_list(modules, 'rgb_matrix_module.inc')
    dump_lines(output_dir / 'rgb_matrix_community_modules.inc', rgb_matrix_lines, cli.args.quiet, remove_repeated_newlines=True)

    if not cli.args.quiet:
        cli.log.info(f"Generated test community module files in {output_dir}")

    return True
