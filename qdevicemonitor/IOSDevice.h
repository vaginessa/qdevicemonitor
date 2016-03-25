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

#ifndef IOSDEVICE_H
#define IOSDEVICE_H

#include "BaseDevice.h"
#include <QFile>
#include <QProcess>
#include <QStringList>
#include <QTextStream>

using namespace DataTypes;

class IOSDevice : public BaseDevice
{
    Q_OBJECT

    QProcess m_deviceInfoProcess;
    QProcess m_deviceLogProcess;
    QFile m_deviceLogFile;
    QSharedPointer<QTextStream> m_deviceLogFileStream;
    bool m_didReadDeviceModel;

public:
    explicit IOSDevice(QPointer<QTabWidget> parent, const QString& id, const DeviceType type,
                       const QString& humanReadableName, const QString& humanReadableDescription,
                       QPointer<DeviceAdapter> deviceAdapter);
    ~IOSDevice() override;
    void update() override;
    void filterAndAddToTextEdit(const QString& line) override;
    const char* getPlatformString() const override { return getPlatformStringStatic(); }
    void reloadTextEdit() override;

    static void updateDeviceStatus(const QString& deviceStatus, BaseDevice& device, const QString& deviceId);
    static void maybeAddNewDevicesOfThisType(QPointer<QTabWidget> parent, DevicesMap& map, QPointer<DeviceAdapter> deviceAdapter);
    static void releaseTempBuffer();
    static void stopDevicesListProcess();
    static void removedDeviceByTabClose(const QString& id);

private:
    void stopDeviceInfoProcess();
    void updateDeviceModel();
    void startLogger();
    void stopLogger();
    void checkFilters(bool& filtersMatch, bool& filtersValid, const QStringRef& text);

    static const char* getPlatformStringStatic() { return "iOS"; }

private slots:
    void readStandardError();
};

#endif // ANDROIDDEVICE_H
