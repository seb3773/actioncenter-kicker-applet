tde_setup_architecture_flags()

include(TestBigEndian)
test_big_endian(WORDS_BIGENDIAN)

tde_setup_largefiles()

find_package(TQt)
find_package(TDE)

if (WITH_GCC_VISIBILITY)
  tde_setup_gcc_visibility()
endif()