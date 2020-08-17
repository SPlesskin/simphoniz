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
 * @file PhotoDirectory.h
 * @author Erwan
 * @date 23/12/2019
 */

#ifndef SIMPHONIZ_PHOTODIRECTORY_H
#define SIMPHONIZ_PHOTODIRECTORY_H

#include <memory>
#include <vector>

#include <QtCore/QMetaType>
#include <QtCore/QSharedPointer>
#include <QtCore/QString>

#include "PhotoResource.h"

namespace simphoniz {

using PhotoResourceVector = std::vector<std::unique_ptr<PhotoResource>>;

/**
 * @brief A photo directory.
 * @ingroup photo
 */
class PhotoDirectory : public PhotoResource {
public:
    /**
     * @brief Constructor.
     * @param path this directory's path
     * @param resource a photo resource located in this directory
     * @note This directory takes ownership of the given resource.
     */
    explicit PhotoDirectory(const QString& path, PhotoResource* resource);

    /// Constructor which accepts multiple photo resources.
    explicit PhotoDirectory(const QString& path, const QVector<PhotoResource*>& resources);

    /**
     * @brief Adds a photo resource to this directory.
     * @param resource the resource to add
     * @note This directory takes ownership of the given resource.
     */
    void addResource(PhotoResource* resource);

    /**
     * @name Getters/Setters
     * @{
     */
    QString getPath() const;
    PhotoResourceVector const& getResources() const;
    /** @} */

    virtual void accept(PhotoResourceVisitor& visitor) const override;

private:
    virtual bool isEqual(const PhotoResource& other) const;

    const QString m_Path;
    PhotoResourceVector m_Resources;
};

} // namespace simphoniz

Q_DECLARE_METATYPE(QSharedPointer<simphoniz::PhotoDirectory>)

#endif // SIMPHONIZ_PHOTODIRECTORY_H
