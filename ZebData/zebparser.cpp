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

#include "zebparser.h"

ZebParser::ZebParser() {

}

ZebParser::~ZebParser() {
}

bool ZebParser::startElement(const QString &namespaceURI,
                             const QString &localName,
                             const QString &qName,
                             const QXmlAttributes &atts) {

}

bool ZebParser::endElement(const QString &namespaceURI,
                           const QString &localName,
                           const QString &qName) {

}

bool ZebParser::characters(const QString &str) {

}

bool ZebParser::fatalError(const QXmlParseException &exception) {

}

QString ZebParser::errorString() const {
    return QObject::tr("%1\nLine %2, column %3")
            .arg(xml.errorString())
            .arg(xml.lineNumber())
            .arg(xml.columnNumber());
    //return errorStr;
}

/*!
 * \brief ZebParser::parseXml
 * This function starts the parsing of a ZEB-file in XML-format.
 * The name of the file is not used, but the xml-file have to be valid.
 * The kind of a ZEB-track is extracted by the XML-name.
 * \param xmlPath the absolute path as QString to a ZEB-file
 * \param track a Track-object, where the content will be stored
 * \param te a pointer to a QTextEdit for logging information
 * \return true if all was correct, otherwise false
 */
bool ZebParser::parseXml(QString xmlPath, Track *track, QTextEdit *te, QString errorMessage, QString startMessage, QString endMessage) {
    te->insertPlainText(QDateTime::currentDateTimeUtc().toString() + " - " + startMessage + xmlPath + "\n");
    QTextCursor c = te->textCursor();
    c.movePosition(QTextCursor::End);
    te->setTextCursor(c);

    //parsing the XML-file
    QFile xmlFile(xmlPath);
    xmlFile.open(QFile::ReadOnly | QFile::Text);
    this->xml.setDevice(&xmlFile);

    //es muss noch geschaut werden, ob im Track-Objekt schon TPs gesetzt sind

    //check the start-element of the XML-file and call the corresponding function
    if(this->xml.readNextStartElement()) {
        if(xml.name() == "RohdatenTP1aGeo") {
            this->readTP1a(track);
        } else if(xml.name() == "RohdatenTP1bGeo") {
            this->readTP1b(track);
        } else if(xml.name() == "RohdatenTP2Geo") {

        }else if(xml.name() == "RohdatenTP3Geo") {
            this->readTP3(track);
        } else {
            this->xml.raiseError(errorMessage);
        }
    }
    te->insertPlainText(QDateTime::currentDateTimeUtc().toString() + " - " + endMessage + xmlPath + "\n");
    c = te->textCursor();
    c.movePosition(QTextCursor::End);
    te->setTextCursor(c);
    return !this->xml.error();
}

//großes try/catch noch drum herum
//wenn Messpunktabstand = -99.99, dann muss abgebrochen und dies geloggt werden

/*!
 * \brief ZebParser::readTP1a
 * This function reads a TP1a-ZEB-file and extracts all needed information.
 * \param track a Track-object, where all information will be stored
 * \return true if all was correct, otherwise false
 */
