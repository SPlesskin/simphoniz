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

#include "TestPhotoDirectoryParser.h"

#include <simphoniz/io/PhotoDirectoryParser.h>
#include <simphoniz/photo/PhotoDirectory.h>
#include <simphoniz/photo/PhotoFile.h>

#include "../common.h"

using namespace simphoniz;

void TestPhotoDirectoryParser::initTestCase()
{
    QVERIFY(workingDir_.isValid());

    qDebug() << "Working directory:" << workingDir_.path();
}

void TestPhotoDirectoryParser::testExecute_data()
{
    QTest::addColumn<QDir>("dir");
    QTest::addColumn<QSharedPointer<PhotoDirectory>>("expectedPhotoDir");

    QTest::newRow("non-existent directory") << QDir{workingDir_.path() + QStringLiteral("/a")}
                                            << QSharedPointer<PhotoDirectory>{};

    {
        const auto dir = QDir{workingDir_.path() + QStringLiteral("/a")};

        QVERIFY(dir.mkpath(QStringLiteral(".")));

        QTest::newRow("empty directory") << dir << QSharedPointer<PhotoDirectory>{};
    }

    {
        const auto dir = QDir{workingDir_.path() + QStringLiteral("/b")};

        QVERIFY(dir.mkpath(QStringLiteral(".")));

        const auto fileName = QStringLiteral("emoticon.png");
        QFile file{kTestImageDirPath + '/' + fileName};

        QVERIFY(file.copy(dir.path() + '/' + fileName));

        QTest::newRow("directory with non-JPEG file") << dir << QSharedPointer<PhotoDirectory>{};
    }

    {
        const auto dir = QDir{workingDir_.path() + QStringLiteral("/c")};

        QVERIFY(dir.mkpath(QStringLiteral(".")));

        const auto fileName = QStringLiteral("eagle.jpg");
        QFile file{kTestImageDirPath + '/' + fileName};

        QVERIFY(file.copy(dir.path() + '/' + fileName));

        QTest::newRow("directory with EXIF-free photo") << dir << QSharedPointer<PhotoDirectory>{};
    }

    {
        const auto dir = QDir{workingDir_.path() + QStringLiteral("/d")};

        QVERIFY(dir.mkpath(QStringLiteral(".")));

        const auto fileName = QStringLiteral("tractor.jpg");
        QFile file{kTestImageDirPath + '/' + fileName};

        QVERIFY(file.copy(dir.path() + '/' + fileName));

        const auto expectedPhotoDir =
            QSharedPointer<PhotoDirectory>::create(dir.path(), new PhotoFile{fileName});

        QTest::newRow("directory with undated photo") << dir << expectedPhotoDir;
    }

    {
        const auto dir = QDir{workingDir_.path() + QStringLiteral("/e")};

        QVERIFY(dir.mkpath(QStringLiteral(".")));

        const auto fileName = QStringLiteral("antelope-canyon.jpg");
        QFile file{kTestImageDirPath + '/' + fileName};

        QVERIFY(file.copy(dir.path() + '/' + fileName));

        const auto expectedPhotoDir = QSharedPointer<PhotoDirectory>::create(
            dir.path(), new PhotoFile{fileName, QDateTime{QDate{2005, 10, 20}, QTime{15, 6, 19}}});

        QTest::newRow("directory with dated photo") << dir << expectedPhotoDir;
    }

    {
        const auto dir = QDir{workingDir_.path() + QStringLiteral("/f")};

        const auto subdirName = QStringLiteral("g");

        QVERIFY(dir.mkpath(subdirName));

        const auto fileName = QStringLiteral("antelope-canyon.jpg");
        QFile file{kTestImageDirPath + '/' + fileName};

        QVERIFY(file.copy(dir.path() + '/' + subdirName + '/' + fileName));

        const auto expectedPhotoDir = QSharedPointer<PhotoDirectory>::create(
            dir.path(), new PhotoDirectory{dir.path() + '/' + subdirName,
                                           new PhotoFile{fileName, QDateTime{QDate{2005, 10, 20},
                                                                             QTime{15, 6, 19}}}});

        QTest::newRow("directory tree") << dir << expectedPhotoDir;
    }
}

void TestPhotoDirectoryParser::testExecute()
{
    QFETCH(QDir, dir);
    QFETCH(QSharedPointer<PhotoDirectory>, expectedPhotoDir);

    const auto photoDir = PhotoDirectoryParser{}.execute(dir);

    if (!expectedPhotoDir) {
        QVERIFY(!photoDir);
    }
    else {
        QVERIFY(static_cast<bool>(photoDir));
        QCOMPARE(*photoDir, *expectedPhotoDir);
    }
}

QTEST_APPLESS_MAIN(TestPhotoDirectoryParser)
