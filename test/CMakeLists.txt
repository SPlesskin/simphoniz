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

if(BUILD_TESTING)
    file(GLOB_RECURSE SIMPHONIZ_TEST_SOURCES src/Test*.cpp)
    file(GLOB_RECURSE SIMPHONIZ_TEST_HEADERS src/Test*.h)

    file(GLOB_RECURSE SIMPHONIZ_TEST_COMMON_SOURCES src/*.cpp)
    file(GLOB_RECURSE SIMPHONIZ_TEST_COMMON_HEADERS src/*.h)
    list(REMOVE_ITEM SIMPHONIZ_TEST_COMMON_SOURCES ${SIMPHONIZ_TEST_SOURCES})
    list(REMOVE_ITEM SIMPHONIZ_TEST_COMMON_HEADERS ${SIMPHONIZ_TEST_HEADERS})

    find_package(Qt5 REQUIRED COMPONENTS Test)

    add_definitions(-DTEST_RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/resources")

    foreach(_file ${SIMPHONIZ_TEST_SOURCES})
        get_filename_component(_dir ${_file} DIRECTORY)
        get_filename_component(_name ${_file} NAME_WE)

        # List the source files of the current test
        file(GLOB_RECURSE _sources "${_dir}/${_name}.*")
        list(APPEND _sources ${SIMPHONIZ_TEST_COMMON_SOURCES})
        list(APPEND _sources ${SIMPHONIZ_TEST_COMMON_HEADERS})

        add_executable(${_name} ${_sources})
        target_link_libraries(${_name} PRIVATE common Qt5::Test ${SIMPHONIZ_LIBRARY})

        add_test(NAME ${_name} COMMAND ${_name})
    endforeach()
endif()
