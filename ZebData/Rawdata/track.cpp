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

#include "track.h"

Track::Track(QObject *parent) : QObject(parent) {
    this->zebAdmin = false;
    this->parametres = false;
}

void Track::setDataMedium(QString medium) {
    this->dataMedium = medium;
}

QString Track::getDataMedium() {
    return this->dataMedium;
}

int Track::getYear() {
    return year;
}

void Track::setYear(int value) {
    year = value;
}

QString Track::getStreetClass() {
    return streetClass;
}

void Track::setStreetClass(QString value) {
    streetClass = value;
}

QString Track::getCountry() {
    return country;
}

void Track::setCountry(QString value) {
    country = value;
}

QVector<Camera *> Track::getCameras() {
    return cameras;
}

void Track::addCamera(Camera *value) {
    cameras.append(value);
}

QString Track::getReason()
{
    return reason;
}

void Track::setReason(QString value)
{
    reason = value;
}

QString Track::getSystem()
{
    return system;
}

void Track::setSystem(QString value)
{
    system = value;
}

QString Track::getVersion()
{
    return version;
}

void Track::setVersion(QString value)
{
    version = value;
}

QString Track::getDesignerCompany()
{
    return designerCompany;
}

void Track::setDesignerCompany(QString value)
{
    designerCompany = value;
}

QString Track::getOperatorCompany()
{
    return operatorCompany;
}

void Track::setOperatorCompany(QString value)
{
    operatorCompany = value;
}

QString Track::getPrinciple()
{
    return principle;
}

void Track::setPrinciple(QString value)
{
    principle = value;
}

QString Track::getDrivingPerson()
{
    return drivingPerson;
}

void Track::setDrivingPerson(QString value)
{
    drivingPerson = value;
}

QString Track::getOperatingPerson()
{
    return operatingPerson;
}

void Track::setOperatingPerson(QString value)
{
    operatingPerson = value;
}

QString Track::getPositionSystem()
{
    return positionSystem;
}

void Track::setPositionSystem(QString value)
{
    positionSystem = value;
}

bool Track::getZebAdmin()
{
    return zebAdmin;
}

void Track::setZebAdmin(bool value)
{
    zebAdmin = value;
}

bool Track::getParametres()
{
    return parametres;
}

void Track::setParametres(bool value)
{
    parametres = value;
}

Longitudinal *Track::getLongitudinalMeasurement()
{
    return longitudinalMeasurement;
}

void Track::setLongitudinalMeasurement(Longitudinal *value)
{
    longitudinalMeasurement = value;
}

Transverse *Track::getTransverseMeasurement()
{
    return transverseMeasurement;
}

void Track::setTransverseMeasruement(Transverse *value)
{
    transverseMeasurement = value;
}

Damage *Track::getDamageMeasurement()
{
    return damageMeasurement;
}

void Track::setDamageMeasurement(Damage *value)
{
    damageMeasurement = value;
}

QString Track::getNumberPlate()
{
    return numberPlate;
}

void Track::setNumberPlate(QString value)
{
    numberPlate = value;
}

