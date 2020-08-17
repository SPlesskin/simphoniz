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
 * @file ProgressBar.h
 * @author Erwan
 * @date 02/01/2020
 */

#ifndef SIMPHONIZ_PROGRESSBAR_H
#define SIMPHONIZ_PROGRESSBAR_H

#include <QtCore/QObject>

namespace simphoniz {

/**
 * @brief Displays an ASCII progress bar.
 * @ingroup console
 */
class ProgressBar : public QObject {

    Q_OBJECT

public:
    /**
     * @brief Constructor.
     * @param totalPhotoCount the total number of photos to be sorted
     */
    explicit ProgressBar(int totalPhotoCount);

public slots:
    /// Updates this progress bar.
    void update();

private:
    const int m_TotalPhotoCount;
    int m_SortedPhotoCount;
};

} // namespace simphoniz

#endif // SIMPHONIZ_PROGRESSBAR_H
