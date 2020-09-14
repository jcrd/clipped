Name: {{{ git_name name="clipped" }}}
Version: {{{ git_version lead="$(git tag | sed -n 's/^v//p' | sort --version-sort -r | head -n1)" }}}
Release: 1%{?dist}
Summary: X11 primary/clipboard selection monitor

License: MIT
URL: https://github.com/jcrd/clipped
VCS: {{{ git_vcs }}}
Source0: {{{ git_pack }}}

BuildRequires: gcc
BuildRequires: perl

BuildRequires: pkgconfig(x11)
BuildRequires: pkgconfig(xfixes)

Requires: bash
Requires: xsel

%global debug_package %{nil}

%description
clipped monitors the ownership of the primary and clipboard X11 selections. When ownership changes, the name of the selection that changed is printed.
It also provides the clipsync script to synchronize content between the primary and clipboard selections using xclip.

%prep
{{{ git_setup_macro }}}

%build
%make_build PREFIX=/usr

%install
%make_install PREFIX=/usr

%files
%license LICENSE
%doc README.md
%{_bindir}/%{name}
%{_bindir}/clipsync
/usr/lib/systemd/user/clipsync.service
%{_mandir}/man1/%{name}.1.gz

%changelog
{{{ git_changelog }}}