bool ZebParser::readTP1a(Track *track) {
    Longitudinal *longitudinal = new Longitudinal();

    int maxCountOfCams = 0;
    int currentCountOfCams = 0;
    int pictureFrequence = 0;

    bool forward = false;
    bool backward = false;

    double currentDistanceValues = 0.0;
    double currentDistanceInformation = 0.0;
    double currentDistanceCurvature = 0.0;
    double currentDistanceInclination = 0.0;
    double currentDistancePictures = 0.0;

    while(!this->xml.atEnd()) {
        this->xml.readNext();
        if(this->xml.isStartElement()) {
            if(this->xml.name() == "Bildparameter") {
                this->extractDataMedium(track);
            } else if(this->xml.name() == "Messpunktabstand_Bilder") {
                int frequency = this->getFrequencyValue(xml.readElementText());
                if(frequency != -99) {
                    pictureFrequence = frequency;
                } else {
                    return false;
                }
            } else if(this->xml.name() == "Kamera") {
                //increase the maxCountOfCameras for calculate the correct distance later on
                maxCountOfCams++;
                this->initCamera(track, pictureFrequence);
            } else if(this->xml.name() == "ZEBAdministration") {
                this->initZebData(track);
            } else if(this->xml.name() == "Messparameter") {
                this->initMeasurementParametres(track);
            } else if(this->xml.name() == "Messpunktabstand_Messgeschwindigkeit") {
                int frequency = this->getFrequencyValue(xml.readElementText());
                if(frequency != -99) {
                    longitudinal->setFrequencyMeasurementInformation(frequency);
                } else {
                    return false;
                }
            } else if(this->xml.name() == "Messpunktabstand_Laengsprofil") {
                double frequency = this->getFrequencyValueAsDouble(xml.readElementText());
                if(frequency != -99.99) {
                    longitudinal->setFrequencyMeasurementValues(frequency);
                } else {
                    return false;
                }
            } else if(this->xml.name() == "Messpunktabstand_Kruemmung") {
                int frequency = this->getFrequencyValue(xml.readElementText());
                if(frequency != -99) {
                    longitudinal->setFrequencyCurvature(frequency);
                } else {
                    return false;
                }
            } else if(this->xml.name() == "Messpunktabstand_Laengsneigung") {
                int frequency = this->getFrequencyValue(xml.readElementText());
                if(frequency != -99) {
                    longitudinal->setFrequencyInclination(frequency);
                } else {
                    return false;
                }
            } else if(this->xml.name() == "Messpunktabstand_Seitenabstand") {
                int frequency = this->getFrequencyValue(xml.readElementText());
                if(frequency != -99) {
                    longitudinal->setFrequencyGapDistance(frequency);
                } else {
                    return false;
                }
            }  else if(this->xml.name() == "Messlinie") {
                longitudinal->setMeasurementLine(xml.readElementText());
            } else if(this->xml.name() == "Vorlauf") {
                forward = true;
            } else if(this->xml.name() == "R") {
                if(forward) {
                    QString a = this->getXmlAttribute("A");
                    QString l = this->getXmlAttribute("L");
                    QString k = this->getXmlAttribute("K");
                    QString elementText = xml.readElementText();
                    longitudinal->addForward(a + ";" + l + ";" + k + ";" + elementText);
                } else if(backward) {
                    QString a = this->getXmlAttribute("A");
                    QString l = this->getXmlAttribute("L");
                    QString k = this->getXmlAttribute("K");
                    QString elementText = xml.readElementText();
                    longitudinal->addBackward(a + ";" + l + ";" + k + ";" + elementText);
                } else {
                    //extract the attributes and store them
                    longitudinal->addCurvature(this->getXmlAttribute("K"));
                    longitudinal->addInclination(this->getXmlAttribute("L"));

                    //increase the distance-vars
                    currentDistanceCurvature += longitudinal->getFrequencyCurvature();
                    currentDistanceInclination += longitudinal->getFrequencyInclination();

                    //now extract the measurement values
                    QStringList values = xml.readElementText().split(" ");
                    foreach (QString value, values) {
                       longitudinal->addHmp(value);
                       currentDistanceValues += longitudinal->getFrequencyMeasurementValues();
                    }
                }
            } else if(this->xml.name() == "Datenstrom") {
                longitudinal->addVelocity(this->getXmlAttribute("V").toInt());
            } else if(this->xml.name() == "Erfassungsflag") {
                int fs = this->getXmlAttribute("FS").toInt();
                int g = this->getXmlAttribute("G").toInt();
                longitudinal->addStripe(fs);
                longitudinal->addValidity(g);
            } else if(this->xml.name() == "WGS") {
                //storing the coordinates as ;-separated QString to prevent data-loose during conversion to double or float
                QString pos = this->extractCoordinates();
                longitudinal->addCoordinates(pos);

                //get the timestamp
                QDateTime timestamp = this->extractTimestamp();
                longitudinal->addTimestamp(timestamp);

                //get and storing the lfdm-information
                int lfdm = this->getXmlAttribute("LfdM").toInt();
                longitudinal->addLfdm(lfdm);
            } else if(this->xml.name() == "Z") {
                longitudinal->addZFlags(this->getXmlAttribute("Z").toInt());
            } else if(this->xml.name() == "B") {
                QString camNumber = this->getXmlAttribute("Nr");
                foreach (Camera *cam, track->getCameras()) {
                   if(cam->getCamNumber() == camNumber) {
                       cam->addPicture(this->getXmlAttribute("D"));
                       break;
                   }
                }

                //now increase the count of current cameras and check, if all pictures for the current distance are extracted
                currentCountOfCams++;
                if(currentCountOfCams == maxCountOfCams) {
                    currentDistancePictures += pictureFrequence;
                    currentCountOfCams = 0;
                }
            } else if(this->xml.name() == "Nachlauf") {
                backward = true;
            }
        } else if(xml.isEndElement()) {
            if(this->xml.name() == "Datenstrom") {
                currentDistanceInformation += longitudinal->getFrequencyMeasurementInformation();
            } else if(this->xml.name() == "Vorlauf") {
                forward = false;
            } else if(this->xml.name() == "Nachlauf") {
                backward = false;
            }
        }
        track->setLongitudinalMeasurement(longitudinal);
    }
    return true;
}

