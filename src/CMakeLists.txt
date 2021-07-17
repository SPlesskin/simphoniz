# Simphoniz - A Simple Photo Organizer
# Copyright (C) 2020, 2021  Erwan Grâce <erwan.grace@outlook.fr>
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

# List the source files
# =====================
set(SIMPHONIZ_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

configure_file(${SIMPHONIZ_RESOURCE_DIR}/cpp/Application.cpp.in "${CMAKE_CURRENT_SOURCE_DIR}/Application.cpp" @ONLY)

file(GLOB_RECURSE SIMPHONIZ_LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE SIMPHONIZ_LIBRARY_HEADERS ${SIMPHONIZ_INCLUDE_DIR}/*.h)

# Build the library
# =================
set(SIMPHONIZ_LIBRARY ${SIMPHONIZ_PROJECT_NAME_L}-api)

# Although ignored, the headers are listed below so that they show up in IDEs.
add_library(${SIMPHONIZ_LIBRARY} STATIC ${SIMPHONIZ_LIBRARY_SOURCES} ${SIMPHONIZ_LIBRARY_HEADERS})

# https://foonathan.net/2018/10/cmake-warnings
target_include_directories(${SIMPHONIZ_LIBRARY}
                           PRIVATE ${SIMPHONIZ_INCLUDE_DIR}
                           SYSTEM INTERFACE ${SIMPHONIZ_INCLUDE_DIR})

find_package(Qt5 REQUIRED COMPONENTS Core)
find_package(Genepy 0.6.0 REQUIRED CONFIG)
find_package(exiv2lib REQUIRED CONFIG NAMES exiv2)

if(UNIX)
    # On Linux systems, the iconv library must be linked to when Exiv2 is compiled statically.
    find_package(Iconv REQUIRED)

    target_link_libraries(${SIMPHONIZ_LIBRARY}
                          PUBLIC Qt5::Core genepy::genepy
                          PRIVATE common Iconv::Iconv exiv2lib)
else()
    target_link_libraries(${SIMPHONIZ_LIBRARY}
                          PUBLIC Qt5::Core genepy::genepy
                          PRIVATE common exiv2lib)

    # Windows has no RPATH mechanism or equivalent, so it only looks for DLLs in the same directory
    # as the executable or in the directories listed in the PATH environment variable.
    simphoniz_copy_external_shared_libraries(SIMPHONIZ_EXTERNAL_SHARED_LIBRARIES genepy::genepy)

    set(SIMPHONIZ_EXTERNAL_SHARED_LIBRARIES ${SIMPHONIZ_EXTERNAL_SHARED_LIBRARIES} PARENT_SCOPE)
endif()

set(SIMPHONIZ_LIBRARY ${SIMPHONIZ_LIBRARY} PARENT_SCOPE)
