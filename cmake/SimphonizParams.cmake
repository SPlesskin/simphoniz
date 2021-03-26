# Simphoniz - A Simple Photo Organizer
# Copyright (C) 2020  Erwan Grâce <erwan.grace@outlook.fr>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

include(CheckCXXSourceCompiles)
include(GNUInstallDirs)

string(TOLOWER ${PROJECT_NAME} SIMPHONIZ_PROJECT_NAME_L)

set(SIMPHONIZ_RESOURCE_DIR "${CMAKE_SOURCE_DIR}/resources")

# Define the search path for CMake modules (but not only)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
list(APPEND CMAKE_MODULE_PATH ${SIMPHONIZ_RESOURCE_DIR}/nsis)

# Locate the external dependencies
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/external/build/external")

# Set the locations of the compiled artifacts
# ===========================================
set(SIMPHONIZ_OUTPUT_DIR "${CMAKE_BINARY_DIR}/dist/${CMAKE_BUILD_TYPE}")

if(UNIX)
    set(SIMPHONIZ_LIBRARY_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR}/${SIMPHONIZ_PROJECT_NAME_L})
    set(SIMPHONIZ_RUNTIME_INSTALL_DIR ${CMAKE_INSTALL_BINDIR}/${SIMPHONIZ_PROJECT_NAME_L})
else()
    set(SIMPHONIZ_LIBRARY_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR})
    set(SIMPHONIZ_RUNTIME_INSTALL_DIR ${CMAKE_INSTALL_BINDIR})
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SIMPHONIZ_OUTPUT_DIR}/${SIMPHONIZ_LIBRARY_INSTALL_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SIMPHONIZ_OUTPUT_DIR}/${SIMPHONIZ_RUNTIME_INSTALL_DIR})

# Set the RPATH
# =============
# https://gitlab.kitware.com/cmake/community/wikis/doc/cmake/RPATH-handling
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
# Note: $ORIGIN resolves to the directory containing the executable.
set(CMAKE_INSTALL_RPATH "$ORIGIN;$ORIGIN/../${SIMPHONIZ_LIBRARY_INSTALL_DIR};$ORIGIN/../../${SIMPHONIZ_LIBRARY_INSTALL_DIR}")