/*!
 * \brief ZebParser::readTP1b
 * This function reads a TP1b-ZEB-file and extracts all needed information.
 * \param track a Track-object, where all information will be stored
 * \return true if all was correct, otherwise false
 */
bool ZebParser::readTP1b(Track *track) {
    Transverse *transverse = new Transverse();

    int maxCountOfCams = 0;
    int currentCountOfCams = 0;
    int pictureFrequence = 0.0;

    double currentDistanceValues = 0.0;
    double currentDistanceInformation = 0.0;
    double currentDistancePictures = 0.0;

    while(!this->xml.atEnd()) {
        this->xml.readNext();
        if(this->xml.isStartElement()) {
            if(this->xml.name() == "Bildparameter") {
                this->extractDataMedium(track);
            } else if(this->xml.name() == "Messpunktabstand_Bilder") {
                int frequency = this->getFrequencyValue(xml.readElementText());
                if(frequency != -99) {
                    pictureFrequence = frequency;
                } else {
                    return false;
                }
            } else if(this->xml.name() == "Kamera") {
                //increase the maxCountOfCameras for calculate the correct distance later on
                maxCountOfCams++;
                this->initCamera(track, pictureFrequence);
            } else if(this->xml.name() == "ZEBAdministration") {
                this->initZebData(track);
            } else if(this->xml.name() == "Messparameter") {
                this->initMeasurementParametres(track);
            } else if(this->xml.name() == "Messpunktabstand_Messgeschwindigkeit") {
                int frequency = this->getFrequencyValue(xml.readElementText());
                if(frequency != -99) {
                    transverse->setFrequencyMeasurementInformation(frequency);
                } else {
                    return false;
                }
            } else if(this->xml.name() == "Abstand_Profile_In_Laengsrichtung") {
                int frequency = this->getFrequencyValue(xml.readElementText());
                if(frequency != -99) {
                    transverse->setFrequencyMeasurementValues(frequency);
                } else {
                    return false;
                }
            } else if(this->xml.name() == "Messlinie") {
                transverse->setMeasurementLine(xml.readElementText());
            } else if(this->xml.name() == "Sonde") {
                int sensorNumber = this->getXmlAttribute("Nr").toInt();
                double sensorPosition = this->getXmlAttribute("Abst_Q").toDouble();
                transverse->addSensor(sensorNumber, sensorPosition);
            } else if(this->xml.name() == "R") {
                QString profile = xml.readElementText().replace(" ", ";");
                transverse->addProfile(profile);
                currentDistanceValues += transverse->getFrequencyMeasurementValues();
            } else if(this->xml.name() == "Datenstrom") {
                transverse->addVelocity(this->getXmlAttribute("V").toInt());
            } else if(this->xml.name() == "Erfassungsflag") {
                int fs = this->getXmlAttribute("FS").toInt();
                int g = this->getXmlAttribute("G").toInt();
                transverse->addStripe(fs);
                transverse->addValidity(g);
            } else if(this->xml.name() == "WGS") {
                //storing the coordinates as ;-separated QString to prevent data-loose during conversion to double or float
                QString pos = this->extractCoordinates();
                transverse->addCoordinate(pos);

                //get the timestamp
                QDateTime timestamp = this->extractTimestamp();
                transverse->addTimestamp(timestamp);

                //get and storing the lfdm-information
                int lfdm = this->getXmlAttribute("LfdM").toInt();
                transverse->addLfdm(lfdm);
            } else if(this->xml.name() == "Z") {
                transverse->addZFlag(this->getXmlAttribute("Z").toInt());
            } else if(this->xml.name() == "B") {
                QString camNumber = this->getXmlAttribute("Nr");
                foreach (Camera *cam, track->getCameras()) {
                   if(cam->getCamNumber() == camNumber) {
                       cam->addPicture(this->getXmlAttribute("D"));
                       break;
                   }
                }

                //now increase the count of current cameras and check, if all pictures for the current distance are extracted
                currentCountOfCams++;
                if(currentCountOfCams == maxCountOfCams) {
                    currentDistancePictures += pictureFrequence;
                    currentCountOfCams = 0;
                }
            }
        } else if(xml.isEndElement()) {
            if(this->xml.name() == "Datenstrom") {
                currentDistanceInformation += transverse->getFrequencyMeasurementInformation();
            }
        }
        track->setTransverseMeasruement(transverse);
    }
    return true;
}

