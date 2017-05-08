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

#include "zebfiles.h"

ZebFiles::ZebFiles(QObject *parent) : QObject(parent) {

}

ZebFiles::~ZebFiles() {
}

/*!
 * \brief ZebFiles::findZebFiles
 * This function searches for all specific ZEB-files, which are corresponding to the given schema of the file names.
 * The given directory will be searched recursivly, i.e. inclusive all subdirectories.
 * If a file matches the given schema, it will be added to the reference of a given QStringList.
 * \param path QString of a directory, which should be scanned for ZEB-files
 * \param resultList the reference of a QStringList, where all located files will be added
 * \param fileNameSchema the schema of the file names as QString
 */
void ZebFiles::findZebFiles(QString &path, QStringList &resultList, QString fileNameSchema) {
    //get all files and directories in the given directory incl. all subdirectories
    QDirIterator it(path, QDirIterator::Subdirectories);

    //starting the loop for finding tp1a-data (incl. files in all subdirectories)
    while(it.hasNext()) {
        //get full path and name of the current entry
        QString currentPath = it.next();
        QString currentFileName = it.fileName();

        //check the file name against the ZEB-format
        if(QRegExp(fileNameSchema).exactMatch(currentFileName)) {
            resultList << currentPath;
        }
    }
}

void ZebFiles::findTP1aGeoRawFiles(QString &path, QStringList &tp1aFiles) {
    this->findZebFiles(path, tp1aFiles, this->nameSchemaTp1aGeo);
    this->findZebFiles(path, tp1aFiles, this->nameSchemaTp1aGeoNotCorrect);
}

void ZebFiles::findTP1bGeoRawFiles(QString &path, QStringList &tp1bFiles) {
    this->findZebFiles(path, tp1bFiles, this->nameSchemaTp1bGeo);
    this->findZebFiles(path, tp1bFiles, this->nameSchemaTp1bGeoNotCorrect);
}

void ZebFiles::findTP3GeoRawFiles(QString &path, QStringList &tp3Files) {
    this->findZebFiles(path, tp3Files, this->nameSchemaTp3Geo);
    this->findZebFiles(path, tp3Files, this->nameSchemaTp3GeoNotCorrect);
}

void ZebFiles::findTP1aRasterRawFiles(QString &path, QStringList &tp1aFiles) {
    this->findZebFiles(path, tp1aFiles, this->nameSchemaTp1aRaster);
    this->findZebFiles(path, tp1aFiles, this->nameSchemaTp1aRasterNotCorrect);
}

void ZebFiles::findTP1bRasterRawFiles(QString &path, QStringList &tp1bFiles) {
    this->findZebFiles(path, tp1bFiles, this->nameSchemaTp1bRaster);
    this->findZebFiles(path, tp1bFiles, this->nameSchemaTp1bRasterNotCorrect);
}

void ZebFiles::findTP3RasterRawFiles(QString &path, QStringList &tp3Files) {
    this->findZebFiles(path, tp3Files, this->nameSchemaTp3Raster);
    this->findZebFiles(path, tp3Files, this->nameSchemaTp3RasterNotCorrect);
}

/*!
 * \brief This function extracts the track-numbre of the given ZEB-file.
 * The track-number is an alpha-numeric string with a length of 8.
 * \param path absolute path as QString of a ZEB-file
 * \return a QString-object, which contains the track-numbre of the given ZEB-file
 */
QString ZebFiles::getTrackNumber(QString &path) {
    QString fileName = QFileInfo(QFile(path).fileName()).fileName();
    return fileName.mid(4,8);
}

/*!
 * \brief This function extracts the prefix of a ZEB-file.
 * The prefix contains the information about the kind of ZEB-data (geo- or raster-orienteted) in the first character (G or R)
 * The second and third characters belongs together.
 * This two characters are number from 1 up to 16 and representing the code for a german country.
 * \param path absolute path as QString of a ZEB-file
 * \return a QString-object with length of 3 with information from the description above
 */
QString ZebFiles::getZebPrefix(QString &path) {
    QString fileName = QFileInfo(QFile(path).fileName()).fileName();
    return fileName.left(3);
}

