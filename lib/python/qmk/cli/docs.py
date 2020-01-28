"""Serve QMK documentation locally
"""
import http.server
import os
import shutil
import subprocess
from pathlib import Path

from milc import cli

def serve(dir):
    """Spin up a local HTTPServer instance for the QMK docs.
    """
    os.chdir(dir)

    with http.server.HTTPServer(('', cli.config.docs.port), http.server.SimpleHTTPRequestHandler) as httpd:
        cli.log.info("Serving QMK docs at http://localhost:%d/", cli.config.docs.port)
        cli.log.info("Press Control+C to exit.")

        try:
            httpd.serve_forever()
        except KeyboardInterrupt:
            cli.log.info("Stopping HTTP server...")
        finally:
            httpd.shutdown()

def build():
    """
    Invoke the docs build process

    TODO(unclaimed):
        * [ ] Add a real build step... something static docs
    """

    input_path = Path('docs')
    output_path = Path('.build/docs')

    if output_path.exists():
        shutil.rmtree(output_path)

    shutil.copytree(input_path, output_path)

    #Generate internal docs
    doxygen = subprocess.run(['doxygen', 'Doxyfile'])
    moxygen = subprocess.run(['npx', 'moxygen', '-q', '-a', '-g', '-o', '.build/docs/internals_%s.md', 'doxygen/xml'])

@cli.argument('-b', '--build', arg_only=True, action='store_true', help='Build.')
@cli.argument('-s', '--serve', arg_only=True, action='store_true', help='Serve docs locally.')
@cli.argument('-p', '--port', default=8936, type=int, help='Port number to use.')
@cli.subcommand('Local interactins wth QMK documentation.', hidden=False if cli.config.user.developer else True)
def docs(cli):
    if cli.args.build:
        build()
        if cli.args.serve:
            serve('.build/docs')
    else:
        # default to just serve the docs folder
        serve('docs')
