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
 * @file LogManager.cpp
 * @author Erwan
 * @date 12/12/2019
 */

#include <iostream>

#include <QtCore/QDir>

#include <spdlog/logger.h>
#include <spdlog/sinks/null_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>

#include <simphoniz/Application.h>
#include <simphoniz/exception/exception_macros.h>
#include <simphoniz/log/LogManager.h>

namespace simphoniz {

namespace {

const auto LOG_DIR_NAME = QStringLiteral("log");
const auto LOG_FILENAME_EXTENSION = QStringLiteral(".log");
const auto MAX_LOG_FILE_SIZE = 5 * 1024 * 1024; // 5 MB
const auto MAX_LOG_FILES = 3;

#ifdef QT_DEBUG
const auto LOG_LEVEL = spdlog::level::debug;
#else
const auto LOG_LEVEL = spdlog::level::info;
#endif

const auto LOG_FORMAT = "[%Y/%m/%d %H:%M:%S.%e] [%P] [%n] [%l] %v";

QString createLogDir()
{
    const auto logDirPath = QDir::homePath() + "/." + Application::applicationName().toLower() +
                            '/' + Application::applicationVersion() + '/' + LOG_DIR_NAME + '/';

    THROW_EXCEPTION_IF(!QDir{}.mkpath(logDirPath), QStringLiteral("Can't create log directory"))

    return logDirPath;
}

spdlog::sink_ptr createFileSink()
{
    // Initialize the log file
    const auto logDirPath = createLogDir();
    const auto logFilePath =
        logDirPath + Application::applicationName().toLower() + LOG_FILENAME_EXTENSION;

    return std::make_shared<spdlog::sinks::rotating_file_sink_st>(logFilePath.toStdString(),
                                                                  MAX_LOG_FILE_SIZE, MAX_LOG_FILES);
}

} // namespace

LogManager& LogManager::getInstance()
{
    static LogManager instance;
    return instance;
}

void LogManager::initialize()
{
    try {
        m_SharedFileSink = createFileSink();

        // The log level is set to TRACE by default.
        // m_SharedFileSink->set_level(LOG_LEVEL);

        m_SharedFileSink->set_pattern(LOG_FORMAT);
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

std::unique_ptr<spdlog::logger> LogManager::getLogger(const std::string& name) const
{
    auto result = m_SharedFileSink ? std::make_unique<spdlog::logger>(name, m_SharedFileSink)
                                   : std::make_unique<spdlog::logger>(name, m_SharedNullSink);

    // Set the log level from INFO to ...
    result->set_level(LOG_LEVEL);

    return result;
}

LogManager::LogManager() : m_SharedNullSink{std::make_shared<spdlog::sinks::null_sink_st>()} {}

} // namespace simphoniz
