#ifndef BASEDEVICE_H
#define BASEDEVICE_H

#include "DeviceWidget.h"
#include "DeviceAdapter.h"
#include "DataTypes.h"

#include <QPointer>
#include <QProcess>
#include <QString>
#include <QTabWidget>
#include <QTimer>

using namespace DataTypes;

class BaseDevice : public QObject
{
    Q_OBJECT

public:
    explicit BaseDevice(QPointer<QTabWidget> parent, const QString& id, DeviceType type,
                        const QString& humanReadableName, const QString& humanReadableDescription,
                        QPointer<DeviceAdapter> deviceAdapter);
    virtual ~BaseDevice();

    void updateTabWidget();
    virtual void update() = 0;
    virtual void filterAndAddToTextEdit(const QString& line) = 0;
    void scheduleReloadTextEdit(int timeout = 500);
    void maybeAddCompletionAfterDelay();

    const QString& getHumanReadableName() const;
    const QString& getHumanReadableDescription() const;

    void setHumanReadableName(const QString& text);
    void setHumanReadableDescription(const QString& text);

    bool isOnline() const;
    void setOnline(bool online);

    const QString& getId() { return m_id; }

signals:

protected slots:
    virtual void reloadTextEdit() = 0;

protected:
    QString m_id;
    DeviceType m_type;
    QString m_humanReadableName;
    QString m_humanReadableDescription;
    bool m_online;
    QPointer<QTabWidget> m_tabWidget;
    QPointer<DeviceWidget> m_deviceWidget;
    int m_tabIndex;
    QPointer<DeviceAdapter> m_deviceAdapter;
    QString m_lastFilter;

private:
    QTimer m_reloadTextEditTimer;
};

#endif // BASEDEVICE_H
