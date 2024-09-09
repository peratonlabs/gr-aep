find_package(PkgConfig)

PKG_CHECK_MODULES(PC_GR_AEP gnuradio-aep)

FIND_PATH(
    GR_AEP_INCLUDE_DIRS
    NAMES gnuradio/aep/api.h
    HINTS $ENV{AEP_DIR}/include
        ${PC_AEP_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GR_AEP_LIBRARIES
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

include("${CMAKE_CURRENT_LIST_DIR}/gnuradio-aepTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GR_AEP DEFAULT_MSG GR_AEP_LIBRARIES GR_AEP_INCLUDE_DIRS)
MARK_AS_ADVANCED(GR_AEP_LIBRARIES GR_AEP_INCLUDE_DIRS)
