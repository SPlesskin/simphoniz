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
 * @file PhotoFile.cpp
 * @author Erwan
 * @date 23/12/2019
 */

#include <simphoniz/photo/PhotoFile.h>

#include <simphoniz/processing/PhotoResourceVisitor.h>

namespace simphoniz {

const QStringList PhotoFile::kFilenameExtensions = QStringList{"jpeg", "jpg"};

PhotoFile::PhotoFile(const QString& name, const QDateTime& creationDate)
    : name_{name}, creationDate_{creationDate}
{
}

QString PhotoFile::getName() const { return name_; }

QString PhotoFile::getBaseName() const { return name_.section('.', 0, 0); }

QDateTime PhotoFile::getCreationDate() const { return creationDate_; }

void PhotoFile::accept(PhotoResourceVisitor& visitor) const { visitor.visit(*this); }

bool PhotoFile::isEqual(const PhotoResource& other) const
{
    const auto& obj = static_cast<const PhotoFile&>(other);

    return name_ == obj.name_ && creationDate_ == obj.creationDate_;
}

} // namespace simphoniz
