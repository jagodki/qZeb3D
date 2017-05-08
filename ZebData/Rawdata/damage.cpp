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

#include "damage.h"

Damage::Damage(QObject *parent) : QObject(parent) {

}

Damage::~Damage() {
}

QList<QString> Damage::getRiss()
{
    return riss;
}

void Damage::addRiss(QString value)
{
    riss.append(value);
}

QList<QString> Damage::getEfli()
{
    return efli;
}

void Damage::addEfli(QString value)
{
    efli.append(value);
}

QList<QString> Damage::getAfli()
{
    return afli;
}

void Damage::addAfli(QString value)
{
    afli.append(value);
}

QList<QString> Damage::getFli()
{
    return fli;
}

void Damage::addFli(QString value)
{
    fli.append(value);
}

QList<QString> Damage::getAus()
{
    return aus;
}

void Damage::addAus(QString value)
{
    aus.append(value);
}

QList<QString> Damage::getOna()
{
    return ona;
}

void Damage::addOna(QString value)
{
    ona.append(value);
}

QList<QString> Damage::getBin()
{
    return bin;
}

void Damage::addBin(QString value)
{
    bin.append(value);
}

QList<QString> Damage::getLqrl()
{
    return lqrl;
}

void Damage::addLqrl(QString value)
{
    lqrl.append(value);
}

QList<QString> Damage::getEabf()
{
    return eabf;
}

void Damage::addEabf(QString value)
{
    eabf.append(value);
}

QList<QString> Damage::getKasl()
{
    return kasl;
}

void Damage::addKasl(QString value)
{
    kasl.append(value);
}

QList<QString> Damage::getNtr()
{
    return ntr;
}

void Damage::addNtr(QString value)
{
    ntr.append(value);
}

QList<QString> Damage::getFuf()
{
    return fuf;
}

void Damage::addFuf(QString value)
{
    fuf.append(value);
}

QList<QString> Damage::getBte()
{
    return bte;
}

void Damage::addBte(QString value)
{
    bte.append(value);
}

QList<QString> Damage::getVerbund()
{
    return verbund;
}

void Damage::addVerbund(QString value)
{
    verbund.append(value);
}

QList<QString> Damage::getBruch()
{
    return bruch;
}

void Damage::addBruch(QString value)
{
    bruch.append(value);
}

QList<QString> Damage::getPbte()
{
    return pbte;
}

void Damage::addPbte(QString value)
{
    pbte.append(value);
}

int Damage::getFrequencyMeasurementValues() const
{
    return frequencyMeasurementValues;
}

void Damage::setFrequencyMeasurementValues(int value)
{
    frequencyMeasurementValues = value;
}

int Damage::getFrequencyMeasurementInformation() const
{
    return frequencyMeasurementInformation;
}

void Damage::setFrequencyMeasurementInformation(int value)
{
    frequencyMeasurementInformation = value;
}

int Damage::getCountOfPartsForEvaluation() const
{
    return countOfPartsForEvaluation;
}

void Damage::setCountOfPartsForEvaluation(int value)
{
    countOfPartsForEvaluation = value;
}

QMap<int, char> Damage::getSurfaceType()
{
    return surfaceType;
}

void Damage::addSurfaceType(int key, char value)
{
    surfaceType.insert(key, value);
}

QList<QString> Damage::getCoordinates()
{
    return coordinates;
}

void Damage::addCoordinates(QString value)
{
    coordinates.append(value);
}

QList<QDateTime> Damage::getTimestamps()
{
    return timestamps;
}

void Damage::addTimestamp(QDateTime value)
{
    timestamps.append(value);
}

QList<int> Damage::getStripe()
{
    return stripe;
}

void Damage::addStripe(int value)
{
    stripe.append(value);
}

QList<int> Damage::getValidity()
{
    return validity;
}

void Damage::addValidity(int value)
{
    validity.append(value);
}

QList<int> Damage::getVelocity()
{
    return velocity;
}

void Damage::addVelocity(int value)
{
    velocity.append(value);
}

QList<int> Damage::getZFlags()
{
    return zFlags;
}

void Damage::addZFlag(int value)
{
    zFlags.append(value);
}

QList<int> Damage::getLfdm()
{
    return lfdm;
}

void Damage::addLfdm(int value)
{
    lfdm.append(value);
}
