"""Serve QMK documentation locally
"""
import http.server

from milc import cli


class DocsHandler(http.server.SimpleHTTPRequestHandler):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, directory='docs', **kwargs)


@cli.argument('-p', '--port', default=8080, help='Port number to use.')
@cli.subcommand('Local instance of QMK docs')
def docs(cli):
    """Spin up a local HTTPServer instance for the QMK docs.
    """
    with http.server.HTTPServer(('', cli.config.docs.port), DocsHandler) as httpd:
        cli.log.info("Serving QMK docs locally on port %d.", cli.config.docs.port)
        cli.log.info("Press Control+C to exit.")

        httpd.serve_forever()
