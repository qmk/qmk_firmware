"""Serve QMK documentation locally
"""
import http.server
import os

from milc import cli


@cli.argument('-p', '--port', default=8936, type=int, help='Port number to use.')
@cli.subcommand('Run a local webserver for QMK documentation.')
def docs(cli):
    """Spin up a local HTTPServer instance for the QMK docs.
    """
    os.chdir('docs')

    with http.server.HTTPServer(('', cli.config.docs.port), http.server.SimpleHTTPRequestHandler) as httpd:
        cli.log.info("Serving QMK docs at http://localhost:%d/", cli.config.docs.port)
        cli.log.info("Press Control+C to exit.")

        try:
            httpd.serve_forever()
        except KeyboardInterrupt:
            cli.log.info("Stopping HTTP server...")
        finally:
            httpd.shutdown()
