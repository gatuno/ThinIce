# Automake file for Thin Ice

gamedatadir = $(pkgdatadir)/data

bin_PROGRAMS = thin-ice
thin_ice_SOURCES = thinice.c cp-button.c draw-text.c cp-button.h draw-text.h gettext.h path.c path.h \
	mapa1.h \
	mapa2.h \
	mapa3.h \
	mapa4.h \
	mapa5.h \
	mapa6.h \
	mapa7.h \
	mapa8.h \
	mapa9.h \
	mapa10.h \
	mapa11.h \
	mapa12.h \
	mapa13.h \
	mapa14.h \
	mapa15.h \
	mapa16.h \
	mapa17.h \
	mapa18.h \
	mapa19.h

EXTRA_DIST=thinice.rc

if MINGW32
thinice_ico.o: thinice.rc ../data/thinice.ico
	$(WINDRES) $(srcdir)/thinice.rc -O coff -o thinice_ico.o

mingw_ldadd = thinice_ico.o

else # NOT MINGW
mingw_ldadd =
endif

thin_ice_CPPFLAGS = -DGAMEDATA_DIR=\"$(gamedatadir)/\" -DLOCALEDIR=\"$(localedir)\" $(AM_CPPFLAGS)
thin_ice_CFLAGS = $(SDL_CFLAGS) $(SDL_image_CFLAGS) $(SDL_mixer_CFLAGS) $(SDL_ttf_CFLAGS) $(CPSTAMP_CFLAGS) $(AM_CFLAGS)
if MACOSX
# En MAC OS X, hay que ligar/compilar contra los frameworks
thin_ice_LDADD = $(SDL_LIBS)
else
thin_ice_LDADD = $(SDL_LIBS) $(SDL_image_LIBS) $(SDL_mixer_LIBS) $(SDL_ttf_LIBS) $(CPSTAMP_LIBS) $(mingw_ldadd)
endif
LDADD = $(LIBINTL)

#------------------ Packaging rules for Mac OSX ------------------------

bundle_root = $(top_builddir)/etc/macfiles
bundle_name = $(bundle_root)/ThinIce.app
# Special target to copy all needed game files to ThinIce.app/Contents/Resources.
# For Mac OS X bundle.
.PHONY: bundle
bundle:
	-rm -rf $(bundle_root)
	mkdir -p $(bundle_name)/Contents/MacOS
	mkdir -p $(bundle_name)/Contents/Resources/data/
	echo "APPL????" > $(bundle_name)/Contents/PkgInfo
	cp $(top_builddir)/etc/Info.plist $(bundle_name)/Contents/
	cp $(top_builddir)/etc/thinice.icns $(bundle_name)/Contents/Resources/
	mkdir -p $(bundle_name)/Contents/Resources/data/images
	cp -R $(top_builddir)/data/images/* $(bundle_name)/Contents/Resources/data/images
	mkdir -p $(bundle_name)/Contents/Resources/data/music
	cp $(top_builddir)/data/music/* $(bundle_name)/Contents/Resources/data/music
	mkdir -p $(bundle_name)/Contents/Resources/data/sounds
	cp $(top_builddir)/data/sounds/* $(bundle_name)/Contents/Resources/data/sounds
	cp $(top_builddir)/data/*.ttf $(bundle_name)/Contents/Resources/data
	for cat in $(ALL_LINGUAS); do \
	  dir=$(bundle_name)/Contents/Resources/locale/$$cat/LC_MESSAGES; \
	  mkdir -p $$dir; \
	  echo "installing $$cat as $$dir/thin-ice.mo"; \
	  cp $(top_builddir)/po/$$cat.gmo $$dir/thin-ice.mo; \
	done

# Special target to copy the binary to ThinIce.app/Contents/MacOS.
.PHONY: bundle-fw
bundle-fw: bundle
	cp thin-ice $(bundle_name)/Contents/MacOS/thin-ice
	mkdir  $(bundle_name)/Contents/Frameworks
	for i in SDL SDL_mixer SDL_image SDL_ttf CPStamp; do \
	  cp -a /Library/Frameworks/$${i}.framework $(bundle_name)/Contents/Frameworks/; \
	done
	strip $(bundle_name)/Contents/MacOS/thin-ice

# Special target to make a disk image of the bundled app
.PHONY: bundle-dmg
bundle-dmg: bundle-fw
	ln -s /Applications $(bundle_root)/Applications
	hdiutil create  -ov -srcfolder $(bundle_root) -volname ThinIce -imagekey zlib-level=6 $(top_builddir)/etc/thinice.dmg

