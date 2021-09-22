"""Serve QMK documentation locally
"""
import http.server
import os
import webbrowser

from milc import cli


@cli.argument('-p', '--port', default=8936, type=int, help='Port number to use.')
@cli.argument('-b', '--browser', action='store_true', help='Open the docs in the default browser.')
@cli.subcommand('Run a local webserver for QMK documentation.', hidden=False if cli.config.user.developer else True)
def docs(cli):
    """Spin up a local HTTPServer instance for the QMK docs.
    """
    os.chdir('docs')

    with http.server.HTTPServer(('', cli.config.docs.port), http.server.SimpleHTTPRequestHandler) as httpd:
        cli.log.info(f"Serving QMK docs at http://localhost:{cli.config.docs.port}/")
        cli.log.info("Press Control+C to exit.")

        if cli.config.docs.browser:
            webbrowser.open(f'http://localhost:{cli.config.docs.port}')

        try:
            httpd.serve_forever()
        except KeyboardInterrupt:
            cli.log.info("Stopping HTTP server...")
        finally:
            httpd.shutdown()
