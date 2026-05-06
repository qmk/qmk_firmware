# Helper to determine if a compiler option is supported
# Args:
#   $(1) = option to test, if successful will be output
#   $(2) = option to use if $(1) is not supported
#   $(3) = additional arguments to pass to the compiler during the test, but aren't contained in the output
cc-option = $(shell \
	if { echo 'int main(){return 0;}' | $(CC) $(1) $(3) -o /dev/null -x c /dev/null >/dev/null 2>&1; }; \
	then echo "$(1)"; else echo "$(2)"; fi)

# Helper to pass comma character to make functions (use with `$(,)` to pass in `$(call ...)` arguments)
, := ,
