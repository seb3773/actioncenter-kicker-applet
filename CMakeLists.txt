cmake_minimum_required(VERSION 3.5)

project(actioncenter_kicker_applet)

include(FindPkgConfig)
include(CheckIncludeFiles)
include(CheckLibraryExists)
include(CheckSymbolExists)
include(CheckCXXSourceCompiles)

include(TDEMacros)
tde_set_project_version()

include(TDESetupPaths)
tde_setup_paths()

option(BUILD_ALL           "Build all"            ON)
option(BUILD_DOC           "Build documentation"  ${BUILD_ALL})
option(BUILD_TRANSLATIONS  "Build translations"   ${BUILD_ALL})

include(ConfigureChecks.cmake)
add_definitions(-DHAVE_CONFIG_H)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TQT_CXX_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-undefined")
set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -Wl,--no-undefined")

add_subdirectory(src)
add_subdirectory(assets)

tde_conditional_add_project_docs(BUILD_DOC)
tde_conditional_add_project_translations(BUILD_TRANSLATIONS)

configure_file( config.h.cmake config.h @ONLY )