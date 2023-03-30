# Contributing to Raspberry Pi Pico C/C++ SDK

## How to Report a Bug

We use GitHub to host code, track [issues](https://github.com/raspberrypi/pico-sdk/issues) and feature requests, and to accept [pull requests](https://github.com/raspberrypi/pico-sdk/pulls). If you find think you have found a bug in the SDK please report it by [opening a new issue](https://github.com/raspberrypi/pico-sdk/issues/new). Please include as much detail as possible, and ideally some code to reproduce the problem.

## How to Contribute Code

In order to contribute new or updated code, you must first create a GitHub account and fork the original repository to your own account. You can make changes, save them in your repository, then [make a pull request](https://docs.github.com/en/github/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/creating-a-pull-request-from-a-fork) against this repository. The pull request will appear [in the repository](https://github.com/raspberrypi/pico-sdk/pulls) where it can be assessed by the maintainers, and if appropriate, merged with the official repository.

**NOTE:** Development takes place on the `develop` branch in this repository. Please open your https://github.com/raspberrypi/pico-sdk/pulls[pull request] (PR) against the [`develop`](https://github.com/raspberrypi/pico-sdk/tree/develop) branch, pull requests against the `master` branch will automatically CI fail checks and will not be accepted. You will be asked to rebase your PR against `develop` and if you do not do so, your PR will be closed.

While we are happy to take contributions, big or small, changes in the SDK may have knock-on effects in other places so it is possible that apparently benign pull requests that make seemingly small changes could be refused. 

### Code Style

If you are contributing new or updated code please match the existing code style, particularly:

* Use 4 spaces for indentation rather than tabs.
* Braces are required for everything except single line `if` statements.
* Opening braces should not be placed on a new line.

### Licensing 

Code in this repository is lisensed under the [BSD-3 License](LICENSE.TXT). By contributing content to this repository you are agreeing to place your contributions under this licence.
