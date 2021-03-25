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

#include "TestPhotoFile.h"

#include <simphoniz/photo/PhotoFile.h>

using namespace simphoniz;

void TestPhotoFile::testEqualityOperator()
{
    {
        const auto name = QStringLiteral("a.jpeg");
        const auto date = QDateTime::currentDateTime();

        const auto photo1 = PhotoFile{name, date};
        const auto photo2 = PhotoFile{name, date};

        QVERIFY(photo1 == photo2);
    }

    {
        const auto name = QStringLiteral("a.jpeg");

        const auto photo1 = PhotoFile{name};
        const auto photo2 = PhotoFile{name};

        QVERIFY(photo1 == photo2);
    }

    {
        const auto date = QDateTime::currentDateTime();

        const auto photo1 = PhotoFile{QStringLiteral("a.jpeg"), date};
        const auto photo2 = PhotoFile{QStringLiteral("b.jpeg"), date};

        QVERIFY(photo1 != photo2);
    }

    {
        const auto name = QStringLiteral("a.jpeg");

        const auto photo1 = PhotoFile{name, QDateTime{QDate{2020, 1, 1}, QTime{0, 0}}};
        const auto photo2 = PhotoFile{name, QDateTime{QDate{2020, 1, 2}, QTime{0, 0}}};

        QVERIFY(photo1 != photo2);
    }
}

QTEST_MAIN(TestPhotoFile)
