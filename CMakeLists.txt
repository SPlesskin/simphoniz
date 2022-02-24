# Simphoniz - A Simple Photo Organizer
# Copyright (C) 2020-2022  Erwan Grâce <erwan.grace@outlook.fr>
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

if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.15)
    cmake_policy(SET CMP0092 NEW) # Silence MSVC warning D9025
endif()

project(Simphoniz VERSION 1.0.0 LANGUAGES CXX)

# Set a default build type if none was specified
include(cmake/SimphonizBuildType.cmake)

# Define global parameters
include(cmake/SimphonizParams.cmake)

# Utility CMake functions
include(cmake/SimphonizUtils.cmake)

# Configure external tools
include(cmake/SimphonizExternalTools.cmake)

# Set compiler flags
include(cmake/SimphonizCompiler.cmake)

include(CTest)

add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(test)

# Configure the package generators
include(cmake/SimphonizPackage.cmake)
