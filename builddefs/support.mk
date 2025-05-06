# Helper to determine if a compiler option is supported
cc-option = $(shell \
	if { echo 'int main(){return 0;}' | $(CC) $(1) $(3) -o /dev/null -x c /dev/null >/dev/null 2>&1; }; \
	then echo "$(1)"; else echo "$(2)"; fi)

# Helper to pass comma character to make functions (use with `$(,)` to pass in `$(call ...)` arguments)
, := ,
