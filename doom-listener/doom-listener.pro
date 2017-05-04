TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

INCLUDEPATH += $$PWD/../chocolate-doom/src/doom
INCLUDEPATH += $$PWD/../chocolate-doom/src

#INCLUDEPATH += $$PWD/../src $$PWD/../textscreen $$PWD/../ $$PWD/../opl $$PWD/../pcsound

HEADERS += \
    ../chocolate-doom/src/aes_prng.h \
    ../chocolate-doom/src/d_event.h \
    ../chocolate-doom/src/d_iwad.h \
    ../chocolate-doom/src/d_loop.h \
    ../chocolate-doom/src/d_mode.h \
    ../chocolate-doom/src/d_ticcmd.h \
    ../chocolate-doom/src/deh_defs.h \
    ../chocolate-doom/src/deh_io.h \
    ../chocolate-doom/src/deh_main.h \
    ../chocolate-doom/src/deh_mapping.h \
    ../chocolate-doom/src/deh_str.h \
    ../chocolate-doom/src/doomfeatures.h \
    ../chocolate-doom/src/doomkeys.h \
    ../chocolate-doom/src/doomtype.h \
    ../chocolate-doom/src/gusconf.h \
    ../chocolate-doom/src/i_cdmus.h \
    ../chocolate-doom/src/i_endoom.h \
    ../chocolate-doom/src/i_joystick.h \
    ../chocolate-doom/src/i_scale.h \
    ../chocolate-doom/src/i_sound.h \
    ../chocolate-doom/src/i_swap.h \
    ../chocolate-doom/src/i_system.h \
    ../chocolate-doom/src/i_timer.h \
    ../chocolate-doom/src/i_video.h \
    ../chocolate-doom/src/i_videohr.h \
    ../chocolate-doom/src/m_argv.h \
    ../chocolate-doom/src/m_bbox.h \
    ../chocolate-doom/src/m_cheat.h \
    ../chocolate-doom/src/m_config.h \
    ../chocolate-doom/src/m_controls.h \
    ../chocolate-doom/src/m_fixed.h \
    ../chocolate-doom/src/m_misc.h \
    ../chocolate-doom/src/memio.h \
    ../chocolate-doom/src/midifile.h \
    ../chocolate-doom/src/mus2mid.h \
    ../chocolate-doom/src/net_client.h \
    ../chocolate-doom/src/net_common.h \
    ../chocolate-doom/src/net_dedicated.h \
    ../chocolate-doom/src/net_defs.h \
    ../chocolate-doom/src/net_gui.h \
    ../chocolate-doom/src/net_io.h \
    ../chocolate-doom/src/net_loop.h \
    ../chocolate-doom/src/net_packet.h \
    ../chocolate-doom/src/net_query.h \
    ../chocolate-doom/src/net_sdl.h \
    ../chocolate-doom/src/net_server.h \
    ../chocolate-doom/src/net_structrw.h \
    ../chocolate-doom/src/sha1.h \
    ../chocolate-doom/src/tables.h \
    ../chocolate-doom/src/v_diskicon.h \
    ../chocolate-doom/src/v_patch.h \
    ../chocolate-doom/src/v_video.h \
    ../chocolate-doom/src/w_checksum.h \
    ../chocolate-doom/src/w_file.h \
    ../chocolate-doom/src/w_main.h \
    ../chocolate-doom/src/w_merge.h \
    ../chocolate-doom/src/w_wad.h \
    ../chocolate-doom/src/z_zone.h \
    ../chocolate-doom/src/doom/am_map.h \
    ../chocolate-doom/src/doom/d_englsh.h \
    ../chocolate-doom/src/doom/d_items.h \
    ../chocolate-doom/src/doom/d_main.h \
    ../chocolate-doom/src/doom/d_player.h \
    ../chocolate-doom/src/doom/d_textur.h \
    ../chocolate-doom/src/doom/d_think.h \
    ../chocolate-doom/src/doom/deh_misc.h \
    ../chocolate-doom/src/doom/doomdata.h \
    ../chocolate-doom/src/doom/doomdef.h \
    ../chocolate-doom/src/doom/doomstat.h \
    ../chocolate-doom/src/doom/dstrings.h \
    ../chocolate-doom/src/doom/f_finale.h \
    ../chocolate-doom/src/doom/f_wipe.h \
    ../chocolate-doom/src/doom/g_game.h \
    ../chocolate-doom/src/doom/hu_lib.h \
    ../chocolate-doom/src/doom/hu_stuff.h \
    ../chocolate-doom/src/doom/info.h \
    ../chocolate-doom/src/doom/m_menu.h \
    ../chocolate-doom/src/doom/m_random.h \
    ../chocolate-doom/src/doom/p_inter.h \
    ../chocolate-doom/src/doom/p_local.h \
    ../chocolate-doom/src/doom/p_mobj.h \
    ../chocolate-doom/src/doom/p_pspr.h \
    ../chocolate-doom/src/doom/p_saveg.h \
    ../chocolate-doom/src/doom/p_setup.h \
    ../chocolate-doom/src/doom/p_spec.h \
    ../chocolate-doom/src/doom/p_tick.h \
    ../chocolate-doom/src/doom/r_bsp.h \
    ../chocolate-doom/src/doom/r_data.h \
    ../chocolate-doom/src/doom/r_defs.h \
    ../chocolate-doom/src/doom/r_draw.h \
    ../chocolate-doom/src/doom/r_local.h \
    ../chocolate-doom/src/doom/r_main.h \
    ../chocolate-doom/src/doom/r_plane.h \
    ../chocolate-doom/src/doom/r_segs.h \
    ../chocolate-doom/src/doom/r_sky.h \
    ../chocolate-doom/src/doom/r_state.h \
    ../chocolate-doom/src/doom/r_things.h \
    ../chocolate-doom/src/doom/s_sound.h \
    ../chocolate-doom/src/doom/sounds.h \
    ../chocolate-doom/src/doom/st_lib.h \
    ../chocolate-doom/src/doom/st_stuff.h \
    ../chocolate-doom/src/doom/statdump.h \
    ../chocolate-doom/src/doom/wi_stuff.h
