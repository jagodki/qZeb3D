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


#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QHash>
#include <QString>
#include <ZebData/Rawdata/track.h>
#include <ZebData/zebfiles.h>
#include <ZebData/zebparser.h>
#include <QMessageBox>
#include <QStringList>
#include <QProgressBar>
#include <QApplication>
#include <QtDataVisualization>
#include <QtDataVisualization/QScatterDataProxy>
#include <QtDataVisualization/QScatterDataItem>
#include <QFile>
#include <QTextEdit>
#include <QTextCursor>
#include "Utilities/settings.h"
#include "ZebData/Rawdata/camera.h"
#include "PointCloud/zeb2pointcloud.h"
#include "PointCloud/pointcloud.h"

using namespace QtDataVisualization;

class Controller : public QObject {
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);

    int importSingleTrack(QString path, QTextEdit *te);
    int convertZebToPointCloud(QString trackNumber, QProgressBar *pb, int indexSensorHmp, QTextEdit *te);

    bool loadSettings();
    QString getMessage(QString key);
    QString getSetting(QString key);
    void setSetting(QString key, QString value);
    QString getDataName(QString path, QString type);

    void loadPointCloudDataArray(QString trackNumber, QScatterDataArray *dataArray);
    bool exportPointCloud(QString path, QString track, QProgressBar *pb, QTextEdit *te);
    void displayPointCloud();

private:
    QHash<QString, Track*> zebTracks;
    QHash<QString, PointCloud*> pointClouds;
    ZebFiles zebFiles;
    ZebParser zebParser;
    Settings settings;

signals:
    void finished();
    void error(QString err);

public slots:
};

#endif // CONTROLLER_H
