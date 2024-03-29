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
 * @file PhotoDirectoryParser.cpp
 * @author Erwan
 * @date 23/12/2019
 */

#include <simphoniz/io/PhotoDirectoryParser.h>

#include <QtCore/QDirIterator>

#include <exiv2/exiv2.hpp>

#include <simphoniz/photo/PhotoDirectory.h>
#include <simphoniz/photo/PhotoFile.h>

#include "exif_tags.h"

namespace {

bool isFileNameExtensionValid(const QString& extension)
{
    for (auto it = std::cbegin(simphoniz::PhotoFile::kFilenameExtensions);
         it != std::cend(simphoniz::PhotoFile::kFilenameExtensions); ++it) {
        if (QString::compare(extension, *it, Qt::CaseInsensitive) == 0) {
            return true;
        }
    }

    return false;
}

QDateTime findPhotoCreationDate(const Exiv2::ExifData& data)
{
    const auto key = Exiv2::ExifKey{simphoniz::exif::key::kDateTimeOriginal};
    const auto it = data.findKey(key);
    if (it == data.end()) {
        return QDateTime{}; // Return an invalid date
    }

    return QDateTime::fromString(QString::fromStdString(it->toString()),
                                 simphoniz::exif::value::kDateTimeOriginalFormat);
}

} // namespace

namespace simphoniz {

GENEPY_DEFINE_CLASS_LOGGER(PhotoDirectoryParser::logger, "PhotoDirectoryParser")

PhotoDirectoryParser::PhotoDirectoryParser() {}

std::unique_ptr<PhotoDirectory> PhotoDirectoryParser::execute(const QDir& dir) const
{
    if (!dir.exists()) {
        GENEPY_LOG_ERROR(logger(), "Can't find directory " << dir.absolutePath())
        return std::unique_ptr<PhotoDirectory>{};
    }

    return std::unique_ptr<PhotoDirectory>{parseDir(dir)};
}

PhotoDirectory* PhotoDirectoryParser::parseDir(const QDir& dir) const
{
    GENEPY_LOG_DEBUG(logger(), "Parsing directory " << dir.absolutePath() << "...")

    // Initialization
    PhotoDirectory* result = nullptr;

    QDirIterator it{dir.path(), QDir::AllEntries | QDir::NoDotAndDotDot};
    while (it.hasNext()) {
        const auto path = it.next();

        auto* resource = it.fileInfo().isDir()
                             ? static_cast<PhotoResource*>(parseDir(QDir{path}))
                             : static_cast<PhotoResource*>(parseFile(it.fileInfo()));

        if (resource) {
            if (!result) {
                result = new PhotoDirectory{dir.path(), resource};
            }
            else {
                result->addResource(resource);
            }
        }
    }

    return result;
}

PhotoFile* PhotoDirectoryParser::parseFile(const QFileInfo& info) const
{
    GENEPY_LOG_DEBUG(logger(), "Parsing file " << info.absoluteFilePath() << "...")

    if (!isFileNameExtensionValid(info.suffix())) {
        return nullptr;
    }

    try {
        const auto image = Exiv2::ImageFactory::open(info.filePath().toStdString());
        image->readMetadata();

        const auto& exifData = image->exifData();
        if (exifData.empty()) {
            GENEPY_LOG_WARN(logger(), "No EXIF data found in file " << info.absoluteFilePath())
            return nullptr;
        }

        // Retrieve the creation date of the photo
        const auto creationDate = findPhotoCreationDate(exifData);
        if (!creationDate.isValid()) {
            GENEPY_LOG_WARN(logger(), "Can't get creation date of file "
                                          << info.absoluteFilePath());
        }
        else {
            GENEPY_LOG_DEBUG(logger(), "Creation date: " << creationDate.toString(
                                           QStringLiteral("yyyy/MM/dd hh:mm:ss")))
        }

        return new PhotoFile{info.fileName(), creationDate};
    }
    catch (const Exiv2::Error& e) {
        GENEPY_LOG_ERROR(logger(), "Error when reading metadata of file " << info.absoluteFilePath()
                                                                          << ": " << e.what())
        return nullptr;
    }
}

} // namespace simphoniz
