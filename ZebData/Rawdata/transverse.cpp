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

#include "transverse.h"

Transverse::Transverse(QObject *parent) : QObject(parent) {

}

Transverse::~Transverse() {
}

int Transverse::getFrequencyMeasurementInformation() const
{
    return frequencyMeasurementInformation;
}

void Transverse::setFrequencyMeasurementInformation(int value)
{
    frequencyMeasurementInformation = value;
}

int Transverse::getFrequencyMeasurementValues() const
{
    return frequencyMeasurementValues;
}

void Transverse::setFrequencyMeasurementValues(int value)
{
    frequencyMeasurementValues = value;
}

QString Transverse::getMeasurementLine() const
{
    return measurementLine;
}

void Transverse::setMeasurementLine(QString value)
{
    measurementLine = value;
}

QMap<int, double> Transverse::getSensors()
{
    return sensors;
}

QList<QString> Transverse::getProfiles()
{
    return profiles;
}

QList<QString> Transverse::getCoordinates()
{
    return coordinates;
}

void Transverse::addCoordinate(QString value)
{
    coordinates.append(value);
}

QList<QDateTime> Transverse::getTimestamps()
{
    return timestamps;
}

void Transverse::addTimestamp(QDateTime value)
{
    timestamps.append(value);
}

QList<int> Transverse::getStripes()
{
    return stripes;
}

void Transverse::addStripe(int value)
{
    stripes.append(value);
}

QList<int> Transverse::getValidity()
{
    return validity;
}

void Transverse::addValidity(int value)
{
    validity.append(value);
}

QList<int> Transverse::getVelocity()
{
    return velocity;
}

void Transverse::addVelocity(int value)
{
    velocity.append(value);
}

QList<int> Transverse::getZFlags()
{
    return zFlags;
}

void Transverse::addZFlag(int value)
{
    zFlags.append(value);
}

void Transverse::addLfdm(int value)
{
    lfdm.append(value);
}

QList<int> Transverse::getLfdm()
{
    return lfdm;
}

void Transverse::addProfile(QString value)
{
    profiles.append(value);
}

void Transverse::addSensor(int key, double value)
{
    sensors.insert(key, value);
}
