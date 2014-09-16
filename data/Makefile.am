gamedatadir = $(pkgdatadir)/data

nobase_dist_gamedata_DATA = images/tiles.png \
	images/arcade.png \
	images/title.png \
	images/icon.png \
	images/puffle-on-ice.png \
	images/puffle-explain.png \
	images/moneybag.png \
	images/explain1.png \
	images/explain2.png \
	images/boton-ui-1-down.png \
	images/boton-ui-1-over.png \
	images/boton-ui-1-up.png \
	images/boton-ui-2-down.png \
	images/boton-ui-2-over.png \
	images/boton-ui-2-up.png \
	images/boton-ui-3-down.png \
	images/boton-ui-3-over.png \
	images/boton-ui-3-up.png \
	images/boton-close-down.png \
	images/boton-close-over.png \
	images/boton-close-up.png \
	images/down-1.png \
	images/down-2.png \
	images/down-3.png \
	images/left-1.png \
	images/left-2.png \
	images/left-3.png \
	images/right-1.png \
	images/right-2.png \
	images/right-3.png \
	images/up-1.png \
	images/up-2.png \
	images/up-3.png \
	images/fire1.png \
	images/fire2.png \
	images/fire3.png \
	images/fire4.png \
	images/fire5.png \
	images/fire6.png \
	images/fire7.png \
	images/fire8.png \
	images/fire9.png \
	images/fire10.png \
	images/puffle_black_1.png \
	images/puffle_black_2.png \
	images/puffle_black_3.png \
	images/puffle_black_4.png \
	images/puffle_black_5.png \
	images/puffle_black_6.png \
	images/puffle_black_7.png \
	images/puffle_black_8.png \
	images/puffle_black_9.png \
	images/puffle_black_10.png \
	images/puffle_black_11.png \
	images/puffle_black_12.png \
	images/puffle_black_13.png \
	images/puffle_black_14.png \
	images/puffle_black_15.png \
	images/puffle_black_16.png \
	images/puffle_black_end1_1.png \
	images/puffle_black_end1_2.png \
	images/puffle_black_end1_3.png \
	images/puffle_black_end1_4.png \
	images/puffle_black_end2_1.png \
	images/puffle_black_end2_2.png \
	images/puffle_black_end2_3.png \
	images/puffle_black_end2_4.png \
	images/puffle_black_end3_1.png \
	images/puffle_black_end3_2.png \
	images/puffle_black_end3_3.png \
	images/puffle_black_end3_4.png \
	images/puffle_off1.png \
	images/puffle_off2.png \
	images/puffle_off3.png \
	images/puffle_off4.png \
	images/puffle_off5.png \
	images/puffle_off6.png \
	images/puffle_off7.png \
	images/puffle_off8.png \
	images/puffle_off9.png \
	images/puffle_off10.png \
	images/keys1.png \
	images/keys2.png \
	burbanksb.ttf \
	burbankbgbk.ttf \
	sounds/complete.wav \
	sounds/double.wav \
	sounds/drown.wav \
	sounds/ice.wav \
	sounds/key.wav \
	sounds/money.wav \
	sounds/move.wav \
	sounds/points.wav \
	sounds/start.wav \
	sounds/warp.wav \
	sounds/button-1.wav \
	music/thinice1.ogg \
	music/thinice2.ogg

# Instalar los archivos .desktop e iconos
applicationsdir = $(datadir)/applications
applications_DATA = desktop/thinice.desktop

icons24dir = $(datadir)/icons/hicolor/24x24/apps
icons24_DATA = desktop/24x24/thinice.png

icons32dir = $(datadir)/icons/hicolor/32x32/apps
icons32_DATA = desktop/32x32/thinice.png

icons48dir = $(datadir)/icons/hicolor/48x48/apps
icons48_DATA = desktop/48x48/thinice.png

icons64dir = $(datadir)/icons/hicolor/64x64/apps
icons64_DATA = desktop/64x64/thinice.png

icons128dir = $(datadir)/icons/hicolor/128x128/apps
icons128_DATA = desktop/128x128/thinice.png

icons256dir = $(datadir)/icons/hicolor/256x256/apps
icons256_DATA = desktop/256x256/thinice.png

# touch the toplevel icon directory as required by the icon theme spec
install-data-hook:
	touch $(DESTDIR)$(datadir)/icons/hicolor

EXTRA_DIST = \
	desktop/thinice.desktop	\
	desktop/24x24/thinice.png		\
	desktop/32x32/thinice.png		\
	desktop/48x48/thinice.png		\
	desktop/64x64/thinice.png		\
	desktop/128x128/thinice.png		\
	desktop/256x256/thinice.png