/*!
 * \brief ZebParser::readTP3
 * This function reads a TP3-ZEB-file and extracts all needed information.
 * \param track a Track-object, where all information will be stored
 * \return true if all was correct, otherwise false
 */
bool ZebParser::readTP3(Track *track) {
    Damage *damage = new Damage();

    bool asphalt;
    bool concrete;
    bool cobbleStone;

    int maxCountOfCams = 0;
    int currentCountOfCams = 0;
    int pictureFrequence = 0.0;

    double currentDistanceValues = 0.0;
    int currentDistanceInformation = 0;
    double currentDistancePictures = 0.0;

    while(!this->xml.atEnd()) {
        this->xml.readNext();
        if(this->xml.isStartElement()) {
            if(this->xml.name() == "Bildparameter") {
                this->extractDataMedium(track);
            } else if(this->xml.name() == "Messpunktabstand_Bilder") {
                int frequency = this->getFrequencyValue(xml.readElementText());
                if(frequency != -99) {
                    pictureFrequence = frequency;
                    damage->setFrequencyMeasurementInformation(frequency);
                } else {
                    return false;
                }
            } else if(this->xml.name() == "Kamera") {
                //increase the maxCountOfCameras for calculate the correct distance later on
                maxCountOfCams++;
                this->initCamera(track, pictureFrequence);
            } else if(this->xml.name() == "ZEBAdministration") {
                this->initZebData(track);
            } else if(this->xml.name() == "Messparameter") {
                this->initMeasurementParametres(track);
            } else if(this->xml.name() == "Messpunktabstand_Oberflaechenschaeden") {
                int frequency = this->getFrequencyValue(xml.readElementText());
                if(frequency != -99) {
                    damage->setFrequencyMeasurementValues(frequency);
                } else {
                    return false;
                }
            } else if(this->xml.name() == "Abstand_Profile_In_Laengsrichtung") {
                int frequency = this->getFrequencyValue(xml.readElementText());
                if(frequency != -99) {
                    damage->setFrequencyMeasurementValues(frequency);
                } else {
                    return false;
                }
            } else if(this->xml.name() == "FahrstreifenteileAsphalt") {
                damage->setCountOfPartsForEvaluation(xml.readElementText().toInt());
            } else if(this->xml.name() == "Aspahlt") {
                damage->addSurfaceType(currentDistanceInformation, 'a');
                asphalt = true;
                concrete = false;
                cobbleStone = false;
            } else if(this->xml.name() == "Beton") {
                damage->addSurfaceType(currentDistanceInformation, 'b');
                asphalt = false;
                concrete = true;
                cobbleStone = false;
            } else if(this->xml.name() == "Pflaster") {
                damage->addSurfaceType(currentDistanceInformation, 'p');
                asphalt = false;
                concrete = false;
                cobbleStone = true;
            } else if(this->xml.name() == "R") {
                int partsForEvaluation = damage->getCountOfPartsForEvaluation();
                if(asphalt) {
                    //create the arrays for storing the evaluation as boolean values
                    QString riss = this->initTp3Evaluation(this->getXmlAttribute("RISS"), partsForEvaluation);
                    QString efli = this->initTp3Evaluation(this->getXmlAttribute("EFLI"), partsForEvaluation);
                    QString afli = this->initTp3Evaluation(this->getXmlAttribute("AFLI"), partsForEvaluation);
                    QString fli = this->initTp3Evaluation(this->getXmlAttribute("FLI"), partsForEvaluation);
                    QString aus = this->initTp3Evaluation(this->getXmlAttribute("AUS"), partsForEvaluation);
                    QString ona = this->initTp3Evaluation(this->getXmlAttribute("ONA"), partsForEvaluation);
                    QString bin = this->initTp3Evaluation(this->getXmlAttribute("BIN"), partsForEvaluation);

                    //add the evaluation arrays to the damage-object
                    damage->addRiss(riss);
                    damage->addEfli(efli);
                    damage->addAfli(afli);
                    damage->addFli(fli);
                    damage->addAus(aus);
                    damage->addOna(ona);
                    damage->addBin(bin);
                } else if(concrete) {
                    //create the arrays for storing the evaluation as boolean values
                    QString lqrl = this->initTp3Evaluation(this->getXmlAttribute("LQRL"), partsForEvaluation);
                    QString eabf = this->initTp3Evaluation(this->getXmlAttribute("EABF"), partsForEvaluation);
                    QString kasl = this->initTp3Evaluation(this->getXmlAttribute("KASL"), partsForEvaluation);
                    QString ntr = this->initTp3Evaluation(this->getXmlAttribute("NTR"), partsForEvaluation);
                    QString fuf = this->initTp3Evaluation(this->getXmlAttribute("FUF"), partsForEvaluation);
                    QString bte = this->initTp3Evaluation(this->getXmlAttribute("BTE"), partsForEvaluation);

                    //add the evaluation arrays to the damage-object
                    damage->addLqrl(lqrl);
                    damage->addEabf(eabf);
                    damage->addKasl(kasl);
                    damage->addNtr(ntr);
                    damage->addFuf(fuf);
                    damage->addBte(bte);
                } else if(cobbleStone) {
                    //create the arrays for storing the evaluation as boolean values
                    QString verbund = this->initTp3Evaluation(this->getXmlAttribute("VERBUND"), partsForEvaluation);
                    QString bruch = this->initTp3Evaluation(this->getXmlAttribute("BRUCH"), partsForEvaluation);
                    QString pbte = this->initTp3Evaluation(this->getXmlAttribute("PBTE"), partsForEvaluation);

                    //add the evaluation arrays to the damage-object
                    damage->addVerbund(verbund);
                    damage->addBruch(bruch);
                    damage->addPbte(pbte);
                }
                currentDistanceValues += damage->getFrequencyMeasurementValues();
            } else if(this->xml.name() == "Datenstrom") {
                damage->addVelocity(this->getXmlAttribute("V").toInt());
            } else if(this->xml.name() == "Erfassungsflag") {
                int fs = this->getXmlAttribute("FS").toInt();
                int g = this->getXmlAttribute("G").toInt();
                damage->addStripe(fs);
                damage->addValidity(g);
            } else if(this->xml.name() == "WGS") {
                //storing the coordinates as ;-separated QString to prevent data-loose during conversion to double or float
                QString pos = this->extractCoordinates();
                damage->addCoordinates(pos);

                //get the timestamp
                QDateTime timestamp = this->extractTimestamp();
                damage->addTimestamp(timestamp);

                //get and storing the lfdm-information
                int lfdm = this->getXmlAttribute("LfdM").toInt();
                damage->addLfdm(lfdm);
            } else if(this->xml.name() == "Z") {
                damage->addZFlag(this->getXmlAttribute("Z").toInt());
            } else if(this->xml.name() == "B") {
                QString camNumber = this->getXmlAttribute("Nr");
                foreach (Camera *cam, track->getCameras()) {
                   if(cam->getCamNumber() == camNumber) {
                       cam->addPicture(this->getXmlAttribute("D"));
                       break;
                   }
                }

                //now increase the count of current cameras and check, if all pictures for the current distance are extracted
                currentCountOfCams++;
                if(currentCountOfCams == maxCountOfCams) {
                    currentDistancePictures += pictureFrequence;
                    currentCountOfCams = 0;
                }
            }
        } else if(xml.isEndElement()) {
            if(this->xml.name() == "Datenstrom") {
                currentDistanceInformation += damage->getFrequencyMeasurementInformation();
            }
        }
        track->setDamageMeasurement(damage);
    }
    return true;
}

