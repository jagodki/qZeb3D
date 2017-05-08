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

#ifndef ZEB2POINTCLOUD_H
#define ZEB2POINTCLOUD_H

#include <QObject>
#include <QList>
#include <QtMath>
#include <QMap>
#include <QList>
#include <QTextEdit>
#include <QTextCursor>

class Zeb2PointCloud : public QObject
{
    Q_OBJECT
public:
    explicit Zeb2PointCloud(QObject *parent = 0);

    double get3dDistance(QString p1, QString p2);
    double get2dDistance(QString p1, QString p2);
    QString getPointInDirection(QString p1, QString p2, double distanceMultiplicator);
    QString getPointCrossingDirection(QString p1,
                                      QString p2,
                                      QString p3,
                                      double distanceCrossValue,
                                      int distanceLongValue, double crossDepth, double offset);
    QString get3dPointWithMeasuredHeight(QString p1, QString transverseValue, double offset);
    void synchroniseLfdmValues(QList<QString> listCoords1, QList<QString> listCoords2,
                               int &startIndex1, int &startIndex2);


signals:

public slots:
};

#endif // ZEB2POINTCLOUD_H
