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

#ifndef ZEBFILES_H
#define ZEBFILES_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QStringList>
#include <QDir>
#include <QListIterator>
#include <QFile>
#include <QFileInfo>
#include <QDirIterator>
#include <QRegExp>
#include "Rawdata/track.h"

/*!
 * \brief The ZebFiles class
 * This class provides functions for finding ZEB-files
 * and parsing their information into objects of the
 * package named Rawdata.
 */
class ZebFiles : public QObject {
    Q_OBJECT
public:
    explicit ZebFiles(QObject *parent = 0);
    ~ZebFiles();

    /*!
     * \brief findTP1aGeoRawFiles
     * \param path
     * \param tp1aFiles
     */
    void findTP1aGeoRawFiles(QString &path, QStringList &tp1aFiles);
    void findTP1bGeoRawFiles(QString &path, QStringList &tp1bFiles);
    void findTP3GeoRawFiles(QString &path, QStringList &tp3Files);

    void findTP1aRasterRawFiles(QString &path, QStringList &tp1aFiles);
    void findTP1bRasterRawFiles(QString &path, QStringList &tp1aFiles);
    void findTP3RasterRawFiles(QString &path, QStringList &tp1aFiles);

    QString getTrackNumber(QString &path);
    QString getZebPrefix(QString &path);
    QString getTP(QString &path);
    bool getCorrespondingFiles(QString &zebPath, QString &tp1a, QString &tp1b, QString &tp3);

    void parseTP1aGeoRawFiles(QString &path, bool admindata, Track &track);
    void parseTP1bGeoRawFiles(QString &path, bool admindata, Track &Track);
    void parseTP3GeoRawFiles(QString &path, bool admindata, Track &track);

 private:
    QString const nameSchemaTp1aGeo = "G.{1}.{1}_.{1}.{1}.{1}.{1}.{1}.{1}.{1}.{1}_T1a.*\\.xml";
    QString const nameSchemaTp1bGeo = "G.{1}.{1}_.{1}.{1}.{1}.{1}.{1}.{1}.{1}.{1}_T1b.*\\.xml";
    QString const nameSchemaTp3Geo = "G.{1}.{1}_.{1}.{1}.{1}.{1}.{1}.{1}.{1}.{1}_T3.*\\.xml";

    QString const nameSchemaTp1aGeoNotCorrect = "G.{1}.{1}_.{1}.{1}.{1}.{1}.{1}.{1}.{1}.{1}_TP1a.*\\.xml";
    QString const nameSchemaTp1bGeoNotCorrect = "G.{1}.{1}_.{1}.{1}.{1}.{1}.{1}.{1}.{1}.{1}_TP1b.*\\.xml";
    QString const nameSchemaTp3GeoNotCorrect = "G.{1}.{1}_.{1}.{1}.{1}.{1}.{1}.{1}.{1}.{1}_TP3.*\\.xml";

    QString const nameSchemaTp1aRaster = "N.{1}.{1}.{1}.{1}.{1}.{1}.{1}.{1}.{1}.{1}.{1}_.{1}.{1}_T1a.*\\.xml";
    QString const nameSchemaTp1bRaster = "N.{1}.{1}.{1}.{1}.{1}.{1}.{1}.{1}.{1}.{1}.{1}_.{1}.{1}_T1b.*\\.xml";
    QString const nameSchemaTp3Raster = "N.{1}.{1}.{1}.{1}.{1}.{1}.{1}.{1}.{1}.{1}.{1}_.{1}.{1}_T3.*\\.xml";

    QString const nameSchemaTp1aRasterNotCorrect = "N.{1}.{1}.{1}.{1}.{1}.{1}.{1}.{1}.{1}.{1}.{1}_.{1}.{1}_TP1a.*\\.xml";
    QString const nameSchemaTp1bRasterNotCorrect = "N.{1}.{1}.{1}.{1}.{1}.{1}.{1}.{1}.{1}.{1}.{1}_.{1}.{1}_TP1b.*\\.xml";
    QString const nameSchemaTp3RasterNotCorrect = "N.{1}.{1}.{1}.{1}.{1}.{1}.{1}.{1}.{1}.{1}.{1}_.{1}.{1}_TP3.*\\.xml";

    void findZebFiles(QString &path, QStringList &resultList, QString fileNameSchema);

signals:

public slots:
};

#endif // ZEBFILES_H
