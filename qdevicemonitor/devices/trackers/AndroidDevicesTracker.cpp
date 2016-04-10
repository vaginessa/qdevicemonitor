#include "AndroidDevicesTracker.h"

#include <QDebug>

AndroidDevicesTracker::AndroidDevicesTracker()
{
    m_codecStream.setCodec("UTF-8");
    m_codecStream.setString(&m_buffer, QIODevice::ReadWrite | QIODevice::Text);
}

AndroidDevicesTracker::~AndroidDevicesTracker()
{
    stopListProcess();
}

void AndroidDevicesTracker::update()
{
    if (m_listProcess.state() == QProcess::NotRunning)
    {
        updateConnectedDevices();
        stopListProcess();
        startListProcess();
    }
}

void AndroidDevicesTracker::startListProcess()
{
    QStringList args;
    args.append("devices");
    m_listProcess.setReadChannel(QProcess::StandardOutput);
    m_listProcess.start("adb", args);
}

void AndroidDevicesTracker::stopListProcess()
{
    if (m_listProcess.state() != QProcess::NotRunning)
    {
        m_listProcess.terminate();
        m_listProcess.kill();
        m_listProcess.close();
    }
}

void AndroidDevicesTracker::updateConnectedDevices()
{
    updateNextConnectedDevices();
    updateDisconnectedDevices();

    m_connectedDevices = m_nextConnectedDevices;
}

/*
    if (s_devicesListProcess.canReadLine())
    {
        *s_tempStream << s_devicesListProcess.readAll();

        QString line;
        while (!s_tempStream->atEnd())
        {
            const bool lineIsRead = s_tempStream->readLineInto(&line);
            if (!lineIsRead)
            {
                break;
            }
            else if (line.contains("List of devices attached"))
            {
                continue;
            }

            // TODO: replace split with splitRef
            const QStringList lineSplit = line.split('\t');
            if (lineSplit.count() >= 2)
            {
                const QString& deviceId = lineSplit[0];
                const QString& deviceStatus = lineSplit[1];
                //qDebug() << "deviceId" << deviceId << "; deviceStatus" << deviceStatus;
*/

void AndroidDevicesTracker::updateNextConnectedDevices()
{
    m_nextConnectedDevices.clear();

    if (m_listProcess.canReadLine())
    {
        m_codecStream << m_listProcess.readAll();
    }

    QString line;
    while (!m_codecStream.atEnd())
    {
        const bool lineIsRead = m_codecStream.readLineInto(&line);
        if (!lineIsRead)
        {
            break;
        }
        else if (line.contains("List of devices attached"))
        {
            continue;
        }

        // TODO: replace split with splitRef
        const QStringList lineSplit = line.split('\t');
        if (lineSplit.count() >= 2)
        {
            const QString& deviceId = lineSplit[0];
            const QString& deviceStatus = lineSplit[1];
            const bool online = deviceStatus == "device";

            if (!online)
            {
                continue;
            }

            if (!m_connectedDevices.contains(deviceId))
            {
                emit deviceConnected(DataTypes::DeviceType::Android, deviceId);
            }

            m_nextConnectedDevices.insert(deviceId);
        }
    }
}

void AndroidDevicesTracker::updateDisconnectedDevices()
{
    const auto disconnectedDevices = m_connectedDevices - m_nextConnectedDevices;
    for (auto it = disconnectedDevices.constBegin(); it != disconnectedDevices.constEnd(); ++it)
    {
        emit deviceDisconnected(DataTypes::DeviceType::Android, *it);
    }
}