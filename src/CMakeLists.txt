include_directories(
    ${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${TDE_INCLUDE_DIR}
    ${TQT_INCLUDE_DIRS}
)

link_directories(
    ${TQT_LIBRARY_DIRS}
)

### actioncenter_applet (plugin) ###############################################
tde_add_kpart(actioncenter_panelapplet AUTOMOC
  SOURCES actioncenter_applet.cpp action_tile.cpp
  LINK tdecore-shared tdeui-shared tdeio-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)

### other data #################################################################
tde_create_translated_desktop(
  SOURCE actioncenter_applet.desktop
  DESTINATION ${DATA_INSTALL_DIR}/kicker/applets
)

tde_install_icons( actioncenter )