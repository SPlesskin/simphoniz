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

#include "TestPhotoDirectory.h"

#include <simphoniz/photo/PhotoDirectory.h>
#include <simphoniz/photo/PhotoFile.h>

using namespace simphoniz;

void TestPhotoDirectory::testEqualityOperator()
{
    {
        const auto path = QStringLiteral("a");
        const auto name = QStringLiteral("a.jpeg");
        const auto date = QDateTime::currentDateTime();

        const auto dir1 = PhotoDirectory{path, new PhotoFile{name, date}};
        const auto dir2 = PhotoDirectory{path, new PhotoFile{name, date}};

        QVERIFY(dir1 == dir2);
    }

    {
        const auto name = QStringLiteral("a.jpeg");
        const auto date = QDateTime::currentDateTime();

        const auto dir1 = PhotoDirectory{QStringLiteral("a"), new PhotoFile{name, date}};
        const auto dir2 = PhotoDirectory{QStringLiteral("b"), new PhotoFile{name, date}};

        QVERIFY(dir1 != dir2);
    }

    {
        const auto path = QStringLiteral("a");
        const auto name = QStringLiteral("a.jpeg");
        const auto date = QDateTime::currentDateTime();

        const auto dir1 = PhotoDirectory{path, new PhotoFile{name, date}};
        const auto dir2 =
            PhotoDirectory{path, {new PhotoFile{name, date}, new PhotoFile{name, date}}};

        QVERIFY(dir1 != dir2);
    }

    {
        const auto path = QStringLiteral("a");
        const auto date = QDateTime::currentDateTime();

        const auto dir1 = PhotoDirectory{path, new PhotoFile{QStringLiteral("a.jpeg"), date}};
        const auto dir2 = PhotoDirectory{path, new PhotoFile{QStringLiteral("b.jpeg"), date}};

        QVERIFY(dir1 != dir2);
    }
}

QTEST_MAIN(TestPhotoDirectory)
