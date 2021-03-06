/*
    This file is part of QDeviceMonitor.

    QDeviceMonitor is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    QDeviceMonitor is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with QDeviceMonitor. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TESTRINGBUFFER_h
#define TESTRINGBUFFER_h

#include <QtTest/QtTest>
#include <QObject>
#include <QString>
#include "../StringRingBuffer.h"

class TestStringRingBuffer : public QObject
{
    Q_OBJECT

private slots:
    void testCapacity()
    {
        const size_t n = 3;
        StringRingBuffer buf(n);
        QCOMPARE(buf.getCapacity(), n);
    }

    void testIterator()
    {
        StringRingBuffer buf(3);
        buf.push("a");
        buf.push("b");

        auto it = buf.constBegin();
        QCOMPARE(it.isValid(), true);
        QCOMPARE(*it, QString("a"));
        QCOMPARE(it.hasNext(), true);
        it++;
        QCOMPARE(it.isValid(), true);
        QCOMPARE(*it, QString("b"));
        QCOMPARE(it.hasNext(), false);
        it++;
        QCOMPARE(it.isValid(), false);

        buf.push("c");
        buf.push("d");
        it = buf.constBegin();
        QCOMPARE(it.isValid(), true);
        QCOMPARE(*it, QString("b"));
        QCOMPARE(it.hasNext(), true);
        it++;
        QCOMPARE(it.isValid(), true);
        QCOMPARE(*it, QString("c"));
        QCOMPARE(it.hasNext(), true);
        it++;
        QCOMPARE(it.isValid(), true);
        QCOMPARE(*it, QString("d"));
        QCOMPARE(it.hasNext(), false);
        it++;
        QCOMPARE(it.isValid(), false);
    }
};

#endif
