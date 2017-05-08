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

#ifndef LONGITUDINAL_H
#define LONGITUDINAL_H

#include <QObject>
#include <QMap>
#include <QVector3D>
#include <QString>
#include <QStringList>
#include <QDateTime>
#include <QList>

/**
 * @brief The Longitudinal class.
 * This class provides all measurements values
 * and all other needed information for displaying
 * the height measuring profil (HMP).
 */
class Longitudinal : public QObject {
    Q_OBJECT
public:
    explicit Longitudinal(QObject *parent = 0);
    ~Longitudinal();

    double getFrequencyMeasurementValues() const;
    void setFrequencyMeasurementValues(double value);

    int getFrequencyInclination() const;
    void setFrequencyInclination(int value);

    int getFrequencyCurvature() const;
    void setFrequencyCurvature(int value);

    QString getMeasurementLine() const;
    void setMeasurementLine(const QString &value);

    QStringList getForward();
    void addForward(QString value);

    double getFrequencyMeasurementInformation() const;
    void setFrequencyMeasurementInformation(double value);

    QList<QString> getHmp();
    void addHmp(QString &value);

    QList<QString> getCurvature();
    void addCurvature(QString value);

    QList<QString> getInclination();
    void addInclination(QString value);

    QList<QString> getCoordinates();
    void addCoordinates(QString &value);

    QList<QDateTime> getTimestamps();
    void addTimestamp(QDateTime &value);

    QList<int> getStripe();
    void addStripe(int &value);

    QList<int> getValidity();
    void addValidity(int &value);

    double getFrequencyGapDistance() const;
    void setFrequencyGapDistance(double value);

    QStringList getBackward();
    void addBackward(QString value);

    QList<int> getVelocity();
    void addVelocity(int value);

    QList<int> getZFlags();
    void addZFlags(int value);

    QList<int> getLfdm();
    void addLfdm(int value);

private:
    double frequencyMeasurementValues;
    int frequencyMeasurementInformation;
    int frequencyInclination;
    int frequencyCurvature;
    int frequencyGapDistance;
    QStringList forward;             //schema for every entry: A;L;K;ElementText (A, L, K are attributes of R-nodes)
    QStringList backward;            //schema for every entry: A;L;K;ElementText (A, L, K are attributes of R-nodes)
    QString measurementLine;
    QList<QString> hmp;              //<distance, hmp>
    QList<QString> curvature;        //<distance, curvature>
    QList<QString> inclination;      //<distance, inclination>
    QList<QString> coordinates;      //<distance, coordinates as QString, separated by semicolon (e.g. X;Y;Z)>
    QList<QDateTime> timestamps;     //<distance, timestamps>
    QList<int> stripe;               //<distance, stripe>
    QList<int> validity;             //<distance, validity>
    QList<int> velocity;             //<distance, velocity>
    QList<int> zFlags;               //<distance, zFlags>
    QList<int> lfdm;                 //<distance, lfdm>

signals:

public slots:
};

#endif // LONGITUDINAL_H
