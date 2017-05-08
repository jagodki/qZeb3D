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

#ifndef ZEBPARSER_H
#define ZEBPARSER_H

#include <QXmlDefaultHandler>
#include <QXmlStreamReader>
#include <QIODevice>
#include <QString>
#include <QFile>
#include <QHash>
#include <QVector>
#include <QStringList>
#include <QVector3D>
#include <QDateTime>
#include <QTextEdit>
#include <QTextCursor>
#include "ZebData/Rawdata/track.h"
#include "ZebData/Rawdata/longitudinal.h"
#include "ZebData/Rawdata/transverse.h"
#include "ZebData/Rawdata/damage.h"

/*!
 * \class ZebParser
 * \brief The ZebParser class
 */

class ZebParser : public QXmlDefaultHandler{

public:
    ZebParser();
    ~ZebParser();
    //old:  bool parseXml(QString &xmlPath);
    bool parseXml(QString xmlPath, Track *track, QTextEdit *te, QString errorMessage, QString startMessage, QString endMessage);
    QString getErrorString();

private:
    bool startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts) Q_DECL_OVERRIDE;
    bool endElement(const QString &namespaceURI, const QString &localName, const QString &qName) Q_DECL_OVERRIDE;
    bool characters(const QString &str) Q_DECL_OVERRIDE;
    bool fatalError(const QXmlParseException &exception) Q_DECL_OVERRIDE;
    QString errorString() const Q_DECL_OVERRIDE;

    bool readTP1a(Track *track);
    bool readTP1b(Track *track);
    bool readTP3(Track *track);

    void readPictureParameter();
    QString getXmlAttribute(QString attrName);
    int getFrequencyValue(QString xmlValue);
    double getFrequencyValueAsDouble(QString xmlValue);
    void initCamera(Track *track, int pictureFrequence);
    void initZebData(Track *track);
    void initMeasurementParametres(Track *track);
    QDateTime extractTimestamp();
    QString extractCoordinates();
    void extractDataMedium(Track *track);
    QString initTp3Evaluation(QString evaluationString, int partsForEvaluation);

    QXmlStreamReader xml;
    QString currentText;
    QString errorStr;
};

#endif // ZEBPARSER_H
