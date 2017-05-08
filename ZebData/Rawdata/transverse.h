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

#ifndef TRANSVERSE_H
#define TRANSVERSE_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QVector3D>
#include <QDateTime>
#include <QList>

/*!
 * \brief The Transverse class
 * This class contains all the measurement values
 * of transverse eveness and all the information,
 * which belong to the measured cross profiles.
 */
class Transverse : public QObject {
    Q_OBJECT
public:
    explicit Transverse(QObject *parent = 0);
    ~Transverse();

    int getFrequencyMeasurementInformation() const;
    void setFrequencyMeasurementInformation(int value);

    int getFrequencyMeasurementValues() const;
    void setFrequencyMeasurementValues(int value);

    QString getMeasurementLine() const;
    void setMeasurementLine(QString value);

    QMap<int, double> getSensors();
    void addSensor(int key, double value);

    QList<QString> getProfiles();
    void addProfile(QString value);

    QList<QString> getCoordinates();
    void addCoordinate(QString value);

    QList<QDateTime> getTimestamps();
    void addTimestamp(QDateTime value);

    QList<int> getStripes();
    void addStripe(int value);

    QList<int> getValidity();
    void addValidity(int value);

    QList<int> getVelocity();
    void addVelocity(int value);

    QList<int> getZFlags();
    void addZFlag(int value);

    QList<int> getLfdm();
    void addLfdm(int value);

private:
    int frequencyMeasurementValues;
    int frequencyMeasurementInformation;
    QString measurementLine;
    QMap<int, double> sensors;
    QList<QString> profiles;         //<distance, profiles as QString(q0;q1;q2;...;qn)>
    QList<QString> coordinates;      //<distance, coordinates as QString, separated by semicolon (e.g. X;Y;Z)>
    QList<QDateTime> timestamps;     //<distance, timestamps>
    QList<int> stripes;              //<distance, stripe>
    QList<int> validity;             //<distance, validity>
    QList<int> velocity;             //<distance, velocity>
    QList<int> zFlags;               //<distance, zFlags>
    QList<int> lfdm;                 //<distance, lfdm>

signals:

public slots:
};

#endif // TRANSVERSE_H
