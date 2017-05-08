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

#ifndef DAMAGE_H
#define DAMAGE_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QDateTime>
#include <QList>

/**
 * @brief The Damage class.
 * This class provides the measurement values and all
 * additionally needed information for displaying
 * surface damages.
 */
class Damage : public QObject {
    Q_OBJECT
public:
    explicit Damage(QObject *parent = 0);
    ~Damage();

    QList<QString> getRiss();
    void addRiss(QString value);

    QList<QString> getEfli();
    void addEfli(QString value);

    QList<QString> getAfli();
    void addAfli(QString value);

    QList<QString> getFli();
    void addFli(QString value);

    QList<QString> getAus();
    void addAus(QString value);

    QList<QString> getOna();
    void addOna(QString value);

    QList<QString> getBin();
    void addBin(QString value);

    QList<QString> getLqrl();
    void addLqrl(QString value);

    QList<QString> getEabf();
    void addEabf(QString value);

    QList<QString> getKasl();
    void addKasl(QString value);

    QList<QString> getNtr();
    void addNtr(QString value);

    QList<QString> getFuf();
    void addFuf(QString value);

    QList<QString> getBte();
    void addBte(QString value);

    QList<QString> getVerbund();
    void addVerbund(QString value);

    QList<QString> getBruch();
    void addBruch(QString value);

    QList<QString> getPbte();
    void addPbte(QString value);

    int getFrequencyMeasurementValues() const;
    void setFrequencyMeasurementValues(int value);

    int getFrequencyMeasurementInformation() const;
    void setFrequencyMeasurementInformation(int value);

    int getCountOfPartsForEvaluation() const;
    void setCountOfPartsForEvaluation(int value);

    QMap<int, char> getSurfaceType();
    void addSurfaceType(int key, char value);

    QList<QString> getCoordinates();
    void addCoordinates(QString value);

    QList<QDateTime> getTimestamps();
    void addTimestamp(QDateTime value);

    QList<int> getStripe();
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
    int countOfPartsForEvaluation;

    /* in all following maps is the first array-entry the left side in driving direction
     * the last array-entry is the most right side in driving direction
     */

    //asphalt section
    QList<QString> riss;              //distance, array of bools if damage is present for one evaluation part
    QList<QString> efli;              //distance, array of bools if damage is present for one evaluation part
    QList<QString> afli;              //distance, array of bools if damage is present for one evaluation part
    QList<QString> fli;               //distance, array of bools if damage is present for one evaluation part
    QList<QString> aus;               //distance, array of bools if damage is present for one evaluation part
    QList<QString> ona;               //distance, array of bools if damage is present for one evaluation part
    QList<QString> bin;               //distance, array of bools if damage is present for one evaluation part

    //concrete section
    QList<QString> lqrl;              //distance, array of bools if damage is present for one evaluation part
    QList<QString> eabf;              //distance, array of bools if damage is present for one evaluation part
    QList<QString> kasl;              //distance, array of bools if damage is present for one evaluation part
    QList<QString> ntr;               //distance, array of bools if damage is present for one evaluation part
    QList<QString> fuf;               //distance, array of bools if damage is present for one evaluation part
    QList<QString> bte;               //distance, array of bools if damage is present for one evaluation part

    //cobble stone section
    QList<QString> verbund;           //distance, array of bools if damage is present for one evaluation part
    QList<QString> bruch;             //distance, array of bools if damage is present for one evaluation part
    QList<QString> pbte;              //distance, array of bools if damage is present for one evaluation part

    QMap<int, char> surfaceType;         //<distance, type of surface (a=asphalt, b=concrete, p=cobble stone)>
    QList<QString> coordinates;      //<distance, coordinates>
    QList<QDateTime> timestamps;     //<distance, timestamps>
    QList<int> stripe;               //<distance, stripe>
    QList<int> validity;             //<distance, validity>
    QList<int> velocity;             //<distance, velocity>
    QList<int> zFlags;               //<distance, zFlags>
    QList<int> lfdm;                 //<distance, lfdm>

signals:

public slots:
};

#endif // DAMAGE_H
