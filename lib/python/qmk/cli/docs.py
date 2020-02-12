"""Interact with QMK documentation locally
"""
import http.server
import os
import shutil
import subprocess
from pathlib import Path

from milc import cli

DOCS_PATH = Path('docs/')
BUILD_PATH = Path('.build/docs/')


def serve(dir):
    """Spin up a local HTTPServer instance for the QMK docs.
    """
    os.chdir(dir)

    with http.server.HTTPServer(('', cli.config.docs.port), http.server.SimpleHTTPRequestHandler) as httpd:
        cli.log.info("Serving %s QMK docs at http://localhost:%d/", dir, cli.config.docs.port)
        cli.log.info("Press Control+C to exit.")

        try:
            httpd.serve_forever()
        except KeyboardInterrupt:
            cli.log.info("Stopping HTTP server...")
        finally:
            httpd.shutdown()


def generate():
    """Invoke the docs generation process

    TODO(unclaimed):
        * [ ] Add a real build step... something static docs
    """

    if BUILD_PATH.exists():
        shutil.rmtree(BUILD_PATH)

    shutil.copytree(DOCS_PATH, BUILD_PATH)

    # When not verbose we want to hide all output
    args = {'check': True}
    if not cli.args.verbose:
        args.update({'stdout': subprocess.DEVNULL, 'stderr': subprocess.STDOUT})

    cli.log.info('Generating internal docs...')

    # Generate internal docs
    subprocess.run(['doxygen', 'Doxyfile'], **args)
    subprocess.run(['moxygen', '-q', '-a', '-g', '-o', BUILD_PATH / 'internals_%s.md', 'doxygen/xml'], **args)

    cli.log.info('Successfully generated internal docs to %s.', BUILD_PATH)


@cli.argument('-g', '--generate', arg_only=True, action='store_true', help='Generate docs.')
@cli.argument('-s', '--serve', arg_only=True, action='store_true', help='Serve docs locally.')
@cli.argument('-p', '--port', default=8936, type=int, help='Port number to use.')
@cli.subcommand('Local interactions wth QMK documentation.', hidden=False if cli.config.user.developer else True)
def docs(cli):
    if cli.args.generate:
        generate()
        # have we been asked to just serve the just generated docs?
        if cli.args.serve:
            serve(BUILD_PATH)
    else:
        # if --serve or invoked with no args
        serve(DOCS_PATH)
