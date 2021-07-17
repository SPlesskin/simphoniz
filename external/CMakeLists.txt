# Simphoniz - A Simple Photo Organizer
# Copyright (C) 2020, 2021  Erwan Grâce <erwan.grace@outlook.fr>
#
# This file is part of Simphoniz.
#
# Simphoniz is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Simphoniz is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Simphoniz.  If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.7)

project(SimphonizExternal)

include(ExternalProject)

if(NOT SIMPHONIZ_EXTERNAL_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(SIMPHONIZ_EXTERNAL_BUILD_TYPE Release CACHE STRING "Choose the type of build.")
    # Set the possible values of build type for the CMake GUI
    set_property(CACHE SIMPHONIZ_EXTERNAL_BUILD_TYPE PROPERTY STRINGS Debug Release MinSizeRel RelWithDebInfo)
endif()

set(SIMPHONIZ_EXTERNAL_BUILD_EXAMPLES OFF)
set(SIMPHONIZ_EXTERNAL_BUILD_SHARED OFF)
set(SIMPHONIZ_EXTERNAL_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/external")
set(SIMPHONIZ_EXTERNAL_BUILD_TESTS OFF)

include(exiv2/SimphonizExternalExiv2.cmake)
