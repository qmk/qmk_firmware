# How To Add Features To QMK

If you have an idea for a custom feature or extra hardware connection, we'd love to accept it into QMK! 

Before you put a lot of work into building your new feature you should make sure you are implementing it in the best way. You can get a basic understanding of QMK by reading [Understaning QMK](understanding_qmk.html), which will take you on a tour of the QMK program flow. From here you should talk to us to get a sense of the best way to implement your idea. There are two main ways to do this:

* [Chat on Gitter](https://gitter.im/qmk/qmk_firmware)
* [Open an Issue](https://github.com/qmk/qmk_firmware/issues/new)

Once you have implemented your new feature you will generally submit a [pull request](https://github.com/qmk/qmk_firmware/pulls). Here are some things to keep in mind when creating one:

* **Disabled by default** - memory is a pretty limited on most chips QMK supports, and it's important that current keymaps aren't broken, so please allow your feature to be turned **on**, rather than being turned off. If you think it should be on by default, or reduces the size of the code, please talk with us about it.
* **Compile locally before submitting** - hopefully this one is obvious, but things need to compile! Our Travis system will catch any issues, but it's generally faster for you to compile a few keyboards locally instead of waiting for the results to come back.
* **Consider subprojects and different chip-bases** - there are several keyboards that have subprojects that allow for slightly different configurations, and even different chip-bases. Try to make a feature supported in ARM and AVR, or automatically disabled on platforms it doesn't work on.
* **Explain your feature** - Document it in `docs/`, either as a new file or as part of an existing file. If you don't document it other people won't be able to benefit from your hard work.
* **Don't refactor code** - to maintain a clear vision of how things are laid out in QMK, we try to plan out refactors in-depth, and have a collaborator make the changes. If you have an idea for refactoring, or suggestions, [open an issue](https://github.com/qmk/qmk_firmware/issues), we'd love to talk about how QMK can be improved.
