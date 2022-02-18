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

# Set variables common to all CPack generators
# ============================================
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VENDOR "Erwan Grâce")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A simple photo organizer")
set(CPACK_PACKAGE_FILE_NAME ${SIMPHONIZ_PROJECT_NAME_L}-${CPACK_PACKAGE_VERSION})
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY ${PROJECT_NAME})

# Configure the source package generators
# =======================================
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_FILE_NAME}-src")
set(CPACK_SOURCE_GENERATOR "TGZ;ZIP")
set(CPACK_SOURCE_IGNORE_FILES "\\\\.git" "build" "CMakeLists.txt.user")

# Configure the binary package generators
# =======================================
if(UNIX)
    set(CPACK_GENERATOR "DEB")
    set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER ${CPACK_PACKAGE_VENDOR})
    set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
else()
    string(TOLOWER ${CPACK_PACKAGE_FILE_NAME}-${SIMPHONIZ_COMPILER}-${SIMPHONIZ_TARGET_ARCHITECTURE} CPACK_PACKAGE_FILE_NAME)

    option(SIMPHONIZ_USE_NSIS "Use NSIS generator to produce installer" OFF)

    if(SIMPHONIZ_USE_NSIS)
        set(CPACK_GENERATOR "NSIS")

        # Disambiguate the name of the setup file otherwise it can be confused with the executable
        set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_FILE_NAME}-setup")

        # This variable is used within NSIS header file.
        set(CPACK_NSIS_INSTALLED_ICON_NAME "${SIMPHONIZ_PROJECT_NAME_L}.ico")

        set(CPACK_NSIS_HELP_LINK "https://github.com/SPlesskin/simphoniz")
        set(CPACK_NSIS_URL_INFO_ABOUT ${CPACK_NSIS_HELP_LINK})
        set(CPACK_NSIS_CONTACT "erwan.grace@outlook.fr")

        # Generate header file with custom definitions for NSIS
        configure_file(${SIMPHONIZ_RESOURCE_DIR}/nsis/NSIS.definitions.nsh.in
                       "${CMAKE_BINARY_DIR}/resources/nsis/NSIS.definitions.nsh" @ONLY)
    else()
        set(CPACK_GENERATOR "ZIP")
    endif()
endif()

include(CPack)
