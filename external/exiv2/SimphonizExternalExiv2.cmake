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

set(SIMPHONIZ_EXTERNAL_EXIV2_PREFIX exiv2)
set(SIMPHONIZ_EXTERNAL_EXIV2_URL "${CMAKE_SOURCE_DIR}/exiv2/exiv2-0.27.2-Source.tar.gz")
set(SIMPHONIZ_EXTERNAL_EXIV2_URL_MD5 8c39c39dc8141bb158e8e9d663bcbf21)

if(MSVC)
    # Note: the /EHsc option resolves the C4530 warning.
    set(SIMPHONIZ_EXTERNAL_EXIV2_COMPILER_FLAGS "/DSUPPRESS_WARNINGS /DWIN32 /EHsc")
else()
    set(SIMPHONIZ_EXTERNAL_EXIV2_COMPILER_FLAGS "-DSUPPRESS_WARNINGS")
endif()

ExternalProject_Add(${SIMPHONIZ_EXTERNAL_EXIV2_PREFIX}
    PREFIX ${SIMPHONIZ_EXTERNAL_EXIV2_PREFIX}
    #--Download step--------------
    URL ${SIMPHONIZ_EXTERNAL_EXIV2_URL}
    URL_MD5 ${SIMPHONIZ_EXTERNAL_EXIV2_URL_MD5}
    #--Configure step-------------
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${SIMPHONIZ_EXTERNAL_BUILD_TYPE}
               -DCMAKE_INSTALL_PREFIX=${SIMPHONIZ_EXTERNAL_INSTALL_PREFIX}
               -DBUILD_SHARED_LIBS=${SIMPHONIZ_EXTERNAL_BUILD_SHARED}
               -DEXIV2_ENABLE_XMP=OFF
               -DEXIV2_ENABLE_PNG=OFF
               -DEXIV2_BUILD_SAMPLES=${SIMPHONIZ_EXTERNAL_BUILD_EXAMPLES}
               -DCMAKE_CXX_FLAGS=${SIMPHONIZ_EXTERNAL_EXIV2_COMPILER_FLAGS}
    #--Output logging-------------
    LOG_DOWNLOAD 1
    LOG_CONFIGURE 0
    LOG_BUILD 0
    LOG_INSTALL 1)
