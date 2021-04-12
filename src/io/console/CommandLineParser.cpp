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
 * @file CommandLineParser.cpp
 * @author Erwan
 * @date 19/10/2019
 */

#include <QtCore/QVector>

#include <simphoniz/Application.h>
#include <simphoniz/io/console/CommandLineData.h>
#include <simphoniz/io/console/CommandLineParser.h>

namespace simphoniz {

namespace {

const auto SOURCE_ARGUMENT_NAME = QStringLiteral("source");
const auto SOURCE_ARGUMENT_DESCRIPTION = QStringLiteral("The unsorted photo directory.");
const auto SOURCE_ARGUMENT_SYNTAX = QStringLiteral("<source>");
const auto DESTINATION_ARGUMENT_NAME = QStringLiteral("destination");
const auto DESTINATION_ARGUMENT_DESCRIPTION = QStringLiteral("The sorted photo directory.");
const auto DESTINATION_ARGUMENT_SYNTAX = QStringLiteral("<destination>");
const auto N_MANDATORY_ARGUMENTS = 2;

QString getApplicationDescription()
{
    return Application::applicationName() +
           QStringLiteral(" allows sorting photos according to their creation time.");
}

} // namespace

CommandLineParser::CommandLineParser()
    : m_HelpOption{addHelpOption()}, m_VersionOption{addVersionOption()}
{
    setApplicationDescription(getApplicationDescription());

    setSingleDashWordOptionMode(ParseAsLongOptions);

    addPositionalArgument(SOURCE_ARGUMENT_NAME, SOURCE_ARGUMENT_DESCRIPTION,
                          SOURCE_ARGUMENT_SYNTAX);
    addPositionalArgument(DESTINATION_ARGUMENT_NAME, DESTINATION_ARGUMENT_DESCRIPTION,
                          DESTINATION_ARGUMENT_SYNTAX);
}

CommandLineParsingResult CommandLineParser::doParsing(CommandLineData& data, QString& errorMessage)
{
    if (!parse(Application::arguments())) {
        errorMessage = errorText();
        return CommandLineParsingResult::KO;
    }

    // Process the optional arguments
    if (isSet(m_HelpOption)) {
        return CommandLineParsingResult::HELP_REQUESTED;
    }

    if (isSet(m_VersionOption)) {
        return CommandLineParsingResult::VERSION_REQUESTED;
    }

    // Process the mandatory arguments
    const auto args = positionalArguments();
    if (args.size() != N_MANDATORY_ARGUMENTS) {
        errorMessage = (args.size() < N_MANDATORY_ARGUMENTS)
                           ? QStringLiteral("The source or destination directory is missing.")
                           : QStringLiteral("Too many directories passed.");
        return CommandLineParsingResult::KO;
    }

    data.sourceDir.setPath(args.first());
    data.destinationDir.setPath(args.last());

    return CommandLineParsingResult::OK;
}

} // namespace simphoniz
