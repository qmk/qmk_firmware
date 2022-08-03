"""Serve QMK documentation locally
"""
import http.server
import os
import shutil
import webbrowser

from milc import cli


@cli.argument('-p', '--port', default=8936, type=int, help='Port number to use.')
@cli.argument('-b', '--browser', action='store_true', help='Open the docs in the default browser.')
@cli.subcommand('Run a local webserver for QMK documentation.', hidden=False if cli.config.user.developer else True)
def docs(cli):
    """Spin up a local HTTP server for the QMK docs.
    """
    os.chdir('docs')

    # If docsify-cli is installed, run that instead so we get live reload
    if shutil.which('docsify'):
        command = ['docsify', 'serve', '--port', f'{cli.config.docs.port}', '--open' if cli.config.docs.browser else '']

        cli.log.info(f"Running {{fg_cyan}}{str.join(' ', command)}{{fg_reset}}")
        cli.log.info("Press Control+C to exit.")

        try:
            cli.run(command, capture_output=False)
        except KeyboardInterrupt:
            cli.log.info("Stopping HTTP server...")
    else:
        # Fall back to Python HTTPServer
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
