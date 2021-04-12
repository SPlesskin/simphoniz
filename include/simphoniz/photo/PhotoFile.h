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
 * @file PhotoFile.h
 * @author Erwan
 * @date 23/12/2019
 */

#ifndef SIMPHONIZ_PHOTOFILE_H
#define SIMPHONIZ_PHOTOFILE_H

#include <QtCore/QDateTime>
#include <QtCore/QStringList>

#include "PhotoResource.h"

namespace simphoniz {

/**
 * @brief A photo file.
 * @ingroup photo
 */
class PhotoFile : public PhotoResource {
public:
    /// The possible photo filename extensions.
    static const QStringList kFilenameExtensions;

    /**
     * @brief Constructor.
     * @param name the name of this file
     * @param creationDate this file's creation date
     */
    PhotoFile(const QString& name, const QDateTime& creationDate = QDateTime{});

    /**
     * @name Getters/Setters
     * @{
     */
    QString getName() const;
    QString getBaseName() const;
    QDateTime getCreationDate() const;
    /** @} */

    virtual void accept(PhotoResourceVisitor& visitor) const override;

private:
    virtual bool isEqual(const PhotoResource& other) const;

    const QString name_;
    const QDateTime creationDate_;
};

} // namespace simphoniz

#endif // SIMPHONIZ_PHOTOFILE_H
