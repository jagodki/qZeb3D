/*
 * qZeb3D - calculating 3D-point-clouds from Georawfiles/Georohdaten of german ZEB
 * Copyright (C) 2016 Christoph Jung
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QApplication>
#include <QString>
#include <QSettings>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QHash>
#include <QResource>
#include <QTextEdit>

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = 0);
    bool loadSettings();
    QString getMessage(QString key);
    QString getSetting(QString key);
    void setSetting(QString key, QString value);

private:
    QString settingsPath;
    QString language;
    QHash<QString, QString> messages;       //key=name of the message, value=message in choosen language
    QStringList keys;
    QStringList values;

    void setMessage(QString key, QString value);
    void loadLanguage(QString path);

signals:

public slots:
};

#endif // SETTINGS_H
