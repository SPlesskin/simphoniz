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
 * @file Exception.h
 * @author Erwan
 * @date 23/11/2019
 */

#ifndef SIMPHONIZ_EXCEPTION_H
#define SIMPHONIZ_EXCEPTION_H

#include <exception>

#include <QtCore/QString>

namespace simphoniz {

/**
 * @defgroup exception Exception
 */

/**
 * @brief A custom exception class.
 * @ingroup exception
 */
class Exception : public std::exception {
public:
    /**
     * @brief Constructor.
     * @param file the name of the source file where the exception was raised
     * @param line the number of the line where the exception was raised
     * @param cause a string which indicates the cause of the exception
     */
    Exception(const char* file, int line, const QString& cause);

    /// @sa http://www.cplusplus.com/reference/exception/exception/what/
    virtual const char* what() const noexcept override;

private:
    const QString m_Message;

    // https://wiki.qt.io/Technical_FAQ#How_can_I_convert_a_QString_to_char.2A_and_vice_versa.3F
    const QByteArray m_MessageData;
};

} // namespace simphoniz

#endif // SIMPHONIZ_EXCEPTION_H
