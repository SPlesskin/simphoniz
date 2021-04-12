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
 * @file PhotoSorter.h
 * @author Erwan
 * @date 01/01/2020
 */

#ifndef SIMPHONIZ_PHOTOSORTER_H
#define SIMPHONIZ_PHOTOSORTER_H

#include <QtCore/QDir>

#include <genepy/log/logging_macros.h>

#include "PhotoResourceVisitor.h"

namespace simphoniz {

/**
 * @brief Sorts photo files.
 * @ingroup processing
 */
class PhotoSorter : public PhotoResourceVisitor {

    Q_OBJECT

public:
    /**
     * @brief Constructor.
     * @param destinationDir the root directory which will hold the sorted photos
     */
    explicit PhotoSorter(const QDir& destinationDir);

    virtual void visit(const PhotoDirectory& dir) override;
    virtual void visit(const PhotoFile& file) override;

signals:
    void photoSorted();

private:
    GENEPY_DECLARE_CLASS_LOGGER(logger)

    const QDir destinationRootDir_;
};

} // namespace simphoniz

#endif // SIMPHONIZ_PHOTOSORTER_H
