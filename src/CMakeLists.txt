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

set(SIMPHONIZ_LIB ${SIMPHONIZ_PROJECT_NAME_L}-api)

# Pass application name and version to the source code
set(application_cpp_in "${SIMPHONIZ_RESOURCE_DIR}/cpp/Application.cpp.in")
set(application_cpp "${CMAKE_CURRENT_SOURCE_DIR}/Application.cpp")
configure_file(${application_cpp_in} ${application_cpp} @ONLY)

file(GLOB_RECURSE SIMPHONIZ_LIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

set(SIMPHONIZ_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/include")

file(GLOB_RECURSE SIMPHONIZ_LIB_HEADERS ${SIMPHONIZ_INCLUDE_DIRS}/*.h)

# Although ignored, the headers are listed below so that they show up in IDEs.
add_library(${SIMPHONIZ_LIB} STATIC ${SIMPHONIZ_LIB_SOURCES} ${SIMPHONIZ_LIB_HEADERS})

# https://foonathan.net/2018/10/cmake-warnings
target_include_directories(${SIMPHONIZ_LIB}
                           PRIVATE ${SIMPHONIZ_INCLUDE_DIRS}
                           SYSTEM INTERFACE ${SIMPHONIZ_INCLUDE_DIRS})

find_package(Qt5 REQUIRED COMPONENTS Core)
find_package(Genepy REQUIRED CONFIG)
find_package(exiv2lib REQUIRED CONFIG NAMES exiv2)

if(UNIX)
    # On Linux systems, the iconv library must be linked to when Exiv2 is compiled statically.
    find_package(Iconv REQUIRED)

    target_link_libraries(${SIMPHONIZ_LIB}
                          PUBLIC Qt5::Core
                          PRIVATE common genepy::genepy Iconv::Iconv exiv2lib)
else()
    target_link_libraries(${SIMPHONIZ_LIB}
                          PUBLIC Qt5::Core
                          PRIVATE common genepy::genepy exiv2lib)
endif()

set(SIMPHONIZ_LIB ${SIMPHONIZ_LIB} PARENT_SCOPE)
