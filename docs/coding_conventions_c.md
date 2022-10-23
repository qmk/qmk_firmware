# Coding Conventions (C)

Most of our style is pretty easy to pick up on, but right now it's not entirely consistent. You should match the style of the code surrounding your change, but if that code is inconsistent or unclear use the following guidelines:

* We indent using four (4) spaces (soft tabs)
* We use a modified One True Brace Style
  * Opening Brace: At the end of the same line as the statement that opens the block
  * Closing Brace: Lined up with the first character of the statement that opens the block
  * Else If: Place the closing brace at the beginning of the line and the next opening brace at the end of the same line.
  * Optional Braces: Always include optional braces.
    * Good: if (condition) { return false; }
    * Bad: if (condition) return false;
* We encourage use of C style comments: `/* */`
  * Think of them as a story describing the feature
  * Use them liberally to explain why particular decisions were made.
  * Do not write obvious comments
  * If you're not sure if a comment is obvious, go ahead and include it.
* In general we don't wrap lines, they can be as long as needed. If you do choose to wrap lines please do not wrap any wider than 76 columns.
* We use `#pragma once` at the start of header files rather than old-style include guards (`#ifndef THIS_FILE_H`, `#define THIS_FILE_H`, ..., `#endif`)
* We accept both forms of preprocessor if's: `#ifdef DEFINED` and `#if defined(DEFINED)`
  * If you are not sure which to prefer use the `#if defined(DEFINED)` form.
  * Do not change existing code from one style to the other, except when moving to a multiple condition `#if`.
* When deciding how (or if) to indent preprocessor directives, keep these points in mind:
  * Readability is more important than consistency.
  * Follow the file's existing style. If the file is mixed, follow the style that makes sense for the section you are modifying.
  * When indenting, keep the hash at the start of the line and add whitespace between `#` and `if`, starting with 4 spaces after the `#`.
  * You can follow the indentation level of the surrounding C code, or preprocessor directives can have their own indentation levels. Choose the style that best communicates the intent of your code.

Here is an example for easy reference:

```c
/* Enums for foo */
enum foo_state {
    FOO_BAR,
    FOO_BAZ,
};

/* Returns a value */
int foo(void) {
    if (some_condition) {
        return FOO_BAR;
    } else {
        return -1;
    }
}
```

# Auto-formatting with clang-format

[Clang-format](https://clang.llvm.org/docs/ClangFormat.html) is part of LLVM and can automatically format your code for you, because ain't nobody got time to do it manually. We supply a configuration file for it that applies most of the coding conventions listed above. It will only change whitespace and newlines, so you will still have to remember to include optional braces yourself.

Use the [full LLVM installer](https://llvm.org/builds/) to get clang-format on Windows, or use `sudo apt install clang-format` on Ubuntu.

If you run it from the command-line, pass `-style=file` as an option and it will automatically find the .clang-format configuration file in the QMK root directory.

If you use VSCode, the standard C/C++ plugin supports clang-format, alternatively there is a [separate extension](https://marketplace.visualstudio.com/items?itemName=LLVMExtensions.ClangFormat) for it.

Some things (like LAYOUT macros) are destroyed by clang-format, so either don't run it on those files, or wrap the sensitive code in `// clang-format off` and `// clang-format on`.
