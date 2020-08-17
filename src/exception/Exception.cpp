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
 * @file Exception.cpp
 * @author Erwan
 * @date 23/11/2019
 */

#include <simphoniz/exception/Exception.h>

namespace simphoniz {

namespace {

const auto MESSAGE_PREFIX = QStringLiteral("Exception ");

} // namespace

Exception::Exception(const char* file, int line, const QString& cause)
    : m_Message{MESSAGE_PREFIX + file + ':' + QString::number(line) + ": " + cause},
      m_MessageData{m_Message.toLocal8Bit()}
{
}

const char* Exception::what() const noexcept { return m_MessageData.constData(); }

} // namespace simphoniz
