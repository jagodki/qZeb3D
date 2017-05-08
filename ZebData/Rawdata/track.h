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

#ifndef TRACK_H
#define TRACK_H

#include <QObject>
#include <QString>
#include <QVector>
#include "camera.h"
#include "longitudinal.h"
#include "transverse.h"
#include "damage.h"

/**
 * @brief The Track class.
 * This class provides information about a measurement
 * track and it administration data. It also contains
 * objects, in that the measurement values are stored.
 */
class Track : public QObject {
    Q_OBJECT
public:
    explicit Track(QObject *parent = 0);

    void setDataMedium(QString medium);
    QString getDataMedium();

    int getYear();
    void setYear(int value);

    QString getStreetClass();
    void setStreetClass(QString value);

    QString getCountry();
    void setCountry(QString value);

    QVector<Camera *> getCameras();
    void addCamera(Camera *value);

    QString getReason();
    void setReason(QString value);

    QString getSystem();
    void setSystem(QString value);

    QString getVersion();
    void setVersion(QString value);

    QString getDesignerCompany();
    void setDesignerCompany(QString value);

    QString getOperatorCompany();
    void setOperatorCompany(QString value);

    QString getPrinciple();
    void setPrinciple(QString value);

    QString getDrivingPerson();
    void setDrivingPerson(QString value);

    QString getOperatingPerson();
    void setOperatingPerson(QString value);

    QString getPositionSystem();
    void setPositionSystem(QString value);

    bool getZebAdmin();
    void setZebAdmin(bool value);

    bool getParametres();
    void setParametres(bool value);

    Longitudinal *getLongitudinalMeasurement();
    void setLongitudinalMeasurement(Longitudinal *value);

    Transverse *getTransverseMeasurement();
    void setTransverseMeasruement(Transverse *value);

    Damage *getDamageMeasurement();
    void setDamageMeasurement(Damage *value);

    QString getNumberPlate();
    void setNumberPlate(QString value);

private:
    QString dataMedium;
    int year;
    QString streetClass;
    QString country;
    QString reason;
    QString system;
    QString numberPlate;
    QString version;
    QString designerCompany;
    QString operatorCompany;
    QString principle;
    QString drivingPerson;
    QString operatingPerson;
    QString positionSystem;
    bool zebAdmin;
    bool parametres;
    QVector<Camera *> cameras;
    Longitudinal *longitudinalMeasurement;
    Transverse *transverseMeasurement;
    Damage *damageMeasurement;

signals:

public slots:


};

#endif // TRACK_H
