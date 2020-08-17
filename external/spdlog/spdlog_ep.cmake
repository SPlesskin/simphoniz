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

set(SPDLOG_PREFIX spdlog)
set(SPDLOG_URL "${CMAKE_SOURCE_DIR}/spdlog/spdlog-1.4.2.tar.gz")
set(SPDLOG_URL_MD5 373bbb7ea7557cbe6726705463bcae16)

ExternalProject_Add(${SPDLOG_PREFIX}
    PREFIX ${SPDLOG_PREFIX}
    #--Download step--------------
    URL ${SPDLOG_URL}
    URL_MD5 ${SPDLOG_URL_MD5}
    #--Configure step-------------
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${EXTERNAL_BUILD_TYPE}
               -DSPDLOG_BUILD_EXAMPLE=${EXTERNAL_BUILD_EXAMPLES}
               -DSPDLOG_BUILD_SHARED=${EXTERNAL_BUILD_SHARED}
               -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_PREFIX}
               -DSPDLOG_BUILD_TESTS=${EXTERNAL_BUILD_TESTS}
    #--Output logging-------------
    LOG_DOWNLOAD 1
    LOG_CONFIGURE 0
    LOG_BUILD 0
    LOG_INSTALL 1)
