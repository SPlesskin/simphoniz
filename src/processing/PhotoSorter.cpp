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
 * @file PhotoSorter.h
 * @author Erwan
 * @date 01/01/2020
 */

#include <simphoniz/photo/PhotoDirectory.h>
#include <simphoniz/photo/PhotoFile.h>
#include <simphoniz/processing/PhotoSorter.h>

namespace simphoniz {

namespace {

const auto DIR_PATH_FORMAT = QStringLiteral("yyyy/MM MMM");
const auto DEFAULT_DIRNAME = QStringLiteral("Unsorted");
const auto FILENAME_PREFIX_FORMAT = QStringLiteral("yyyyMMdd-hhmmss");
const auto FILENAME_EXTENSION = QStringLiteral(".jpeg");

auto currentPhotoDirPath = QString{};

QString computeNewFilePath(const PhotoFile& file, const QDir& destinationDir)
{
    const auto date = file.getCreationDate();
    auto fileName = date.isValid() ? date.toString(FILENAME_PREFIX_FORMAT) : file.getBaseName();

    // We verify if a file named as above is present in the destination folder.
    const auto list =
        destinationDir.entryList(QStringList{fileName + '*' + FILENAME_EXTENSION}, QDir::Files);
    if (!list.isEmpty()) {
        fileName += QString{" [%1]"}.arg(list.size());
    }

    fileName += FILENAME_EXTENSION;

    return destinationDir.path() + '/' + fileName;
}

} // namespace

SIMPHONIZ_DEFINE_CLASS_LOGGER(PhotoSorter::logger, "PhotoSorter")

PhotoSorter::PhotoSorter(const QDir& destinationDir) : m_DestinationRootDir{destinationDir} {}

void PhotoSorter::visit(const PhotoDirectory& dir)
{
    // Store the path of the current directory
    currentPhotoDirPath = dir.getPath();

    for (auto it = std::cbegin(dir.getResources()); it != std::cend(dir.getResources()); ++it) {
        (*it)->accept(*this);
    }
}

void PhotoSorter::visit(const PhotoFile& file)
{
    // The path of the file to process
    const auto filePath = currentPhotoDirPath + '/' + file.getName();

    // Create the destination folder
    const auto date = file.getCreationDate();
    const auto locale = QLocale{QLocale::English};
    const auto dirPath =
        date.isValid() ? locale.toString(date, DIR_PATH_FORMAT).toUpper() : DEFAULT_DIRNAME;

    if (!m_DestinationRootDir.mkpath(dirPath)) {
        SIMPHONIZ_LOG_ERROR(logger, "Can't create destination directory for " << filePath)
        return;
    }

    const auto newFilePath =
        computeNewFilePath(file, QDir{m_DestinationRootDir.path() + '/' + dirPath});

    if (!QFile::rename(filePath, newFilePath)) {
        SIMPHONIZ_LOG_ERROR(logger, "Can't rename " << filePath)
    }

    emit photoSorted();
}

} // namespace simphoniz
