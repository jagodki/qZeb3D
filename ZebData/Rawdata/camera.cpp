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

#include "camera.h"

Camera::Camera(QObject *parent) : QObject(parent) {

}

void Camera::setRootDirectory(QString newRootDirectory) {
    this->rootDirectory = newRootDirectory;
}

void Camera::setPixelH(int ph) {
    this->pixelH = ph;
}

void Camera::setPixelV(int pv) {
    this->pixelV = pv;
}

QString Camera::getRootDirectory() {
    return this->rootDirectory;
}

int Camera::getPixelH() {
    return this->pixelH;
}

int Camera::getPixelV() {
    return this->pixelV;
}

QString Camera::getCamName() const
{
    return camName;
}

void Camera::setCamName(const QString &value)
{
    camName = value;
}

QString Camera::getCamNumber() const
{
    return camNumber;
}

void Camera::setCamNumber(const QString &value)
{
    camNumber = value;
}

QList<QString> Camera::getPictures()
{
    return pictures;
}

void Camera::addPicture(QString value)
{
    pictures.append(value);
}

int Camera::getFrequency() const
{
    return frequency;
}

void Camera::setFrequency(int value)
{
    frequency = value;
}
