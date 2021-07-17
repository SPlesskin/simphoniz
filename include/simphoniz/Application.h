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
 * @file Application.h
 * @author Erwan
 * @date 27/09/2019
 */

#ifndef SIMPHONIZ_APPLICATION_H
#define SIMPHONIZ_APPLICATION_H

#include <QtCore/QCoreApplication>

namespace simphoniz {

/**
 * @brief The `Application` class.
 *
 * In this project, it is mainly used to store the application's name and version number.
 */
class Application : public QCoreApplication {
public:
    /**
     * @brief Constructor.
     * @param argc the number of command-line arguments
     * @param argv the command-line arguments
     */
    Application(int& argc, char** argv);
};

} // namespace simphoniz

#endif // SIMPHONIZ_APPLICATION_H
