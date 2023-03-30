# Raspberry Pi Pico SDK

The Raspberry Pi Pico SDK (Software Development Kit), henceforth SDK, provides the headers, libraries and build system necessary to write programs for RP2040-based devices such as the Raspberry Pi Pico in C, C++ or assembly language. The SDK is designed to provide an API (Application Programming Interface) and programming environment that is familiar both to non-embedded C developers and embedded C developers alike.

A single program runs on the device at a time with a conventional `main()` method. Standard C/C++ libraries are supported along with APIs for accessing the RP2040’s hardware, including DMA, IRQs, and the wide variety of fixed-function peripherals and PIO (Programmable IO).

Additionally the SDK provides higher-level libraries for dealing with timers, USB, synchronization and multi-core programming, along with additional high-level functionality built using PIO, such as audio. The SDK can be used to build anything from simple applications, or full-fledged runtime environments such as MicroPython, to low-level software such as the RP2040’s on-chip bootrom itself.

This documentation is generated from the SDK source tree using Doxygen. It provides basic information on the APIs used for each library, but does not provide usage information. Please refer to the Databooks for usage and more technical information.

## SDK Design

The RP2040 is a powerful chip, however it is an embedded environment, so both RAM and program space are at premium. Additionally the trade-offs between performance and other factors (e.g. edge-case error handling, runtime vs compile-time configuration) are necessarily much more visible to the developer than they might be on other higher-level platforms.

The intention within the SDK has been for features to just work out of the box, with sensible defaults, but also to give the developer as much control and power as possible (if they want it) to fine-tune every aspect of the application they are building and the libraries used.

## The Build System

The SDK uses CMake to manage the build. CMake is widely supported by IDEs (Integrated Development Environments), and allows a simple specification of the build (via `CMakeLists.txt` files), from which CMake can generate a build system (for use by `make`, `ninja` or other build tools) customized for the platform and by any configuration variables the developer chooses.

Apart from being a widely-used build system for C/C++ development, CMake is fundamental to the way the SDK is structured, and how applications are configured and built.

The SDK builds an executable which is bare-metal, i.e. it includes the entirety of the code needed to run on the device (other than floating-point and other optimized code contained in the bootrom within the RP2040).

## Examples

This SDK documentation contains a number of example code fragments. An index of these examples can be found [here](@ref examples_page). These examples, and any other source code included in this documentation, is Copyright &copy; 2020 Raspberry Pi (Trading) Ltd. and licensed under the [3-Clause BSD](https://opensource.org/licenses/BSD-3-Clause) license.

