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
 * @file PhotoResource.h
 * @author Erwan
 * @date 23/12/2019
 */

#ifndef SIMPHONIZ_PHOTORESOURCE_H
#define SIMPHONIZ_PHOTORESOURCE_H

namespace simphoniz {

class PhotoResourceVisitor;

/**
 * @defgroup photo Photo
 * @{
 */

/**
 * @brief A photo resource.
 *
 * A photo resource can be a photo file or a directory which contains photo files (or other photo
 * directories).
 */
class PhotoResource {
public:
    /// Constructor.
    PhotoResource();

    /// Destructor.
    virtual ~PhotoResource();

    virtual void accept(PhotoResourceVisitor& visitor) const = 0;

    friend bool operator==(const PhotoResource& lhs, const PhotoResource& rhs);

private:
    // This function has a precondition: it will only be called if the object passed in parameter is
    // of the same type as the instance invoking it.
    virtual bool isEqual(const PhotoResource& other) const = 0;
};

/// Overloaded equality operator to compare `PhotoResource` objects.
bool operator==(const PhotoResource& lhs, const PhotoResource& rhs);

/// Overloaded inequality operator to compare `PhotoResource` objects.
bool operator!=(const PhotoResource& lhs, const PhotoResource& rhs);

/** @} */

} // namespace simphoniz

#endif // SIMPHONIZ_PHOTORESOURCE_H