/*!
 * \brief This function is for searching the corresponding files to a given file of one measurement.
 * One ZEB-track will be described by 3 files (for this software).
 * The three files have the same country-code and the same track-numbre.
 * With this information, the missing two files will be found in the given directory.
 * It is mandatory, that all three files are within the same directory, subdirectories will be untouched.
 * \param zebPath absolute path as QString of the ZEB-file, which was selected
 * \param tp1a QString for storing the absolute path of the TP1a-file
 * \param tp1b QString for storing the absolute path of the TP1b-file
 * \param tp3 QString for storing the absolute path of the TP3-file
 */
bool ZebFiles::getCorrespondingFiles(QString &zebPath, QString &tp1a, QString &tp1b, QString &tp3) {
    //first get prefix, track-number and TP of the given zeb-file
    QString prefix = this->getZebPrefix(zebPath);
    QString trackNumber = this->getTrackNumber(zebPath);
    QString tp = this->getTP(zebPath);

    //second get the directory where we have to search
    QString searchingDirectory = QFileInfo(zebPath).dir().absolutePath();

    //third create the strings for searching the ZEB-files
    QString tp1aCorrect = prefix + "_" + trackNumber + "_" + "T1a_";
    QString tp1aUncorrect = prefix + "_" + trackNumber + "_" + "TP1a_";
    QString tp1bCorrect = prefix + "_" + trackNumber + "_" + "T1b_";
    QString tp1bUncorrect = prefix + "_" + trackNumber + "_" + "TP1b_";
    QString tp3Correct = prefix + "_" + trackNumber + "_" + "T3_";
    QString tp3Uncorrect = prefix + "_" + trackNumber + "_" + "TP3_";

    //now searching the other two files depending on the type of the given file
    QDirIterator it(searchingDirectory);

    if(tp == "TP1a" || tp == "T1a_") {
        tp1a = zebPath;
        while(it.hasNext()) {
            QString currentPath = it.next();
            QString currentFileName = it.fileName();
            if(currentFileName.contains(tp1bCorrect, Qt::CaseSensitive) || currentFileName.contains(tp1bUncorrect, Qt::CaseSensitive)) {
                tp1b = currentPath;
            } else if(currentFileName.contains(tp3Correct, Qt::CaseSensitive) || currentFileName.contains(tp3Uncorrect, Qt::CaseSensitive)) {
                tp3 = currentPath;
            }
        }
    } else if(tp == "TP1b" || tp == "T1b_") {
        tp1b = zebPath;
        while(it.hasNext()) {
            QString currentPath = it.next();
            QString currentFileName = it.fileName();
            if(currentFileName.contains(tp1aCorrect, Qt::CaseSensitive) || currentFileName.contains(tp1aUncorrect, Qt::CaseSensitive)) {
                tp1a = currentPath;
            } else if(currentFileName.contains(tp3Correct, Qt::CaseSensitive) || currentFileName.contains(tp3Uncorrect, Qt::CaseSensitive)) {
                tp3 = currentPath;
            }
        }
    } else if(tp == "TP3_" || tp.startsWith("T3_")) {
        tp3 = zebPath;
        while(it.hasNext()) {
            QString currentPath = it.next();
            QString currentFileName = it.fileName();
            if(currentFileName.contains(tp1aCorrect, Qt::CaseSensitive) || currentFileName.contains(tp1aUncorrect, Qt::CaseSensitive)) {
                tp1a = currentPath;
            } else if(currentFileName.contains(tp1bCorrect, Qt::CaseSensitive) || currentFileName.contains(tp1bUncorrect, Qt::CaseSensitive)) {
                tp1b = currentPath;
            }
        }
    } else {
        return false;
    }

    return true;
}

/*!
 * \brief This function extracts the number of the TP from a given ZEB-file.
 * The ZEB-file have to be named by its absolute path as QString.
 * The function returns a QString with a length of 4.
 * If the file is named correctly, the function returns the following statements: T1a_, T1b_, T3_ (and one additional character).
 * \param path absolute path as QString of the ZEB-file
 * \return a QString with information about the TP (see description above)
 */
QString ZebFiles::getTP(QString &path) {
    QString fileName = QFileInfo(QFile(path).fileName()).fileName();
    return fileName.mid(13,4);
}
