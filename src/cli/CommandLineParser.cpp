/* Simphoniz - A Simple Photo Organizer
 * Copyright (C) 2020, 2021  Erwan Grâce <erwan.grace@outlook.fr>
 *
 * This file is part of Simphoniz.
 *
 * Simphoniz is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Simphoniz is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Simphoniz.  If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * @file CommandLineParser.cpp
 * @author Erwan
 * @date 19/10/2019
 */

#include <QtCore/QVector>

#include <simphoniz/Application.h>
#include <simphoniz/cli/CommandLineData.h>
#include <simphoniz/cli/CommandLineParser.h>

namespace simphoniz {

namespace {

const auto kSourceArgumentName = QStringLiteral("source");
const auto kSourceArgumentDescription = QStringLiteral("The unsorted photo directory.");
const auto kSourceArgumentSyntax = QStringLiteral("<source>");
const auto kDestinationArgumentName = QStringLiteral("destination");
const auto kDestinationArgumentDescription = QStringLiteral("The sorted photo directory.");
const auto kDestinationArgumentSyntax = QStringLiteral("<destination>");
const auto kNMandatoryArguments = 2;

QString getApplicationDescription()
{
    return Application::applicationName() +
           QStringLiteral(" allows sorting photos according to their creation time.");
}

} // namespace

CommandLineParser::CommandLineParser()
    : helpOption_{addHelpOption()}, versionOption_{addVersionOption()}
{
    setApplicationDescription(getApplicationDescription());

    setSingleDashWordOptionMode(ParseAsLongOptions);

    addPositionalArgument(kSourceArgumentName, kSourceArgumentDescription, kSourceArgumentSyntax);
    addPositionalArgument(kDestinationArgumentName, kDestinationArgumentDescription,
                          kDestinationArgumentSyntax);
}

CommandLineParsingResult CommandLineParser::doParsing(CommandLineData& data, QString& errorMessage)
{
    if (!parse(Application::arguments())) {
        errorMessage = errorText();
        return CommandLineParsingResult::kKo;
    }

    // Process the optional arguments
    if (isSet(helpOption_)) {
        return CommandLineParsingResult::kHelpRequested;
    }

    if (isSet(versionOption_)) {
        return CommandLineParsingResult::kVersionRequested;
    }

    // Process the mandatory arguments
    const auto args = positionalArguments();
    if (args.size() != kNMandatoryArguments) {
        errorMessage = (args.size() < kNMandatoryArguments)
                           ? QStringLiteral("The source or destination directory is missing.")
                           : QStringLiteral("Too many directories passed.");
        return CommandLineParsingResult::kKo;
    }

    data.sourceDir.setPath(args.first());
    data.destinationDir.setPath(args.last());

    return CommandLineParsingResult::kOk;
}

} // namespace simphoniz
