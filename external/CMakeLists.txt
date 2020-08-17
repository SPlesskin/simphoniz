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

cmake_minimum_required(VERSION 3.7)
project(external)

include(ExternalProject)

if(NOT EXTERNAL_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(EXTERNAL_BUILD_TYPE Release CACHE STRING "Choose the type of build.")
    # Set the possible values of build type for the CMake GUI
    set_property(CACHE EXTERNAL_BUILD_TYPE PROPERTY STRINGS Debug Release MinSizeRel RelWithDebInfo)
endif()

set(EXTERNAL_BUILD_EXAMPLES OFF)
set(EXTERNAL_BUILD_SHARED OFF)
set(EXTERNAL_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/external")
set(EXTERNAL_BUILD_TESTS OFF)

include(spdlog/spdlog_ep.cmake)
include(exiv2/exiv2_ep.cmake)
