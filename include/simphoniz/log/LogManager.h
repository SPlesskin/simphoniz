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
 * @file LogManager.h
 * @author Erwan
 * @date 12/12/2019
 */

#ifndef SIMPHONIZ_LOGMANAGER_H
#define SIMPHONIZ_LOGMANAGER_H

#include <memory>

namespace spdlog {

class logger;

namespace sinks {

class sink;

} // namespace sinks

} // namespace spdlog

namespace simphoniz {

/**
 * @defgroup log Log
 */

/**
 * @brief The `LogManager` class.
 *
 * This object initializes the log file and provides a method for obtaining loggers.
 *
 * @ingroup log
 */
class LogManager {
public:
    /// Returns the single instance of this class.
    static LogManager& getInstance();

    LogManager(const LogManager&) = delete;
    void operator=(const LogManager&) = delete;

    /// Initializes this manager.
    void initialize();

    /// Returns a logger with the given name.
    std::unique_ptr<spdlog::logger> getLogger(const std::string& name) const;

private:
    LogManager();

    std::shared_ptr<spdlog::sinks::sink> m_SharedFileSink;

    // A "backup" sink which will be used if the manager isn't initialized or if the main sink fails
    // to be created.
    const std::shared_ptr<spdlog::sinks::sink> m_SharedNullSink;
};

} // namespace simphoniz

#endif // SIMPHONIZ_LOGMANAGER_H
