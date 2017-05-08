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

#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QMap>
#include <QList>
#include <QVector3D>

/**
 * @brief The Pictures class. This class contains
 * information about the cameras from the ZEB-header
 * in XML-rawdata. Just one camera per track is stored
 * in this class. Additionally all picctures of this
 * camera, which can be found in the XML document,
 * are stored in this class too.
 */
class Camera : public QObject {
    Q_OBJECT
public:
    explicit Camera(QObject *parent = 0);
    void setRootDirectory(QString newRootDirectory);
    void setPixelH(int ph);
    void setPixelV(int pv);
    QString getRootDirectory();
    int getPixelH();
    int getPixelV();

    QString getCamName() const;
    void setCamName(const QString &value);

    QString getCamNumber() const;
    void setCamNumber(const QString &value);

    QList<QString> getPictures();
    void addPicture(QString value);

    int getFrequency() const;
    void setFrequency(int value);

private:
    QString rootDirectory;
    int pixelH;
    int pixelV;
    int frequency;
    QString camNumber;
    QString camName;
    QList<QString> pictures;    //<timestamp, picturename>
    QList<QVector3D> coordinates;   //timestamp, coordinates (lon, lat, height)


signals:

public slots:
};

#endif // PICTURES_H