QString ZebParser::getErrorString() {
    return this->errorStr;
}

/*!
 * \brief ZebParser::getXmlAttribute
 * This function iterates over all attributes of the current XML-node and returns value of the searched attribute.
 * \param attrName the name of the searched attribute as QString
 * \return the value of an attribute as QString
 */
QString ZebParser::getXmlAttribute(QString attrName) {
    QXmlStreamAttributes attrs = xml.attributes();
    for(int i = 0; i < attrs.size(); i++) {
        if(attrs[i].name() == attrName) {
            return attrs[i].value().toString();
        }
    }
    return "";
}

/*!
 * \brief ZebParser::getFrequencyValue
 * This function extracts the number of the frequency of measurement values etc.
 * It is mandatory, that the word "Meter" is part of the given attribute-value, to extract the frequency successfully.
 * \param xmlValue the value of the the current attribute as QString
 * \return the frequency as int. If the frequency cannot be extracted, the value "-99" will be returned
 */
int ZebParser::getFrequencyValue(QString xmlValue) {
    QStringList splittedValue = xmlValue.split(" ");
    if(splittedValue.size() > 0) {
        for(int i = 0; i < splittedValue.size(); i++) {
            if(i > 0 && splittedValue.at(i) == "Meter") {
                QString frequencyValue = splittedValue.value(i - 1);
                try {
                    return frequencyValue.toInt();
                } catch(std::exception &e) {
                    return -99;
                }
            }
        }
    }
    return -99;
}

