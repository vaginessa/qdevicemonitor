#ifndef ANDROIDDEVICE_H
#define ANDROIDDEVICE_H

#include "BaseDevice.h"
#include <QProcess>

using namespace DataTypes;

class AndroidDevice : public BaseDevice
{
    QProcess m_deviceInfoProcess;
    QProcess m_deviceLogProcess;

public:
    AndroidDevice(QPointer<QTabWidget> parent, const QString& id, DeviceType type,
                  const QString& humanReadableName, const QString& humanReadableDescription);
    ~AndroidDevice();
    virtual void update();

    static void addNewDevicesOfThisType(QPointer<QTabWidget> parent, DevicesMap& map);
    virtual qint64 readData(char* data, qint64 maxlen);

private:
    virtual qint64 writeData(const char* data, qint64 len);
    void updateDeviceModel();
    void startLogger();
};

#endif // ANDROIDDEVICE_H
