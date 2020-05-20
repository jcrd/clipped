VERSIONCMD = git describe --dirty --tags --always 2> /dev/null
VERSION := $(shell $(VERSIONCMD) || cat VERSION)

PREFIX ?= /usr/local
BINPREFIX ?= $(PREFIX)/bin
LIBPREFIX ?= $(PREFIX)/lib
MANPREFIX ?= $(PREFIX)/share/man

CPPFLAGS += -D_POSIX_C_SOURCE=200809L -DVERSION=\"$(VERSION)\"
CFLAGS += -std=c99 -Wall -Wextra
LDLIBS = $(shell pkgconf --libs x11 xfixes)

OBJ = clipped.o
MANPAGE = clipped.1

all: clipped $(MANPAGE)

clipped: $(OBJ)

$(MANPAGE): man/$(MANPAGE).pod
	pod2man -n=clipped -c=clipped -s=1 -r=$(VERSION) $< $(MANPAGE)

install:
	mkdir -p $(DESTDIR)$(BINPREFIX)
	cp -p clipped $(DESTDIR)$(BINPREFIX)
	cp -p clipsync $(DESTDIR)$(BINPREFIX)
	mkdir -p $(DESTDIR)$(LIBPREFIX)/systemd/user
	cp -p systemd/clipsync.service $(DESTDIR)$(LIBPREFIX)/systemd/user
	mkdir -p $(DESTDIR)$(MANPREFIX)/man1
	cp -p $(MANPAGE) $(DESTDIR)$(MANPREFIX)/man1

uninstall:
	rm -f $(DESTDIR)$(BINPREFIX)/clipped
	rm -f $(DESTDIR)$(BINPREFIX)/clipsync
	rm -f $(DESTDIR)$(LIBPREFIX)/systemd/user/clipsync.service
	rm -f $(DESTDIR)$(MANPREFIX)/man1/$(MANPAGE)

clean:
	rm -f clipped $(OBJ) $(MANPAGE)

.PHONY: all install uninstall clean
