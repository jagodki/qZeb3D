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

#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent) {
}

/*!
 * \brief Controller::importSingleTrack
 * This function imports a single track given by the path to one ZEB-file.
 * \param path absolute path as QString to a single zeb-file
 * \return returns an integer value with the following expression
 * \return  0 = all threeh files imported without problems
 * \return -1 = no TP3-file could be found in the given directory, but TP1a and TP1b were imported
 * \return -2 = not TP1a or TP1b could be found, import cancelled
 * \return -3 = import of TP1a was not successfull, import cancelled
 * \return -4 = import of TP1b was not successfull, import cancelled
 * \return -5 = import of TP3 was not successfull, but TP1a and TP1b were imported
 */
int Controller::importSingleTrack(QString path, QTextEdit *te) {
    //log information
    te->insertPlainText(QDateTime::currentDateTimeUtc().toString() + " - " + this->getMessage("startingimport") + "\n");
    QTextCursor c = te->textCursor();
    c.movePosition(QTextCursor::End);
    te->setTextCursor(c);

    int result;

    //find the three zeb-files, which are corresponding to the given path
    QString tp1aPath;
    QString tp1bPath;
    QString tp3Path;
    this->zebFiles.getCorrespondingFiles(path, tp1aPath, tp1bPath, tp3Path);

    //check, if any ZEB-file could not be found
    if(tp1aPath == "" || tp1bPath == "") {
        return -2;
    }
    if(tp3Path == "") {
        result = -1;
    } else {
        result = 0;
    }

    //get the key of the current track and create a new Track-object
    QString trackKey = this->getDataName(tp1aPath, "zeb");
    Track *track = new Track();

    //import TP1a
    bool tp1aImportResult = this->zebParser.parseXml(
                tp1aPath, track, te, this->getMessage("thefileisnotazebfile"),
                this->getMessage("parsingfilehasstarted") + " ", this->getMessage("parsingfilefinished") + "");
    if(!tp1aImportResult) {
        return -3;
    }

    //import TP1b
    bool tp1bImportResult = this->zebParser.parseXml(
                tp1bPath, track, te, this->getMessage("thefileisnotazebfile"),
                this->getMessage("parsingfilehasstarted") + " ", this->getMessage("parsingfilefinished") + "");
    if(!tp1bImportResult) {
        return -4;
    }

    //import TP3
    if(result == 0) {
        bool tp3ImportResult = this->zebParser.parseXml(
                    tp3Path, track, te, this->getMessage("thefileisnotazebfile"),
                    this->getMessage("parsingfilehasstarted") + " ", this->getMessage("parsingfilefinished") + "");
        if(!tp3ImportResult) {
            result = -5;
        }
    }

    this->zebTracks.insert(trackKey, track);
    te->insertPlainText(QDateTime::currentDateTimeUtc().toString() + " - " + this->getMessage("importfinished") + "\n");
    c = te->textCursor();
    c.movePosition(QTextCursor::End);
    te->setTextCursor(c);
    return result;
}

/*!
 * \brief Controller::loadSettings
 * This function calls a function for loading the settings- and translation-file.
 * \return true if all was correct, otherwise false
 */
bool Controller::loadSettings() {
    return this->settings.loadSettings();
}

/*!
 * \brief Controller::getMessage
 * This function gets the text of a message corresponding to the selected language,
 * \param key identifier of the message-text
 * \return the whole message as QString
 */
QString Controller::getMessage(QString key) {
    return settings.getMessage(key);
}

/*!
 * \brief Controller::convertZebToPointCloud
 * This function converts an imported ZEB-track into a 3D-pointcloud.
 * \param trackNumber number of the track as QString for identifying the track
 * \param pb the progressbar from the gui
 * \param indexSensorHmp the integer of the transverse beam crossing the HMP, starting by one at the right side in driving direction
 * \return 0 in every cases (no additional error handling implemented yet)
 */
