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

#include "pointcloud.h"

PointCloud::PointCloud(QObject *parent) : QObject(parent) {

}

/*!
 * \brief PointCloud::addPoint
 * This function stores a 3D-point with string and float value.
 * Besides the string values, information about indices of HMP and crossprofile will be stored too.
 * This information can be helpful for further analysis.
 * \param point the 3D-point as QString, values have to be separeted by semicolon
 * \param indexOfCrossProfile the index of the cross profil which contains the given 3D-point
 * \param indexCrossSensor the index of the sensor along the cross beam which is corresponding to the 3D-point
 * \param indexHmp index of the hmp which contains the 3D-point
 */
void PointCloud::addPoint(QString point, int indexOfCrossProfile, int indexCrossSensor, int indexHmp) {
    QStringList coords = point.split(";");
    if(coords.size() == 3) {
        float x = coords.at(0).toFloat();
        float y = coords.at(1).toFloat();
        float z = coords.at(2).toFloat();

        this->pointCloudVector.append(QVector3D(x, y, z));
        this->pointCloudString.append(point + ";" + QString::number(indexOfCrossProfile) +
                                      ";" + QString::number(indexCrossSensor) + ";" + QString::number(indexHmp));
    }
}

/*!
 * \brief PointCloud::addAttributeName
 * This function adds the name of an attribute to a list.
 * If the attr-name already exists, an index will be added after the name (e.g. attrName_1)
 * \param name QString containing the name of the attribute
 */
void PointCloud::addAttributeName(QString name) {
    if(!this->attributeNames.contains(name)) {
        this->attributeNames.insert(name, this->attributeNames.size());
    } else {
        int i = 1;
        bool loop = true;
        while(loop) {
            if(!this->attributeNames.contains(name + "_" + i)) {
                this->attributeNames.insert(name + "_" + i, this->attributeNames.size());
                loop = false;
            } else {
                i++;
            }
        }
    }
}

void PointCloud::addAttributes(QMap<int, QString> attr) {
    this->attributes.append(attr);
}

QList<QVector3D> PointCloud::getPointCloud() {
    return this->pointCloudVector;
}

QList<QString> PointCloud::getPointCloudAsQString() {
    return this->pointCloudString;
}

QList<QString> PointCloud::getAttributeNames() {
    return this->attributeNames.keys();
}

QString PointCloud::getAttribute(int index, QString attributeName) {
    return this->attributes.value(index).value(this->attributeNames.value(attributeName));
}
