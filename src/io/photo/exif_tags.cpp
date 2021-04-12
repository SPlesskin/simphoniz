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
 * @file exif_tags.cpp
 * @author Erwan
 * @date 24/01/2020
 */

#include "exif_tags.h"

namespace simphoniz {

namespace exif {

namespace key {

const std::string DATE_TIME_ORIGINAL = "Exif.Photo.DateTimeOriginal";

} // namespace key

namespace value {

const QString DATE_TIME_ORIGINAL_FORMAT = QStringLiteral("yyyy:MM:dd hh:mm:ss");

} // namespace value

} // namespace exif

} // namespace simphoniz
