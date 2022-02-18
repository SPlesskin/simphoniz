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

function(simphoniz_find_qt_include_dir result)
    find_package(Qt5 REQUIRED COMPONENTS Core)
    list(GET Qt5Core_INCLUDE_DIRS 0 ${result})

    # Remove unnecessary path separators (e.g., the trailing one)
    file(TO_CMAKE_PATH "${${result}}" ${result})

    set(${result} ${${result}} PARENT_SCOPE)
endfunction()

function(simphoniz_copy_external_shared_libraries external_shared_libraries)
    if(WIN32)
        foreach(_target ${ARGN})
            # Third-party libraries should be used as imported targets.
            get_target_property(_location ${_target} IMPORTED_LOCATION_RELEASE)

            # Copy DLL near to the executable(s)
            file(COPY ${_location} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

            list(APPEND ${external_shared_libraries} ${_location})
        endforeach()
    endif()

    set(${external_shared_libraries} ${${external_shared_libraries}} PARENT_SCOPE)
endfunction()
