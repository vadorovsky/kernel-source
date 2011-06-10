# Recurse into subdirectories and print symbols exported by built-in.o files

dir := $(obj)

makefile := $(lastword $(MAKEFILE_LIST))
sourcedir := $(dir $(makefile))
subdirs := $(wildcard $(dir)/*/.)
#$(shell echo "subdirs: $(subdirs)" >&2)
subdir_exports := $(patsubst %,%/.directory_symbols, $(subdirs))
builtin_o := $(dir)/built-in.o

all: $(dir)/.directory_symbols
	@:

$(dir)/.directory_symbols: $(subdir_exports)
	cat /dev/null $(subdir_exports) >$@
	for part in $$(grep -sv '/built-in\.o$$' $(builtin_o).parts); do \
		$(sourcedir)/symsets.pl --list-exported-symbols $$part | \
		awk 'BEGIN { FS = "\t" ; OFS = "\t" } { $$3 = $$3 "/built-in"; print }'; \
	done | sed 's:\./::g' >>$@
	if test -e $(builtin_o); then \
		$(sourcedir)/symsets.pl --list-exported-symbols $(builtin_o); \
	fi | sed 's:\./::g' >>$@

$(dir)/%/.directory_symbols:
	$(MAKE) -f $(makefile) obj=$(dir)/$*

