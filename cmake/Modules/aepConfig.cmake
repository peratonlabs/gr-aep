INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_AEP aep)

FIND_PATH(
    AEP_INCLUDE_DIRS
    NAMES aep/api.h
    HINTS $ENV{AEP_DIR}/include
        ${PC_AEP_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    AEP_LIBRARIES
    NAMES gnuradio-aep
    HINTS $ENV{AEP_DIR}/lib
        ${PC_AEP_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(AEP DEFAULT_MSG AEP_LIBRARIES AEP_INCLUDE_DIRS)
MARK_AS_ADVANCED(AEP_LIBRARIES AEP_INCLUDE_DIRS)