int Controller::convertZebToPointCloud(QString trackNumber, QProgressBar *pb, int indexSensorHmp, QTextEdit *te) {
    te->insertPlainText(QDateTime::currentDateTimeUtc().toString() + " - " + this->getMessage("computingofpointcloudstarted") + "\n");
    QTextCursor c = te->textCursor();
    c.movePosition(QTextCursor::End);
    te->setTextCursor(c);

    //create new Zeb2PointCloud-object to access all needed functions
    Zeb2PointCloud *z2pc = new Zeb2PointCloud();

    //create a new pointcloud-object
    PointCloud *pc = new PointCloud();

    //get the measurements and the track
    Track *track = this->zebTracks.value(trackNumber);
    Longitudinal *longitudinal = this->zebTracks.value(trackNumber)->getLongitudinalMeasurement();
    Transverse *transverse = this->zebTracks.value(trackNumber)->getTransverseMeasurement();

    //init progressbar
    pb->setValue(0);
    pb->setMaximum(longitudinal->getHmp().size());

    //extract the frequencys of TP1a and Tp1b
    double frequency1a = track->getLongitudinalMeasurement()->getFrequencyMeasurementValues();
    int frequency1b = track->getTransverseMeasurement()->getFrequencyMeasurementValues();

    //synchronise the starting lfdm values
    int index1a = 0;
    int index1b = 0;

    //distance-werte sollten strings sein
    z2pc->synchroniseLfdmValues(longitudinal->getCoordinates(), transverse->getCoordinates(), index1a, index1b);

    //compare both frequencys
    if(frequency1a <= frequency1b) {
        int sizeOfCoords = longitudinal->getCoordinates().size();

        //loop over tp1a
        while((index1a + 1) < sizeOfCoords) {
            //get 2 following coords of the lower frequency
            QString firstPointLowerFrequency = longitudinal->getCoordinates()[index1a];
            QString secondPointLowerFrequency = longitudinal->getCoordinates()[index1a + 1];

            //get the information about the distance between first and second point in metres
            int distanceMetres = longitudinal->getLfdm().at(index1a + 1) - longitudinal->getLfdm().at(index1a);

            //get the ratio of frequency between values of hmp and coordinates
            double frequencyRatio = longitudinal->getFrequencyMeasurementValues() / distanceMetres;

            //get the frequency of measurement values of the lower frequency for our inner loop
            double distanceMultiplicated = 0.0;
            int iterator = 0;

            //loop over tp1a within two following cross profiles
            while(iterator < 100) {
                //get the coordinates for the current index in driving direction
                QString currentPointDrivingDirection = z2pc->getPointInDirection(
                            firstPointLowerFrequency, secondPointLowerFrequency, distanceMultiplicated);

                //get the crossing profile and iterate over them
                QStringList profileList = transverse->getProfiles().at(index1b).split(";");

                //get the offset between hmp and cross beam
                double hmpHeight = longitudinal->getHmp().at(index1a * 100 + iterator).toDouble();
                double offsetCrossProfileHmp = profileList.at(indexSensorHmp).toDouble() - hmpHeight;

                //loop over the sensors of the cross beam
                for(int i = 0; i < profileList.size(); i++) {
                    if(profileList.at(i) == "X") {
                        continue;
                    }

                    //get the information for calculating the correct height
                    double crossProfileHeight = profileList.at(i).toDouble();

                    //get the distance of the current sensor to the zero-sensor
                    double sensorPosition = transverse->getSensors().value(i + 1);

                    //get the coordinates for the searched point in crossing direction
                    QString currentPointCrossingDirection = z2pc->getPointCrossingDirection(
                                currentPointDrivingDirection, secondPointLowerFrequency,
                                firstPointLowerFrequency, sensorPosition, distanceMetres,
                                crossProfileHeight, offsetCrossProfileHmp);

                    //add the received point to the pointcloud
                    pc->addPoint(currentPointCrossingDirection, index1b, index1a * 100 + iterator, i);
                }
                //increase the iterators
                distanceMultiplicated += frequencyRatio;
                iterator += 1;

                //increase the progressbar
                pb->setValue(pb->value() + 1);
                qApp->processEvents();
            }
            index1a += 1;
            index1b += 1;
        }
    } else {
        //at this point code could be written if frequency1a > frequency1b (the absolute numbers)
    }
    //add the pointcloud-object to the corresponding  hashmap
    this->pointClouds.insert(trackNumber, pc);
    te->insertPlainText(QDateTime::currentDateTimeUtc().toString() + " - " + this->getMessage("pointcloudcreated") + "\n");
    c = te->textCursor();
    c.movePosition(QTextCursor::End);
    te->setTextCursor(c);
    return 0;
}

