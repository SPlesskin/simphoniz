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

function(simphoniz_copy_external_shared_libraries shared_libraries)
    if(WIN32)
        foreach(target ${ARGN})
            # Third-party libraries should be used as imported targets.
            get_target_property(location ${target} IMPORTED_LOCATION_RELEASE)

            # Copy DLL near to the executable(s)
            file(COPY ${location} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

            list(APPEND ${shared_libraries} ${location})
        endforeach()
    endif()

    set(${shared_libraries} ${${shared_libraries}} PARENT_SCOPE)
endfunction()
