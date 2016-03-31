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

#ifndef DEVICEFACADE_H
#define DEVICEFACADE_H

#include "DataTypes.h"

#include <QCompleter>
#include <QObject>
#include <QPointer>
#include <QStandardItemModel>
#include <QTabWidget>
#include <QTimer>
#include <QSettings>
#include <QStringList>

class DeviceWidget;

class DeviceFacade : public QObject
{
    Q_OBJECT

private:
    DataTypes::DevicesMap m_devicesMap;
    QTimer m_updateTimer;
    QTimer m_filesRemovalTimer;

    int m_visibleBlocks;
    QString m_font;
    int m_fontSize;
    bool m_fontBold;
    bool m_darkTheme;
    bool m_clearAndroidLog;
    int m_autoRemoveFilesHours;
    QStandardItemModel m_filterCompleterModel;
    QCompleter m_filterCompleter;
    QStringList m_filterCompletions;
    QString m_textEditorPath;

public:
    static const int UPDATE_FREQUENCY = 20;
    static const int LOG_REMOVAL_FREQUENCY = 30 * 60 * 1000;
    static const int MAX_FILTER_COMPLETIONS = 60;
    static const int COMPLETION_ADD_TIMEOUT = 10 * 1000;
    static const int MAX_LINES_UPDATE = 30;

    explicit DeviceFacade(QPointer<QTabWidget> parent = 0);
    ~DeviceFacade();

    void removeDeviceByTabIndex(const int index);
    void focusFilterInput();
    void markLog();
    void clearLog();
    void openLogFile();

    void start();
    void stop();
    void loadSettings(const QSettings& s);
    void saveSettings(QSettings& s);
    void allDevicesReloadText();

    inline bool isDarkTheme() const { return m_darkTheme; }
    inline bool getClearAndroidLog() const { return m_clearAndroidLog; }
    inline const QString& getFont() const { return m_font; }
    inline int getFontSize() const { return m_fontSize; }
    inline bool isFontBold() const { return m_fontBold; }
    inline int getAutoRemoveFilesHours() const { return m_autoRemoveFilesHours; }
    inline int getVisibleLines() const { return m_visibleBlocks; }
    inline const QString& getTextEditorPath() const { return m_textEditorPath; }

    inline QCompleter& getFilterCompleter() { return m_filterCompleter; }
    void addFilterAsCompletion(const QString& completionToAdd);

signals:

public slots:
    void update();
    void removeOldLogFiles();

private:
    void updateDevicesMap();
    void fixTabIndexes(const int removedTabIndex);
    QPointer<DeviceWidget> getCurrentDeviceWidget();
};

#endif // DEVICEFACADE_H