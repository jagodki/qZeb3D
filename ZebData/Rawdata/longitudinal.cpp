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

#include "longitudinal.h"

Longitudinal::Longitudinal(QObject *parent) : QObject(parent) {

}

Longitudinal::~Longitudinal() {
}

double Longitudinal::getFrequencyMeasurementValues() const
{
    return frequencyMeasurementValues;
}

void Longitudinal::setFrequencyMeasurementValues(double value)
{
    frequencyMeasurementValues = value;
}

int Longitudinal::getFrequencyInclination() const
{
    return frequencyInclination;
}

void Longitudinal::setFrequencyInclination(int value)
{
    frequencyInclination = value;
}

int Longitudinal::getFrequencyCurvature() const
{
    return frequencyCurvature;
}

void Longitudinal::setFrequencyCurvature(int value)
{
    frequencyCurvature = value;
}

QString Longitudinal::getMeasurementLine() const
{
    return measurementLine;
}

void Longitudinal::setMeasurementLine(const QString &value)
{
    measurementLine = value;
}

QStringList Longitudinal::getForward()
{
    return forward;
}

void Longitudinal::addForward(QString value)
{
    forward.append(value);
}

double Longitudinal::getFrequencyMeasurementInformation() const
{
    return frequencyMeasurementInformation;
}

void Longitudinal::setFrequencyMeasurementInformation(double value)
{
    frequencyMeasurementInformation = value;
}

QList<QString> Longitudinal::getHmp()
{
    return hmp;
}

void Longitudinal::addHmp(QString &value)
{
    hmp.append(value);
}

QList<QString> Longitudinal::getCurvature()
{
    return curvature;
}

void Longitudinal::addCurvature(QString value)
{
    curvature.append(value);
}

QList<QString> Longitudinal::getInclination()
{
    return inclination;
}

void Longitudinal::addInclination(QString value)
{
    inclination.append(value);
}

QList<QString> Longitudinal::getCoordinates()
{
    return coordinates;
}

void Longitudinal::addCoordinates(QString &value)
{
    coordinates.append(value);
}

QList<QDateTime> Longitudinal::getTimestamps()
{
    return timestamps;
}

void Longitudinal::addTimestamp(QDateTime &value)
{
    timestamps.append(value);
}

QList<int> Longitudinal::getStripe()
{
    return stripe;
}

void Longitudinal::addStripe(int &value)
{
    stripe.append(value);
}

QList<int> Longitudinal::getValidity()
{
    return validity;
}

void Longitudinal::addValidity(int &value)
{
    validity.append(value);
}

double Longitudinal::getFrequencyGapDistance() const
{
    return frequencyGapDistance;
}

void Longitudinal::setFrequencyGapDistance(double value)
{
    frequencyGapDistance = value;
}

QStringList Longitudinal::getBackward()
{
    return backward;
}

void Longitudinal::addBackward(QString value)
{
    backward.append(value);
}

QList<int> Longitudinal::getVelocity()
{
    return velocity;
}

void Longitudinal::addVelocity(int value)
{
    velocity.append(value);
}

QList<int> Longitudinal::getZFlags()
{
    return zFlags;
}

void Longitudinal::addZFlags(int value)
{
    zFlags.append(value);
}

QList<int> Longitudinal::getLfdm()
{
    return lfdm;
}

void Longitudinal::addLfdm(int value)
{
    lfdm.append(value);
}
