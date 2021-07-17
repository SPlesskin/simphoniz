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

# List the source files
# =====================
file(GLOB_RECURSE SIMPHONIZ_APPLICATION_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE SIMPHONIZ_APPLICATION_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

# Build the application
# =====================
set(SIMPHONIZ_APPLICATION ${SIMPHONIZ_PROJECT_NAME_L})

add_executable(${SIMPHONIZ_APPLICATION} ${SIMPHONIZ_APPLICATION_SOURCES} ${SIMPHONIZ_APPLICATION_HEADERS})

# Store the executable name in a global variable
set(SIMPHONIZ_EXECUTABLE_NAME ${SIMPHONIZ_APPLICATION}${CMAKE_EXECUTABLE_SUFFIX} PARENT_SCOPE)

# Since CMake 3.14, Qt5Core_VERSION_MAJOR/MINOR variables must be set to run Qt moc/rcc/uic. These
# are usually set by find_package(Qt5...) calls.
find_package(Qt5 REQUIRED COMPONENTS Core)

target_link_libraries(${SIMPHONIZ_APPLICATION} PRIVATE common ${SIMPHONIZ_LIBRARY})

# Install application
# ===================
install(TARGETS ${SIMPHONIZ_APPLICATION} DESTINATION ${SIMPHONIZ_RUNTIME_INSTALL_DIR})

if(WIN32)
    if(MINGW)
        get_filename_component(SIMPHONIZ_MINGW_BIN_DIR ${CMAKE_CXX_COMPILER} DIRECTORY)
        list(APPEND CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS "${SIMPHONIZ_MINGW_BIN_DIR}/libgcc_s_seh-1.dll")
        list(APPEND CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS "${SIMPHONIZ_MINGW_BIN_DIR}/libwinpthread-1.dll")
        list(APPEND CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS "${SIMPHONIZ_MINGW_BIN_DIR}/libstdc++-6.dll")
    endif()

    # Install the Qt-related dependencies (libraries, plugins...) as well as the compiler runtime
    # libraries near to the executable
    windeployqt(${SIMPHONIZ_APPLICATION} ${SIMPHONIZ_RUNTIME_INSTALL_DIR})

    install(FILES ${SIMPHONIZ_EXTERNAL_SHARED_LIBRARIES} DESTINATION ${SIMPHONIZ_RUNTIME_INSTALL_DIR})
endif()
