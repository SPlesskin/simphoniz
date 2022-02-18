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

#include "TestPhotoSorter.h"

#include <simphoniz/io/PhotoDirectoryParser.h>
#include <simphoniz/photo/PhotoDirectory.h>
#include <simphoniz/processing/PhotoSorter.h>

#include "../common.h"

using namespace simphoniz;

namespace {

bool isDirectoryEmpty(const QString& dirPath)
{
    const auto dir = QDir{dirPath};
    const auto list = dir.entryList(QDir::AllEntries | QDir::NoDotAndDotDot);

    return list.isEmpty();
}

} // namespace

void TestPhotoSorter::initTestCase()
{
    QVERIFY(workingDir_.isValid());

    qDebug() << "Working directory:" << workingDir_.path();

    destinationDir_.setPath(workingDir_.path() + QStringLiteral("/Photos"));
}

void TestPhotoSorter::cleanup() { QVERIFY(destinationDir_.removeRecursively()); }

void TestPhotoSorter::test_data()
{
    QTest::addColumn<QSharedPointer<PhotoDirectory>>("photoDir");
    QTest::addColumn<QStringList>("sortedPhotoPaths");

    {
        const auto dir = QDir{workingDir_.path() + QStringLiteral("/a")};

        QVERIFY(dir.mkpath(QStringLiteral(".")));

        const auto fileName = QStringLiteral("antelope-canyon.jpg");
        QFile file{kTestImageDirPath + '/' + fileName};

        QVERIFY(file.copy(dir.path() + '/' + fileName));

        auto photoDir = PhotoDirectoryParser{}.execute(dir);

        QTest::newRow("directory with dated photo")
            << QSharedPointer<PhotoDirectory>{photoDir.release()}
            << QStringList{destinationDir_.path() +
                           QStringLiteral("/2005/10 OCT/20051020-150619.jpeg")};
    }

    {
        const auto dir = QDir{workingDir_.path() + QStringLiteral("/b")};

        QVERIFY(dir.mkpath(QStringLiteral(".")));

        const auto fileName = QStringLiteral("tractor.jpg");
        QFile file{kTestImageDirPath + '/' + fileName};

        QVERIFY(file.copy(dir.path() + '/' + fileName));

        auto photoDir = PhotoDirectoryParser{}.execute(dir);

        QTest::newRow("directory with undated photo")
            << QSharedPointer<PhotoDirectory>{photoDir.release()}
            << QStringList{destinationDir_.path() + QStringLiteral("/Unsorted/tractor.jpeg")};
    }

    {
        const auto dir = QDir{workingDir_.path() + QStringLiteral("/c")};

        QVERIFY(dir.mkpath(QStringLiteral(".")));

        const auto fileName = QStringLiteral("antelope-canyon.jpg");
        QFile file{kTestImageDirPath + '/' + fileName};

        QVERIFY(file.copy(dir.path() + QStringLiteral("/a.jpeg")));
        QVERIFY(file.copy(dir.path() + QStringLiteral("/b.jpeg")));

        auto photoDir = PhotoDirectoryParser{}.execute(dir);

        QTest::newRow("directory with duplicate photos")
            << QSharedPointer<PhotoDirectory>{photoDir.release()}
            << (QStringList{destinationDir_.path() +
                            QStringLiteral("/2005/10 OCT/20051020-150619.jpeg")}
                << destinationDir_.path() +
                       QStringLiteral("/2005/10 OCT/20051020-150619 [1].jpeg"));
    }
}

void TestPhotoSorter::test()
{
    QFETCH(QSharedPointer<PhotoDirectory>, photoDir);
    QFETCH(QStringList, sortedPhotoPaths);

    PhotoSorter sorter{destinationDir_};
    photoDir->accept(sorter);

    for (const auto& path : sortedPhotoPaths) {
        QVERIFY(QFile::exists(path));
    }

    QVERIFY(isDirectoryEmpty(photoDir->getPath()));
}

QTEST_APPLESS_MAIN(TestPhotoSorter)
