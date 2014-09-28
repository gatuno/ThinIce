# Automake file for Thin Ice

gamedatadir = $(pkgdatadir)/data

bin_PROGRAMS = thin-ice
thin_ice_SOURCES = thinice.c cp-button.c draw-text.c
EXTRA_DIST = cp-button.h \
	draw-text.h \
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

thin_ice_CPPFLAGS = -DGAMEDATA_DIR=\"$(gamedatadir)/\" -DLOCALEDIR=\"$(localedir)\" -I$(srcdir)/../libcpstamp/src $(AM_CPPFLAGS)
thin_ice_CFLAGS = $(SDL_CFLAGS) $(SDL_image_CFLAGS) $(SDL_mixer_CFLAGS) $(SDL_ttf_LIBS) $(AM_CFLAGS)
thin_ice_LDADD = $(SDL_LIBS) $(SDL_image_LIBS) $(SDL_mixer_LIBS) $(SDL_ttf_LIBS) $(builddir)/../libcpstamp/src/libcpstamp.la