/*!
 * \brief ZebParser::getFrequencyValueAsDouble
 * This function extracts the number of the frequency of measurement values etc. and returns it as double.
 * It is mandatory, that the word "Meter" is part of the given attribute-value, to extract the frequency successfully.
 * \param xmlValue the value of the the current attribute as QString
 * \return the frequency as double. If the frequency cannot be extracted, the value "-99.99" will be returned
 */
double ZebParser::getFrequencyValueAsDouble(QString xmlValue) {
    QStringList splittedValue = xmlValue.split(" ");
    if(splittedValue.size() > 0) {
        for(int i = 0; i < splittedValue.size(); i++) {
            if(i > 0 && splittedValue.at(i) == "Meter") {
                QString frequencyValue = splittedValue.value(i - 1);
                try {
                    return frequencyValue.toDouble();
                } catch(std::exception &e) {
                    return -99.99;
                }
            }
        }
    }
    return -99.99;
}

/*!
 * \brief ZebParser::initCamera
 * This function extracts all cameras from the current xml-file.
 * The result of the extraction will be compared to the cameras, which are already stored in the given Track-object.
 * If an extracted camera is not stored in the Track-object already, it will be initialised as a new Camera-object.
 * \param track the Track-object, where Camera-information are stored
 * \param pictureFrequence a reference to store the frequency of pictures in the current XML-file as integer
 */
void ZebParser::initCamera(Track *track, int pictureFrequence) {
    //get the number of the current cam from xml
    QString number = this->getXmlAttribute("Nr");

    //iterate over cameras which are already stored
    QVector<Camera *> cams = track->getCameras();
    bool camExisting = false;
    if(cams.size() > 0) {
        for(int i = 0; i < cams.size(); i++) {
            if(cams.at(i)->getCamNumber() == number) {
                camExisting = true;
                pictureFrequence = cams.at(i)->getFrequency();
            }
        }
    }

    //just store a new camera, if cam-number is not stored already
    if(!camExisting) {
        Camera *cam = new Camera();
        cam->setFrequency(pictureFrequence);
        cam->setCamNumber(number);
        cam->setCamName(this->getXmlAttribute("Name"));
        cam->setPixelH(this->getXmlAttribute("PixelH").toInt());
        cam->setPixelV(this->getXmlAttribute("PixelV").toInt());
        cam->setRootDirectory(this->getXmlAttribute("RootVerzeichnis"));
        cam->setFrequency(pictureFrequence);
        track->addCamera(cam);
    }
}

