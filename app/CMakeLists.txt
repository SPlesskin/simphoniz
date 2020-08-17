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

set(SIMPHONIZ_APP ${SIMPHONIZ_PROJECT_NAME_L})

file(GLOB_RECURSE SIMPHONIZ_APP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE SIMPHONIZ_APP_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

add_executable(${SIMPHONIZ_APP} ${SIMPHONIZ_APP_SOURCES} ${SIMPHONIZ_APP_HEADERS})

# Since CMake 3.14, Qt5Core_VERSION_MAJOR/MINOR variables must be set to run Qt moc/rcc/uic. These
# are usually set by find_package(Qt5...) calls.
find_package(Qt5 REQUIRED COMPONENTS Core)

target_link_libraries(${SIMPHONIZ_APP} PRIVATE common ${SIMPHONIZ_LIB})

install(TARGETS ${SIMPHONIZ_APP} DESTINATION ${SIMPHONIZ_INSTALL_BIN_DIR})

if(WIN32)
    if(MINGW)
        get_filename_component(mingw_bin_dir ${CMAKE_CXX_COMPILER} DIRECTORY)
        list(APPEND CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS "${mingw_bin_dir}/libgcc_s_seh-1.dll")
        list(APPEND CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS "${mingw_bin_dir}/libwinpthread-1.dll")
        list(APPEND CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS "${mingw_bin_dir}/libstdc++-6.dll")
    endif()

    # Install the Qt-related dependencies (libraries, plugins...) as well as the compiler runtime
    # libraries near to the executable
    windeployqt(${SIMPHONIZ_APP} ${SIMPHONIZ_INSTALL_BIN_DIR})
endif()

# Store the executable name in a global variable
set(SIMPHONIZ_EXE_NAME ${SIMPHONIZ_APP}${CMAKE_EXECUTABLE_SUFFIX} PARENT_SCOPE)
