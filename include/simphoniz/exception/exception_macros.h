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
 * @file exception-macros.h
 * @author Erwan
 * @date 23/12/2019
 */

#ifndef SIMPHONIZ_EXCEPTION_MACROS_H
#define SIMPHONIZ_EXCEPTION_MACROS_H

#include <QtCore/QTextStream>

#include "Exception.h"

#ifdef Q_OS_WINDOWS
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

namespace simphoniz {

/**
 * @def THROW_EXCEPTION_IF(condition, cause)
 * @hideinitializer
 * @brief This macro throws an exception if the given condition is true.
 * @ingroup exception
 */
#define THROW_EXCEPTION_IF(condition, cause)                                                       \
    if (condition) {                                                                               \
        auto str = QString{};                                                                      \
        QTextStream stream{&str};                                                                  \
        stream << cause;                                                                           \
        throw Exception{__FILENAME__, __LINE__, str};                                              \
    }

} // namespace simphoniz

#endif // SIMPHONIZ_EXCEPTION_MACROS_H
