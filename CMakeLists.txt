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

project(Simphoniz VERSION 0.1.0 LANGUAGES CXX)

# Set a default build type if none was specified
include(cmake/build_type.cmake)

# Define global parameters
include(cmake/params.cmake)

# Configure external tools
include(cmake/external_tools.cmake)

# Set compiler flags
include(cmake/compiler.cmake)

include(CTest)

add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(test)

# Configure the package generators
include(cmake/package.cmake)