/*!
 * \brief ZebParser::initZebData
 * This function extracts all attribute values of the XML-node "ZEBAdministration" and stores them in the given track-object.
 * \param track a Track-object where all extracted data will be stored.
 */
void ZebParser::initZebData(Track *track) {
    if(!track->getZebAdmin()) {
        track->setYear(this->getXmlAttribute("Jahr").toInt());
        track->setStreetClass(this->getXmlAttribute("Strassenklasse"));
        track->setCountry(this->getXmlAttribute("ZENDI"));
        track->setReason(this->getXmlAttribute("Anlass"));
        track->setVersion(this->getXmlAttribute("Dateiversion"));
        track->setZebAdmin(true);
    }
}

/*!
 * \brief ZebParser::initMeasurementParametres
 * This function extracts all attribute values of the XML-node "Messparameter" and stores them in the given track-object.
 * \param track a Track-object where all extracted data will be stored.
 */
void ZebParser::initMeasurementParametres(Track *track) {
    if(!track->getParametres()) {
        track->setSystem(this->getXmlAttribute("Messsystem"));
        track->setNumberPlate(this->getXmlAttribute("KfzKennz"));
        track->setDesignerCompany(this->getXmlAttribute("Messgeraetebauer"));
        track->setOperatorCompany(this->getXmlAttribute("Messsystembetreiber"));
        track->setPrinciple(this->getXmlAttribute("Messprinzip"));
        track->setDrivingPerson(this->getXmlAttribute("Fahrer"));
        track->setOperatingPerson(this->getXmlAttribute("Operator"));
        track->setPositionSystem(this->getXmlAttribute("Positionsbestimmungsverfahren"));
        track->setParametres(true);
    }
}

/*!
 * \brief ZebParser::extractTimestamp
 * This function extracts the timestamp from an XML-node named "WGS".
 * The timetstamp in the XML-file is in the format DD.MM.YYYY for the date and in the format HH:MM:SS for the time.
 * \return the timestamp as QDateTime in ISO-format
 */
QDateTime ZebParser::extractTimestamp() {
    QString localTimestamp = this->getXmlAttribute("Datum")
            + "T"
            + this->getXmlAttribute("Uhr");
    return QDateTime::fromString(localTimestamp, Qt::ISODate);
}

/*!
 * \brief ZebParser::extractCoordinates
 * This function extracts the coordinates stored in an XML-node named "WGS".
 * In ZEB-files two height-information are stored (H_WGS and H_NN). The value of "H_WGS" will be extracted.
 * \return a QString containing the 3D-coordinates in format "x;y;z"
 */
QString ZebParser::extractCoordinates() {
    QString x = this->getXmlAttribute("L");
    QString y = this->getXmlAttribute("B");
    QString z = this->getXmlAttribute("H_WGS");
    return (x + ";" + y + ";" + z);
}

/*!
 * \brief ZebParser::extractDataMedium
 * This function extracts the value of the attribute "Datentraeger" located in the XML-Node "Bildparameter".
 * \param track the Track-object where the extracted information should be stored.
 */
void ZebParser::extractDataMedium(Track *track) {
    if(track->getDataMedium() == "") {
        track->setDataMedium(this->getXmlAttribute("Datentraeger"));
    }
}

/*!
 * \brief ZebParser::initTp3Evaluation
 * This function extracts the information about the evaluation and correct the order of the evaluation parts.
 * \param evaluationString the evaluation as QString from the current XML-node
 * \param partsForEvaluation the number of parts of the TP3-evaluation, i.e. in how many columns a TP3-image is separated
 * \return a QString containing the TP3-evaluation with all parts of the evaluation, e.g. "0;1;1" - "0" = no damage detected, "1" = damage detected
 */
QString ZebParser::initTp3Evaluation(QString evaluationString, int partsForEvaluation) {
    int evaluationStringSize = evaluationString.size();
    QString result;
    for(int i = 0; i < evaluationStringSize; i++) {
        QString substring = evaluationString.mid(evaluationStringSize - 1 - i, 1);
        if(substring == "1") {
            result.append("1");
        } else {
            result.append("0");
        }
        if(i < evaluationStringSize - 1) {
            result.append(";");
        }
    }
    return result;
}
