# Unit Testing

If you are new to unit testing, then you can find many good resources on internet. However most of it is scattered around in small pieces here and there, and there's also many different opinions, so I won't give any recommendations.

Instead I recommend these two books, explaining two different styles of Unit Testing in detail.

* "Test Driven Development: By Example: Kent Beck"
* "Growing Object-Oriented Software, Guided By Tests: Steve Freeman, Nat Pryce"

If you prefer videos there are Uncle Bob's [Clean Coders Videos](https://cleancoders.com/), which unfortunately cost quite a bit, especially if you want to watch many of them. But James Shore has a free [Let's Play](http://www.jamesshore.com/Blog/Lets-Play) video series.

## Google Test and Google Mock
It's possible to Unit Test your code using [Google Test](https://github.com/google/googletest). The Google Test framework also includes another component for writing testing mocks and stubs, called "Google Mock". For information how to write the actual tests, please refer to the documentation on that site.

## Use of C++

Note that Google Test and therefore any test has to be written in C++, even if the rest of the QMK codebases is written in C. This should hopefully not be a problem even if you don't know any C++, since there's quite clear documentation and examples of the required C++ features, and you can write the rest of the test code almost as you would write normal C. Note that some compiler errors which you might get can look quite scary, but just read carefully what it says, and you should be ok.

One thing to remember, is that you have to append `extern "C"` around all of your C file includes.

## Adding tests for new or existing features

If you want to unit test some feature, then take a look at the existing serial_link tests, in the `quantum/serial_link/tests folder`, and follow the steps below to create a similar structure.

1. If it doesn't already exist, add a test subfolder to the folder containing the feature.
2. Create a `testlist.mk` and a `rules.mk` file in that folder.
3. Include those files from the root folder `testlist.mk`and `build_test.mk` respectively.
4. Add a new name for your testgroup to the `testlist.mk` file. Each group defined there will be a separate executable. And that's how you can support mocking out different parts. Note that it's worth adding some common prefix, just like it's done for the serial_link tests. The reason for that is that the make command allows substring filtering, so this way you can easily run a subset of the tests.
5. Define the source files and required options in the `rules.mk` file.
   * `_SRC` for source files
   * `_DEFS` for additional defines
   * `_INC` for additional include folders
6. Write the tests in a new cpp file inside the test folder you created. That file has to be one of the files included from the `rules.mk` file.

Note how there's several different tests, each mocking out a separate part. Also note that each of them only compiles the very minimum that's needed for the tests. It's recommend that you try to do the same. For a relevant video check out [Matt Hargett "Advanced Unit Testing in C & C++](https://www.youtube.com/watch?v=Wmy6g-aVgZI)

## Running the tests

To run all the tests in the codebase, type `make test`. You can also run test matching a substring by typing `make test:matchingsubstring` Note that the tests are always compiled with the native compiler of your platform, so they are also run like any other program on your computer.

## Debugging the tests

If there are problems with the tests, you can find the executable in the `./build/test` folder. You should be able to run those with GDB or a similar debugger.

## Full Integration tests

It's not yet possible to do a full integration test, where you would compile the whole firmware and define a keymap that you are going to test. However there are plans for doing that, because writing tests that way would probably be easier, at least for people that are not used to unit testing.

In that model you would emulate the input, and expect a certain output from the emulated keyboard.

# Tracing variables 

Sometimes you might wonder why a variable gets changed and where, and this can be quite tricky to track down without having a debugger. It's of course possible to manually add print statements to track it, but you can also enable the variable trace feature. This works for both for variables that are changed by the code, and when the variable is changed by some memory corruption.

To take the feature into use add `VARIABLE_TRACE=x` to the end of you make command. `x` represents the number of variables you want to trace, which is usually 1. 

Then at a suitable place in the code, call `ADD_TRACED_VARIABLE`, to begin the tracing. For example to trace all the layer changes, you can do this
```c
void matrix_init_user(void) {
  ADD_TRACED_VARIABLE("layer", &layer_state, sizeof(layer_state));
}
```

This will add a traced variable named "layer" (the name is just for your information), which tracks the memory location of `layer_state`. It tracks 4 bytes (the size of `layer_state`), so any modification to the variable will be reported. By default you can not specify a size bigger than 4, but you can change it by adding `MAX_VARIABLE_TRACE_SIZE=x` to the end of the make command line.

In order to actually detect changes to the variables you should call `VERIFY_TRACED_VARIABLES` around the code that you think that modifies the variable. If a variable is modified it will tell you between which two `VERIFY_TRACED_VARIABLES` calls the modification happened. You can then add more calls to track it down further. I don't recommend spamming the codebase with calls. It's better to start with a few, and then keep adding them in a binary search fashion. You can also delete the ones you don't need, as each call need to store the file name and line number in the ROM, so you can run out of memory if you add too many calls.

Also remember to delete all the tracing code once you have found the bug, as you wouldn't want to create a pull request with tracing code.