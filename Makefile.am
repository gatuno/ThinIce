SUBDIRS = po src data etc

ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = build-aux/config.rpath m4/ChangeLog

.PHONY: macapp
macapp:
	cd src && $(MAKE) $(AM_MAKEFLAGS) bundle && $(MAKE) $(AM_MAKEFLAGS) bundle-fw

.PHONY: macdmg
macdmg:
	cd src && $(MAKE) $(AM_MAKEFLAGS) bundle-dmg
