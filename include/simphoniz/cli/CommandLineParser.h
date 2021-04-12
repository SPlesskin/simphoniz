/* Simphoniz - A Simple Photo Organizer
 * Copyright (C) 2020, 2021  Erwan Grâce <erwan.grace@outlook.fr>
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
 * @file CommandLineParser.h
 * @author Erwan
 * @date 19/10/2019
 */

#ifndef SIMPHONIZ_COMMANDLINEPARSER_H
#define SIMPHONIZ_COMMANDLINEPARSER_H

#include <QtCore/QCommandLineParser>

#include "CommandLineParsingResult.h"

namespace simphoniz {

struct CommandLineData;

/**
 * @defgroup cli Command-Line Interface
 */

/**
 * @brief Parses the command line.
 * @ingroup cli
 */
class CommandLineParser : public QCommandLineParser {
public:
    /// Constructor.
    CommandLineParser();

    /**
     * @brief Performs the command-line parsing.
     * @param data the data retrieved from the command line
     * @param errorMessage an error message which is set if the parsing failed
     * @return the result of the parsing
     */
    CommandLineParsingResult doParsing(CommandLineData& data, QString& errorMessage);

private:
    const QCommandLineOption helpOption_;
    const QCommandLineOption versionOption_;
};

} // namespace simphoniz

#endif // SIMPHONIZ_COMMANDLINEPARSER_H
