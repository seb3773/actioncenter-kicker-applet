install(
  FILES
    action1_on.png action1.png
    action2_on.png action2.png
    action3.png
    action4.png
    action5.png
    actioncenter.png
    proj1.png
    proj2.png
    proj3.png
    proj4.png
    proj.png
  DESTINATION ${DATA_INSTALL_DIR}/actioncenter_applet
)

install(
  FILES actions.sh proj.sh
  PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
              GROUP_EXECUTE GROUP_READ
              WORLD_EXECUTE WORLD_READ
  DESTINATION ${DATA_INSTALL_DIR}/actioncenter_applet
)