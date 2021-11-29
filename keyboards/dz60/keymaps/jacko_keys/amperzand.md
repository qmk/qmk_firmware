# `amperzand` the Language Outline
So imagine a `.html` page. If the parse starts in the abstract syntax tree of `amperzand` and `<` opening a tag is treated as a statement until `<z />` closes the statement back into the language syntax tree as a printed literal, it becomes an easy extension of a C style syntax with duck typing (but not coercion to stings as I hate that "feature").

* A - `&amp;` - a literal of use.
* B - `break;`
* C - `continue;`
* D - `do {} while();`
* E - `export <name>` - a prefix which exports a name, perhaps even as assigned.
* F - `for(;;) {}`
* G - `gallowed <sub-name>;` - a prefix which allows a hash loaded usage of a new included sub-file.
* H - `hallowed <super-name>;` - a prefix which allows a file to be used by inclusion in a super file.
* I - `if() {} else {}`
* J - `true`
* K - `false`
* L - `&lt;` - another useful literal.
* M - `main(<number>) {}` - a numbered from zero parameter argument with anonymous inner class extension.
* N - `new <file-name>(<args>) {}` - instancing a new file as an object with anonymous outer class extension.
* O - `obj(<string>)` - parses a new object from string.
* P - `&apos;` - occasionally useful.
* Q - `&quot;` - more useful.
* R - `return <x>;`
* S - `switch() { case : break; default: break; }`
* T - `this` - object orientation.
* U - `utf8(<obj>)` - make an explicit string cast.
* V - `void(<obj>)` - a void object with a sub-object explanation monad.
* W - `while() {}`
* X - `xref(<string>)` - a string to variable reference lookup. Maybe used on the LHS of assignment.
* Y - `yield <x>;` - a return variant for continuations.
* Z - `<z />` - a syntax end delimiter of the HTML statement.

And that's about it. Default values from code would have to be entered through the DOM. I think it's technically sufficient.
