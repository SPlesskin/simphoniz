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

# Set compiler and target architecture (for further purposes)
# ===========================================================
if(WIN32)
    if(MINGW)
        set(SIMPHONIZ_COMPILER MinGW)
    else()
        set(SIMPHONIZ_COMPILER MSVC)
    endif()
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(SIMPHONIZ_TARGET_ARCHITECTURE x64)
else()
    set(SIMPHONIZ_TARGET_ARCHITECTURE x86)
endif()

# Enable C++14 and prevent CMake from falling back to a previous standard if the compiler doesn't
# support the specified one
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Disable compiler features which extend the C++ standard for maximum portability
set(CMAKE_CXX_EXTENSIONS OFF)

# Set warning flags
# =================
set(SIMPHONIZ_COMPILER_CONFIGURATION ${SIMPHONIZ_PROJECT_NAME_L}-cc)

add_library(${SIMPHONIZ_COMPILER_CONFIGURATION} INTERFACE)

if(MSVC)
    simphoniz_find_qt_include_dir(SIMPHONIZ_QT_INCLUDE_DIR)

    # The /external:* switch group disables warnings for third-party header files
    # (https://devblogs.microsoft.com/cppblog/broken-warnings-theory/).
    target_compile_options(${SIMPHONIZ_COMPILER_CONFIGURATION} INTERFACE /WX /W4
                                                                         /experimental:external /external:I ${SIMPHONIZ_QT_INCLUDE_DIR} /external:W0)
else()
    target_compile_options(${SIMPHONIZ_COMPILER_CONFIGURATION} INTERFACE -Werror -pedantic-errors
                                                                         -Wall -Wextra -Wconversion
                                                                         -Wsign-conversion)
endif()
