TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

HEADERS += \
    ../chocolate-doom-2.3.0/src/doom/am_map.h \
    ../chocolate-doom-2.3.0/src/doom/d_englsh.h \
    ../chocolate-doom-2.3.0/src/doom/d_items.h \
    ../chocolate-doom-2.3.0/src/doom/d_main.h \
    ../chocolate-doom-2.3.0/src/doom/d_player.h \
    ../chocolate-doom-2.3.0/src/doom/d_textur.h \
    ../chocolate-doom-2.3.0/src/doom/d_think.h \
    ../chocolate-doom-2.3.0/src/doom/deh_misc.h \
    ../chocolate-doom-2.3.0/src/doom/doomdata.h \
    ../chocolate-doom-2.3.0/src/doom/doomdef.h \
    ../chocolate-doom-2.3.0/src/doom/doomstat.h \
    ../chocolate-doom-2.3.0/src/doom/dstrings.h \
    ../chocolate-doom-2.3.0/src/doom/f_finale.h \
    ../chocolate-doom-2.3.0/src/doom/f_wipe.h \
    ../chocolate-doom-2.3.0/src/doom/g_game.h \
    ../chocolate-doom-2.3.0/src/doom/hu_lib.h \
    ../chocolate-doom-2.3.0/src/doom/hu_stuff.h \
    ../chocolate-doom-2.3.0/src/doom/info.h \
    ../chocolate-doom-2.3.0/src/doom/m_menu.h \
    ../chocolate-doom-2.3.0/src/doom/m_random.h \
    ../chocolate-doom-2.3.0/src/doom/p_inter.h \
    ../chocolate-doom-2.3.0/src/doom/p_local.h \
    ../chocolate-doom-2.3.0/src/doom/p_mobj.h \
    ../chocolate-doom-2.3.0/src/doom/p_pspr.h \
    ../chocolate-doom-2.3.0/src/doom/p_saveg.h \
    ../chocolate-doom-2.3.0/src/doom/p_setup.h \
    ../chocolate-doom-2.3.0/src/doom/p_spec.h \
    ../chocolate-doom-2.3.0/src/doom/p_tick.h \
    ../chocolate-doom-2.3.0/src/doom/r_bsp.h \
    ../chocolate-doom-2.3.0/src/doom/r_data.h \
    ../chocolate-doom-2.3.0/src/doom/r_defs.h \
    ../chocolate-doom-2.3.0/src/doom/r_draw.h \
    ../chocolate-doom-2.3.0/src/doom/r_local.h \
    ../chocolate-doom-2.3.0/src/doom/r_main.h \
    ../chocolate-doom-2.3.0/src/doom/r_plane.h \
    ../chocolate-doom-2.3.0/src/doom/r_segs.h \
    ../chocolate-doom-2.3.0/src/doom/r_sky.h \
    ../chocolate-doom-2.3.0/src/doom/r_state.h \
    ../chocolate-doom-2.3.0/src/doom/r_things.h \
    ../chocolate-doom-2.3.0/src/doom/s_sound.h \
    ../chocolate-doom-2.3.0/src/doom/sounds.h \
    ../chocolate-doom-2.3.0/src/doom/st_lib.h \
    ../chocolate-doom-2.3.0/src/doom/st_stuff.h \
    ../chocolate-doom-2.3.0/src/doom/statdump.h \
    ../chocolate-doom-2.3.0/src/doom/wi_stuff.h

INCLUDEPATH += $$PWD/../chocolate-doom-2.3.0/src/doom
INCLUDEPATH += $$PWD/../chocolate-doom-2.3.0/src

#INCLUDEPATH += $$PWD/../src $$PWD/../textscreen $$PWD/../ $$PWD/../opl $$PWD/../pcsound