/*!
 * \brief Controller::getDataName
 * Returns the name of the ZEB-file (CountryCode_MeasurementNumber) from a given path.
 * \param path QString of a path of a zeb-file
 * \param type data type as QString (just "zeb" is already supported)
 * \return the data name as QString
 */
QString Controller::getDataName(QString path, QString type) {
    QString dataName;
    if(type == "zeb") {
        dataName = zebFiles.getZebPrefix(path) + "_" + zebFiles.getTrackNumber(path);
    }
    return dataName;
}

/*!
 * \brief Controller::loadPointCloudDataArray
 * This function loads the pointcloud data into the GUI.
 * \param trackNumber identifier of a track as QString
 * \param dataArray QScatterDataArray for storing the 3D-data in a Scatter-object
 */
void Controller::loadPointCloudDataArray(QString trackNumber, QScatterDataArray *dataArray) {
    //get the needed pointcloud
    QList<QVector3D> pc = this->pointClouds.value(trackNumber)->getPointCloud();

    //get the size of the needed pointcloud
    int pcSize = pc.size();

    //populate the data-array
    dataArray->resize(pc.size());
    QScatterDataItem *ptrToDataArray = &dataArray->first();
    for(int i = 0; i < pcSize; i++) {
        ptrToDataArray->setPosition(QVector3D(pc.at(i).y(), pc.at(i).z(), pc.at(i).x()));
        ptrToDataArray++;
    }
}

/*!
 * \brief Controller::exportPointCloud
 * Exports the pointcloud of a selected track into a text file.
 * \param path QString of the destination of the export
 * \param track QString as identifier of the selected track
 * \param pb progressbar for displaying the progress
 * \return true if all was correct, otherwise false
 */
bool Controller::exportPointCloud(QString path, QString track, QProgressBar *pb, QTextEdit *te) {
    te->insertPlainText(QDateTime::currentDateTimeUtc().toString() + " - " + this->getMessage("exportofpointcloudhasstarted") + "\n");
    QTextCursor c = te->textCursor();
    c.movePosition(QTextCursor::End);
    te->setTextCursor(c);

    //get the point cloud as QString-data
    QList<QString> pc = this->pointClouds.value(track)->getPointCloudAsQString();
    int pcSize = pc.size();

    //set up progressbar
    pb->setValue(0);
    pb->setMaximum(pcSize);

    //write data
    QFile fOut(path);
    if (fOut.open(QFile::WriteOnly | QFile::Text)) {
      QTextStream s(&fOut);
      s << "x;y;z;indexCrossProfile;indexHmp;indexCrossSensor" << '\n';
      for (int i = 0; i < pc.size(); ++i) {
        s << pc.at(i) << '\n';
        pb->setValue(pb->value() + 1);
        qApp->processEvents();
      }
    } else {
      return false;
    }
    fOut.close();
    te->insertPlainText(QDateTime::currentDateTimeUtc().toString() + " - " + this->getMessage("exportofpointcloudfinished") + "\n");
    c = te->textCursor();
    c.movePosition(QTextCursor::End);
    te->setTextCursor(c);
    return true;
}

/*!
 * \brief Controller::getSetting
 * This function calls another function for getting a needed setting
 * \param key the identifier as QString of a needed property
 * \return the corresponding value as QString
 */
QString Controller::getSetting(QString key) {
    return this->settings.getSetting(key);
}

/*!
 * \brief Controller::setSetting
 * This function calls another function for inserting a property
 * \param key the identifier as QString of a needed property
 * \param value the corresponding value as QString of the needed property
 */
void Controller::setSetting(QString key, QString value) {
    return this->settings.setSetting(key, value);
}
