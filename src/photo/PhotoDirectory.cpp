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
 * @file PhotoDirectory.cpp
 * @author Erwan
 * @date 23/12/2019
 */

#include <simphoniz/photo/PhotoDirectory.h>

#include <QtCore/QVector>

#include <simphoniz/processing/PhotoResourceVisitor.h>

namespace simphoniz {

PhotoDirectory::PhotoDirectory(const QString& path, PhotoResource* resource) : path_{path}
{
    addResource(resource);
}

PhotoDirectory::PhotoDirectory(const QString& path, const QVector<PhotoResource*>& resources)
    : path_{path}
{
    for (auto it = std::cbegin(resources); it != std::cend(resources); ++it) {
        addResource(*it);
    }
}

void PhotoDirectory::addResource(PhotoResource* resource)
{
    Q_ASSERT(resource);

    resources_.push_back(std::unique_ptr<PhotoResource>{resource});
}

QString PhotoDirectory::getPath() const { return path_; }

PhotoResourceVector const& PhotoDirectory::getResources() const { return resources_; }

void PhotoDirectory::accept(PhotoResourceVisitor& visitor) const { visitor.visit(*this); }

bool PhotoDirectory::isEqual(const PhotoResource& other) const
{
    const auto& obj = static_cast<const PhotoDirectory&>(other);

    if (path_ != obj.path_ || resources_.size() != obj.resources_.size()) {
        return false;
    }

    for (auto it = std::cbegin(resources_); it != std::cend(resources_); ++it) {
        // Check if at least one resource in the other directory is equal to the one at the current
        // iterator position
        if (!std::any_of(std::cbegin(obj.resources_), std::cend(obj.resources_),
                         [&it](const auto& v) { return *v == **it; })) {
            return false;
        }
    }

    return true;
}

} // namespace simphoniz
