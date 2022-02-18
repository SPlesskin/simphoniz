/* Simphoniz - A Simple Photo Organizer
 * Copyright (C) 2020-2022  Erwan Grâce <erwan.grace@outlook.fr>
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
 * @file main.cpp
 * @author Erwan
 * @date 21/09/2019
 */

#include <iostream>

#include <genepy/application/ConsoleApplication.h>
#include <genepy/cli/CommandLineParserBuilder.h>
#include <genepy/cli/ProgressBar.h>
#include <genepy/log/Logger.h>

#include <simphoniz/ApplicationInformation.h>
#include <simphoniz/io/PhotoDirectoryParser.h>
#include <simphoniz/photo/PhotoDirectory.h>
#include <simphoniz/processing/PhotoCounter.h>
#include <simphoniz/processing/PhotoSorter.h>

namespace {

const auto kCopyrightNotice = "Simphoniz  Copyright (C) 2020-2022  Erwan Grâce\n"
                              "This is free software; see the source code for copying conditions.\n"
                              "There is ABSOLUTELY NO WARRANTY; not even for MERCHANTABILITY or\n"
                              "FITNESS FOR A PARTICULAR PURPOSE.\n\n";

} // namespace

using namespace simphoniz;

int main(int argc, char** argv)
{
    genepy::ConsoleApplication app{kApplicationInformation, argc, argv};

    /********************************************
     * Parse the command line
     ********************************************/
    genepy::CommandLineParser parser =
        genepy::CommandLineParser::create(app)
            .addArgument(QStringLiteral("source"), QStringLiteral("The unsorted photo directory."),
                         QStringLiteral("<source>"))
            .addArgument(QStringLiteral("destination"),
                         QStringLiteral("The sorted photo directory."),
                         QStringLiteral("<destination>"));

    parser.doParsing();

    const auto sourceDir = parser.getArgumentValue<QDir>(QStringLiteral("source"));
    const auto destinationDir = parser.getArgumentValue<QDir>(QStringLiteral("destination"));

    std::cout << kCopyrightNotice;

    /********************************************
     * Initialize the logging system
     ********************************************/
    genepy::Logger::initialize(&app);

    /********************************************
     * Search for the photos to sort
     ********************************************/
    std::cout << "Analyzing directory " << sourceDir.absolutePath().toStdString() << "..."
              << std::endl;

    const auto photoDir = PhotoDirectoryParser{}.execute(sourceDir);
    if (!photoDir) {
        std::cerr << "No photo found!" << std::endl;
        return 1;
    }

    /********************************************
     * Process the photo files
     ********************************************/
    PhotoCounter counter;
    photoDir->accept(counter);
    const auto count = counter.getCount();

    std::cout << "Processing " << count << " photo(s)..." << std::endl;

    PhotoSorter sorter{destinationDir};
    genepy::ProgressBar progressBar{count};

    QObject::connect(&sorter, &PhotoSorter::photoSorted, &progressBar,
                     &genepy::ProgressBar::update);

    photoDir->accept(sorter);

    return 0;
}
