/* Simphoniz - A Simple Photo Organizer
 * Copyright (C) 2020  Erwan Grâce <erwan.grace@outlook.fr>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * @file ProgressBar.cpp
 * @author Erwan
 * @date 02/01/2020
 */

#include <iostream>

#include <simphoniz/io/console/ProgressBar.h>

namespace simphoniz {

namespace {

const auto COMPLETION_CHAR = '=';
const auto COMPLETION_CHAR_WIDTH = 5; // 5%

} // namespace

ProgressBar::ProgressBar(int totalPhotoCount)
    : m_TotalPhotoCount{totalPhotoCount}, m_SortedPhotoCount{0}
{
}

void ProgressBar::update()
{
    ++m_SortedPhotoCount;

    const auto percentage =
        static_cast<std::size_t>((100 * m_SortedPhotoCount) / m_TotalPhotoCount);

    // The output buffer is flushed so that its content is displayed immediately.
    std::cout << "\r[" << std::string(percentage / COMPLETION_CHAR_WIDTH, COMPLETION_CHAR)
              << std::string(100 / COMPLETION_CHAR_WIDTH - percentage / COMPLETION_CHAR_WIDTH, ' ')
              << "] " << m_SortedPhotoCount << '/' << m_TotalPhotoCount << ' ' << percentage << '%'
              << std::flush;

    if (percentage == 100) {
        std::cout << std::endl;
    }
}

} // namespace simphoniz
