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

#ifndef POINTCLOUD_H
#define POINTCLOUD_H

#include <QObject>
#include <QVector3D>
#include <QString>
#include <QMap>
#include <QList>
#include <QStringList>

class PointCloud : public QObject
{
    Q_OBJECT
public:
    explicit PointCloud(QObject *parent = 0);

    void addPoint(QString point, int indexOfCrossProfile, int indexCrossSensor, int indexHmp);
    void addAttributeName(QString name);
    void addAttributes(QMap<int, QString> attr);

    QList<QVector3D> getPointCloud();
    QList<QString> getPointCloudAsQString();
    QList<QString> getAttributeNames();
    QString getAttribute(int index, QString attributeName);

private:
    QList<QVector3D> pointCloudVector;      //3D-points as key, value as int represents the key for attributes and pointCloudString
    QList<QString> pointCloudString;        //x;y;z;indexCrossProfil;indexCrossSensor;indexHmp
    QMap<QString, int> attributeNames;      //values for connecting the names of the attributes
    QList<QMap<int, QString>> attributes;   //outer map: key = value of attributeNames, inner map: key = value of pointCloudVector

signals:

public slots:
};

#endif // POINTCLOUD_H
