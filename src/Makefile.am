# Automake file for Thin Ice

gamedatadir = $(pkgdatadir)/data

bin_PROGRAMS = thin-ice
thin_ice_SOURCES = thinice.c


thin_ice_CPPFLAGS = -DGAMEDATA_DIR=\"$(gamedatadir)/\" -DLOCALEDIR=\"$(localedir)\" $(AM_CPPFLAGS)
thin_ice_CFLAGS = $(SDL_CFLAGS) $(SDL_image_CFLAGS) $(AM_CFLAGS)
thin_ice_LDADD = $(SDL_LIBS) $(SDL_image_LIBS)

