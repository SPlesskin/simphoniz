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

# Enable C++14 and prevent CMake from falling back to a previous standard if the compiler doesn't
# support the specified one
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Disable compiler features which extend the C++ standard for maximum portability
set(CMAKE_CXX_EXTENSIONS OFF)

# Set warning flags
add_library(common INTERFACE)
if(MSVC)
    # Note: Qt generates a lot of C4127 warnings; consequently, they are suppressed.
    target_compile_options(common INTERFACE /WX /W4 /wd4127)
else()
    target_compile_options(common INTERFACE -Werror -pedantic-errors -Wall -Wextra -Wconversion
                                            -Wsign-conversion)
endif()
