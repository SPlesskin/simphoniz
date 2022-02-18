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
 * @file PhotoCounter.h
 * @author Erwan
 * @date 01/01/2020
 */

#ifndef SIMPHONIZ_PHOTOCOUNTER_H
#define SIMPHONIZ_PHOTOCOUNTER_H

#include "PhotoResourceVisitor.h"

namespace simphoniz {

/**
 * @brief Counts the number of photo files.
 * @ingroup processing
 */
class PhotoCounter : public PhotoResourceVisitor {
public:
    /// Constructor.
    PhotoCounter();

    /// Returns the number of counted files.
    int getCount() const;

    virtual void visit(const PhotoDirectory& dir) override;
    virtual void visit(const PhotoFile& file) override;

private:
    int count_;
};

} // namespace simphoniz

#endif // SIMPHONIZ_PHOTOCOUNTER_H
