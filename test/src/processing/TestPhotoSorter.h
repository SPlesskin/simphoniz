/* Simphoniz - A Simple Photo Organizer
 * Copyright (C) 2020-2022  Erwan Grâce <erwan.grace@outlook.fr>
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

#ifndef TESTPHOTOSORTER_H
#define TESTPHOTOSORTER_H

#include <QtTest/QtTest>

class TestPhotoSorter : public QObject {

    Q_OBJECT

private slots:
    void initTestCase();
    void cleanup();
    void test_data();
    void test();

private:
    QTemporaryDir workingDir_;
    QDir destinationDir_;
};

#endif // TESTPHOTOSORTER_H
