"""Serve QMK documentation locally
"""
import http.server
from os import chdir

from milc import cli


@cli.argument('-p', '--port', default=8080, help='Port number to use.')
@cli.subcommand('Local instance of QMK docs')
def docs(cli):
    """Spin up a local HTTPServer instance for the QMK docs.
    """
    cli.log.info("Serving QMK docs locally on port %d.", cli.config.docs.port)
    cli.log.info("Press Control+C to exit.")

    chdir('docs')

    httpd = http.server.HTTPServer(('', cli.config.docs.port), http.server.SimpleHTTPRequestHandler)
    httpd.serve_forever()
