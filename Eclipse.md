[Eclipse](https://en.wikipedia.org/wiki/Eclipse_(software)) is an open-source [Integrated Development Environment](https://en.wikipedia.org/wiki/Integrated_development_environment) (IDE) widely used for Java development, but with an extensible plugin system that allows to customize it for other languages and usages.

Using an IDE such as Eclipse provides many advantages over a plain text editor, such as:
* intelligent code completion
* convenient navigation in the code
* refactoring tools
* build automation (no need for the command-line)
* a GUI for GIT
* static code analysis
* many other tools such as debugging, code formatting, showing call hierarchies etc.

The goal of the is page is to document how to set-up Eclipse for developing AVR software, and working on the QMK code base.

Note that this set-up has been tested on Ubuntu 16.04 only for the moment.

# Prerequisites
Before starting, you must have followed the [Getting Started](../#getting-started) section corresponding to your system. In particular, you must have been able to build the firmware with [the `make` command](../#the-make-command).

# Install Eclipse and its plugins
Eclipse comes in [several flavours](http://www.eclipse.org/downloads/eclipse-packages/) depending on the target usage that you will have. There is no package comprising the AVR stack, so we will need to start from Eclipse CDT (C/C++ Development Tooling) and install the necessary plugins.

## Download and install Eclipse CDT
If you already have Eclipse CDT on your system, you can skip this step. However it is advised to keep it up-to-date for better support.

If you have another Eclipse package installed, it is normally possible to [install the CDT plugin over it](https://eclipse.org/cdt/downloads.php). However it is probably better to reinstall it from scratch to keep it light and avoid the clutter of tools that you don't need for the projects you will be working on.

Installation is very simple:
* [Download Eclipse IDE for C/C++ Developers](http://www.eclipse.org/downloads/eclipse-packages/) ([direct link to current version](http://www.eclipse.org/downloads/packages/eclipse-ide-cc-developers/neonr)) from the official Eclipse website
* Extract the package to the location of your choice (this creates an `eclipse` folder)
* (optional) Rename the extracted `eclipse` folder to something more specific like `eclipse-cpp-neon-x64` (to avoid conflicts if you install several packages of Eclipse)

## Install the necessary plugins
(todo)

# Configure Eclipse for QMK
(todo)