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
 * @file PhotoDirectoryParser.h
 * @author Erwan
 * @date 23/12/2019
 */

#ifndef SIMPHONIZ_PHOTODIRECTORYPARSER_H
#define SIMPHONIZ_PHOTODIRECTORYPARSER_H

#include <memory>

#include <genepy/log/logging_macros.h>

class QDir;
class QFileInfo;

namespace simphoniz {

class PhotoDirectory;
class PhotoFile;

/**
 * @defgroup photo-io Photo
 * @ingroup io
 */

/**
 * @brief Parses a photo directory.
 * @ingroup photo-io
 */
class PhotoDirectoryParser {
public:
    /// Constructor.
    PhotoDirectoryParser();

    /**
     * @brief Executes the parser on the given directory.
     * @param dir the directory to parse
     * @return a pointer to a `PhotoDirectory` object which can be null if the directory contains no
     * photo
     */
    std::unique_ptr<PhotoDirectory> execute(const QDir& dir) const;

private:
    GENEPY_DECLARE_CLASS_LOGGER(logger)

    PhotoDirectory* parseDir(const QDir& dir) const;
    PhotoFile* parseFile(const QFileInfo& info) const;
};

} // namespace simphoniz

#endif // SIMPHONIZ_PHOTODIRECTORYPARSER_H
