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
 * @file PhotoResourceVisitor.h
 * @author Erwan
 * @date 01/01/2020
 */

#ifndef SIMPHONIZ_PHOTORESOURCEVISITOR_H
#define SIMPHONIZ_PHOTORESOURCEVISITOR_H

#include <QtCore/QObject>

namespace simphoniz {

class PhotoDirectory;
class PhotoFile;

/**
 * @defgroup processing Processing
 */

/**
 * @brief Base class for the processing classes.
 * @ingroup processing
 *
 * All of these classes implement the visitor pattern.
 */
class PhotoResourceVisitor : public QObject {
public:
    /// Constructor.
    PhotoResourceVisitor();

    virtual void visit(const PhotoDirectory& dir) = 0;
    virtual void visit(const PhotoFile& file) = 0;
};

} // namespace simphoniz

#endif // SIMPHONIZ_PHOTORESOURCEVISITOR_H
