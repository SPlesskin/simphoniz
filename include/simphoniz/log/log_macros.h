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
 * @file log-macros.h
 * @author Erwan
 * @date 14/12/2019
 */

#ifndef SIMPHONIZ_LOG_MACROS_H
#define SIMPHONIZ_LOG_MACROS_H

#include <QtCore/QTextStream>

#include <spdlog/logger.h>

#include "LogManager.h"

namespace simphoniz {

/**
 * @ingroup log
 * @{
 */

/**
 * @def SIMPHONIZ_DECLARE_CLASS_LOGGER(varname)
 * @hideinitializer
 * @brief Declares a logger variable in a class.
 *
 * The logger is static so that it is shared between all the class instances. Actually, this macro
 * declares a function which returns a pointer to a static logger. That way, the logger is created
 * once the logging system is initialized.
 */
#define SIMPHONIZ_DECLARE_CLASS_LOGGER(varname) static spdlog::logger* varname();

/**
 * @def SIMPHONIZ_DEFINE_CLASS_LOGGER(varname, name)
 * @hideinitializer
 * @brief Defines a logger variable in a class.
 */
#define SIMPHONIZ_DEFINE_CLASS_LOGGER(varname, name)                                               \
    spdlog::logger* varname()                                                                      \
    {                                                                                              \
        static const auto logger = LogManager::getInstance().getLogger(name);                      \
        return logger.get();                                                                       \
    }

/**
 * @def SIMPHONIZ_LOG_TRACE(varname, message)
 * @hideinitializer
 * @brief Writes the given *trace* message to the log.
 */
#define SIMPHONIZ_LOG_TRACE(varname, message)                                                      \
    if (varname()->should_log(spdlog::level::trace)) {                                             \
        auto str = QString{};                                                                      \
        QTextStream stream{&str};                                                                  \
        stream << message;                                                                         \
        varname()->trace(str.toStdString());                                                       \
    }

/**
 * @def SIMPHONIZ_LOG_DEBUG(varname, message)
 * @hideinitializer
 * @brief Writes the given *debug* message to the log.
 */
#define SIMPHONIZ_LOG_DEBUG(varname, message)                                                      \
    if (varname()->should_log(spdlog::level::debug)) {                                             \
        auto str = QString{};                                                                      \
        QTextStream stream{&str};                                                                  \
        stream << message;                                                                         \
        varname()->debug(str.toStdString());                                                       \
    }

/**
 * @def SIMPHONIZ_LOG_INFO(varname, message)
 * @hideinitializer
 * @brief Writes the given *info* message to the log.
 */
#define SIMPHONIZ_LOG_INFO(varname, message)                                                       \
    if (varname()->should_log(spdlog::level::info)) {                                              \
        auto str = QString{};                                                                      \
        QTextStream stream{&str};                                                                  \
        stream << message;                                                                         \
        varname()->info(str.toStdString());                                                        \
    }

/**
 * @def SIMPHONIZ_LOG_WARN(varname, message)
 * @hideinitializer
 * @brief Writes the given *warn* message to the log.
 */
#define SIMPHONIZ_LOG_WARN(varname, message)                                                       \
    if (varname()->should_log(spdlog::level::warn)) {                                              \
        auto str = QString{};                                                                      \
        QTextStream stream{&str};                                                                  \
        stream << message;                                                                         \
        varname()->warn(str.toStdString());                                                        \
    }

/**
 * @def SIMPHONIZ_LOG_ERROR(varname, message)
 * @hideinitializer
 * @brief Writes the given *error* message to the log.
 */
#define SIMPHONIZ_LOG_ERROR(varname, message)                                                      \
    if (varname()->should_log(spdlog::level::err)) {                                               \
        auto str = QString{};                                                                      \
        QTextStream stream{&str};                                                                  \
        stream << message;                                                                         \
        varname()->error(str.toStdString());                                                       \
    }

/**
 * @def SIMPHONIZ_LOG_FATAL(varname, message)
 * @hideinitializer
 * @brief Writes the given *fatal* message to the log.
 */
#define SIMPHONIZ_LOG_FATAL(varname, message)                                                      \
    if (varname()->should_log(spdlog::level::critical)) {                                          \
        auto str = QString{};                                                                      \
        QTextStream stream{&str};                                                                  \
        stream << message;                                                                         \
        varname()->critical(str.toStdString());                                                    \
    }

/** @} */

} // namespace simphoniz

#endif // SIMPHONIZ_LOG_MACROS_H
