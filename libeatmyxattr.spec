Name:           libeatmyxattr
Version:        131
Release:        1%{?dist}
Group:          Development/Tools
License:        GPLv3
Summary:        Library and utilities designed to disable fsync and friends
BuildRoot:      %{_tmppath}/%{name}-%{version}-root
BuildRequires:  autoconf, automake, make, libtool, strace
Source:         https://www.flamingspork.com/projects/libeatmyxattr/%{name}-%{version}.tar.gz
URL:            https://www.flamingspork.com/projects/libeatmyxattr/

%description
This package contains a small LD_PRELOAD library (libeatmyxattr) and a couple 
of helper utilities designed to transparently disable fsync and friends 
(like open(O_SYNC)). This has two side-effects: making software that writes 
data safely to disk a lot quicker and making this software no longer 
crash safe..


%prep

%setup -q

%build
autoreconf --force --install

%configure
%{__make}

%install
rm -fr %{buildroot}

%makeinstall
find %{buildroot} -name "*.la" -print0 | xargs -0 rm -f

%check
%{__make} check

%clean
rm -fr %{buildroot}
#
%files
%defattr(-,root,root)
%attr(755,-,-) %{_bindir}/eatmyxattr
%{_libdir}/*
%{_libexecdir}/*

%doc README.md AUTHORS
#

%post -p /sbin/ldconfig
%postun -p /sbin/ldconfig

%changelog
* Sun Oct 10 2021 Stewart Smith <stewart@flamingspork.com> - 130-1
- version 130, add syncfs() wrapper
* Sat Apr 10 2021 Stewart Smith <stewart@flamingspork.com> - 129-1
- Version 129, as always, bug fix release
* Fri Jul 26 2013 Jaroslav Kortus <jkortus@redhat.com> - 82-1
- Version 82, bug fix release
- spec file changed to meet fedora packaging guidelines
* Fri May 18 2013 Stewart Smith <stewart@flamingspork.com> - 79
- Version 79, bug fix release
* Fri Mar 08 2013 Alexey Bychko <alexey.bychko@percona.com> - 0.1
- Version 0.1, initial package for RPM-based systems


