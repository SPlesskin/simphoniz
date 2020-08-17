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
 * @file PhotoCounter.cpp
 * @author Erwan
 * @date 01/01/2020
 */

#include <simphoniz/photo/PhotoDirectory.h>
#include <simphoniz/processing/PhotoCounter.h>

namespace simphoniz {

PhotoCounter::PhotoCounter() : m_Count{0} {}

int PhotoCounter::getCount() const { return m_Count; }

void PhotoCounter::visit(const PhotoDirectory& dir)
{
    for (auto it = std::cbegin(dir.getResources()); it != std::cend(dir.getResources()); ++it) {
        (*it)->accept(*this);
    }
}

void PhotoCounter::visit(const PhotoFile& file)
{
    ++m_Count;

    Q_UNUSED(file)
}

} // namespace simphoniz
