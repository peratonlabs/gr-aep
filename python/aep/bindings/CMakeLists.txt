# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# Check if there is C++ code at all
########################################################################
if(NOT aep_sources)
    message(STATUS "No C++ sources... skipping python bindings")
    return()
endif(NOT aep_sources)

########################################################################
# Check for pygccxml
########################################################################
gr_python_check_module_raw("pygccxml" "import pygccxml" PYGCCXML_FOUND)

include(GrPybind)

########################################################################
# Python Bindings
########################################################################

list(APPEND aep_python_files
    aep_channel_processing_python.cc
    aep_metric_python.cc
    apply_weights_python.cc
    spatial_cov_per_sc_python.cc python_bindings.cc)

gr_pybind_make_oot(aep ../../.. gr::aep "${aep_python_files}")

# copy bindings extension for use in QA test module
add_custom_command(
    TARGET aep_python
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:aep_python>
            ${PROJECT_BINARY_DIR}/test_modules/gnuradio/aep/)

install(
    TARGETS aep_python
    DESTINATION ${GR_PYTHON_DIR}/gnuradio/aep
    COMPONENT pythonapi)
