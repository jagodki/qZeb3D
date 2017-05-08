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

#include "zeb2pointcloud.h"

Zeb2PointCloud::Zeb2PointCloud(QObject *parent) : QObject(parent) {

}

/*!
 * \brief Zeb2PointCloud::get3dDistance
 * This function calculates the euklidian distance in 3D-space.
 * No exception handling or else implemented, if coordinates can not extracted by the function.
 * \param p1 QString containing the coordinates of point 1 (coords separeted by semicolon)
 * \param p2 QString containing the coordinates of point 2 (coords separeted by semicolon)
 * \return the euklidian distance as double value
 */
double Zeb2PointCloud::get3dDistance(QString p1, QString p2) {
    //extract the coordinates from strings
    double x1 = p1.split(";").at(0).toDouble();
    double y1 = p1.split(";").at(1).toDouble();
    double z1 = p1.split(";").at(2).toDouble();

    double x2 = p2.split(";").at(0).toDouble();
    double y2 = p2.split(";").at(1).toDouble();
    double z2 = p2.split(";").at(2).toDouble();

    //calculate the distance with Pythagoras and return the result
    double result = qSqrt(qPow(x2 - x1, 2) + qPow(y2 - y1, 2) + qPow(z2 - z1, 2));
    return result;
}

/*!
 * \brief Zeb2PointCloud::get2dDistance
 * This function calculates the euklidian distance in 2D-space.
 * No exception handling or else implemented, if coordinates can not extracted by the function.
 * \param p1 QString containing the coordinates of point 1 (coords separeted by semicolon)
 * \param p2 QString containing the coordinates of point 2 (coords separeted by semicolon)
 * \return the euklidian distance as double value
 */
double Zeb2PointCloud::get2dDistance(QString p1, QString p2) {
    //extract the coordinates from strings
    double x1 = p1.split(";").at(0).toDouble();
    double y1 = p1.split(";").at(1).toDouble();

    double x2 = p2.split(";").at(0).toDouble();
    double y2 = p2.split(";").at(1).toDouble();

    //calculate the distance with Pythagoras and return the result
    double result = qSqrt(qPow(x2 - x1, 2) + qPow(y2 - y1, 2));
    return result;
}

/*!
 * \brief Zeb2PointCloud::getPointInDirection
 * This function calculates a new point on the line in direction (i.e. in driving direction) between to other points.
 * With the two given points a vector equation of a line will be calculated.
 * By using the multiplicator for the direction vector, the new point can be found.
 * No exception handling or else implemented, if coordinates can not extracted by the function.
 * \param p1 QString containing the coordinates of point 1 (coords separeted by semicolon)
 * \param p2 QString containing the coordinates of point 2 (coords separeted by semicolon)
 * \param distanceMultiplicator a double value as multiplicator for the directional vector
 * \return a new 3D-point as QString, the values will be separeted by semicolon (x;y;z)
 */
QString Zeb2PointCloud::getPointInDirection(QString p1, QString p2, double distanceMultiplicator) {
    //extract the coordinates from strings
    double x1 = p1.split(";").at(0).toDouble();
    double y1 = p1.split(";").at(1).toDouble();
    double z1 = p1.split(";").at(2).toDouble();

    double x2 = p2.split(";").at(0).toDouble();
    double y2 = p2.split(";").at(1).toDouble();
    double z2 = p2.split(";").at(2).toDouble();

    //get the directional vector
    double u = x2 - x1;
    double v = y2 - y1;
    double w = z2 - z1;

    //calculating the coordinates of the new point on the line, using the distanceOnLine (starting at p1)
    double x3 = x1 + distanceMultiplicator * u;
    double y3 = y1 + distanceMultiplicator * v;
    double z3 = z1 + distanceMultiplicator * w;

    //create the result as QString with format x;y;z
    QString result = QString::number(x3, 'f', 10) + ";" + QString::number(y3, 'f', 10) + ";" + QString::number(z3, 'f', 10);
    return result;
}

/*!
 * \brief Zeb2PointCloud::getPointCrossingDirection
 * This function calculates a new point, which is located on the orthongonaly crossing line of a line between 2 points.
 * First a curve between 2 given points will be calculated.
 * Then the given distance in metres will be converted in a distance in coordinates (i.e. coords can be in EPSG: 4326/WGS84)
 * The middle point, i.e. the crossing point between the original and its orthogonal curve, is the centre point of an circle.
 * By using a radius, which is the distance from starting point to the cross sensor, the new point on the orthogonal
 * curve can be descriped with polar coordinates. In the last step, this coordinates will be transformed in cartesian coordinates.
 * The z-value is no real height. It is the sum of HMP and cross-value
 * No exception handling or else implemented, if coordinates can not extracted by the function.
 * \param p1 QString containing the coordinates of point 1 (coords separeted by semicolon), where the crossing line starts of
 * \param p2 QString containing the coordinates of point 2 (coords separeted by semicolon), end point of the line in driving direction
 * \param p3 QString containing the coordinates of point 3 (coords separeted by semicolon), the starting point of the line in driving direction
 * \param distanceCrossValue the distance between point in crossing direction and p1 in metres
 * \param distanceLongValue the distance between p2 and p3 in metres
 * \param crossDepth the height value of the cross beam
 * \param offset the offset of the crossing height, so that transverse profil can be connected with the HMP
 * \return a new 3D-point as QString, the values will be separeted by semicolon (x;y;z)
 */
QString Zeb2PointCloud::getPointCrossingDirection(QString p1,
                                                  QString p2,
                                                  QString p3,
                                                  double distanceCrossValue,
                                                  int distanceLongValue,
                                                  double crossDepth,
                                                  double offset) {
    //extract the coordinates from strings
    double x1 = p1.split(";").at(0).toDouble();
    double y1 = p1.split(";").at(1).toDouble();

    double x2 = p2.split(";").at(0).toDouble();
    double y2 = p2.split(";").at(1).toDouble();

    //check, if driving direction is north or south
    bool drivingNorth;
    if(y2 > y1) {
        drivingNorth = true;
    } else {
        drivingNorth = false;
    }

    //check, if driving direction is east or west
    bool drivingEast;
    if(x2 > x1) {
        drivingEast = true;
    } else {
        drivingEast = false;
    }

    //check the driving direction and correct the algebraic sign, if necessary
    if(x2 != x1 && y2 != y1) {
        if(drivingNorth && drivingEast) {
            distanceCrossValue *= -1;
        } else if(!drivingNorth && drivingEast) {
            distanceCrossValue *= -1;
        }
    } else if(x2 != x1) {
        if(drivingEast) {
            distanceCrossValue *= -1;
        }
    } else if(y2 != y1) {
        if(drivingNorth) {
           distanceCrossValue *= -1;
        }
    }

    //get the slope of the line from p1 to p2 in 2D and get the orthogonal angle
    double slope = (y2 - y1) / (x2 - x1);
    double mOrthogonal = -1 / slope;
    double mAngle = atan(mOrthogonal);

    //get the distance between p1-p2 and between p2-p3
    double distance23 = this->get2dDistance(p2, p3);

    //calculate the ratio between the distance in driving and cross direction in metres and coordinates
    double distanceRatioMetres = distanceCrossValue / distanceLongValue;
    double distanceRatioCoordinates = distance23 * distanceRatioMetres;

    //calculate the new points by using polar coordinates
    double xResult = x1 + distanceRatioCoordinates * cos(mAngle);
    double yResult = y1 + distanceRatioCoordinates * sin(mAngle);
    double zResult = crossDepth - offset;

    //create the result string
    QString result = QString::number(xResult, 'f', 10) + ";" +
                     QString::number(yResult, 'f', 10) + ";" +
                     QString::number(zResult, 'f', 10);

    return result;
}

/*
 *!
 * \brief Zeb2PointCloud::getPointCrossingDirection
 * This function calculates a new point, which is located on the orthongonaly crossing line of a line between 2 points.
 * First a curve between 2 given points will be calculated.
 * Then the given distance in metres will be converted in a distance in coordinates (i.e. coords can be in EPSG: 4326/WGS84)
 * Crossing line and a circle will be created (base is p1).
 * The 2 intersections between circle and crossing line will be calculated.
 * At the end, one of the two intersections have to be chosen as the searched point,
 * depending on which side corresponding to the first line the new point has to be.
 * No exception handling or else implemented, if coordinates can not extracted by the function.
 * \param p1 QString containing the coordinates of point 1 (coords separeted by semicolon), where the crossing line starts of
 * \param p2 QString containing the coordinates of point 2 (coords separeted by semicolon), end point of the line in driving direction
 * \param p3 QString containing the coordinates of point 3 (coords separeted by semicolon), the starting point of the line in driving direction
 * \param distanceCrossValue the distance between point in crossing direction and p1 in metres
 * \param distanceLongValue the distance between p2 and p3 in metres
 * \param side 'r' or 'l' are allowed, means on which side in driving direction the resulting point has to be
 * \param crossDepth the height value of the cross beam/point
 * \param offset the offset of the crossing height, so that transverse profil can be connected with the HMP
 * \param te a pointer to a QTextEdit for logging information
 * \return a new 3D-point as QString, the values will be separeted by semicolon (x;y;z)
 *
QString Zeb2PointCloud::getPointCrossingDirection(QString p1,
                                                  QString p2,
                                                  QString p3,
                                                  double distanceCrossValue,
                                                  int distanceLongValue,
                                                  char side,
                                                  double crossDepth,
                                                  double offset,
                                                  QTextEdit *te) {
    //extract the coordinates from strings
    double x1 = p1.split(";").at(0).toDouble();
    double y1 = p1.split(";").at(1).toDouble();
    double z1 = p1.split(";").at(2).toDouble();

    double x2 = p2.split(";").at(0).toDouble();
    double y2 = p2.split(";").at(1).toDouble();
    double z2 = p2.split(";").at(2).toDouble();

    double x3 = p3.split(";").at(0).toDouble();
    double y3 = p3.split(";").at(1).toDouble();
    double z3 = p3.split(";").at(2).toDouble();

    //get the slope of the line from p1 to p2 in 2D
    double m = (y2 - y1) / (x2 - x1);

    //now get the orthogonal slope
    double mOrthogonal = -1 / m;

    //calculate the last parametre for our orthogonaly equation through p1
    double n = y1 - (mOrthogonal * x1);

    //get the distance between p1-p2 and between p2-p3
    //double distance12 = this->get3dDistance(p1, p2);
    double distance23 = this->get3dDistance(p2, p3);

    //calculate the ratio between the distance in driving and cross direction in metres and coordinates
    double distanceRatioMetres = distanceCrossValue / distanceLongValue;
    double distanceRatioCoordinates = distance23 * distanceRatioMetres;

    //now calculate the point of orthogonaly equation by using the distance ratio
    double discriminant = qPow(distanceRatioCoordinates, 2) * (qPow(mOrthogonal, 2) + 1) - (n + mOrthogonal * x1 - y1);

    //check, if discriminant is positive (otherwise the result will be a complex number)
    if(discriminant >= 0.0) {
        //calculate both intersection points between circle and line
        double xResult1 = x1 + (-1 * mOrthogonal * (n + mOrthogonal * x1 - y1) + qSqrt(discriminant)) / (qPow(mOrthogonal, 2) + 1);
        double xResult2 = x1 + (-1 * mOrthogonal * (n + mOrthogonal * x1 - y1) - qSqrt(discriminant)) / (qPow(mOrthogonal, 2) + 1);
        double yResult1 = mOrthogonal * xResult1 + n;
        double yResult2 = mOrthogonal * xResult2 + n;
        double zResult = z1 + crossDepth - offset;

        //get the information, on which side the two results are standing
        double xResultOnLine = (yResult1 - n) / m;
        int right;
        int left;

        if(y2 > y1) {
            if(xResultOnLine < xResult1) {
                right = 1;
                left = 2;
            } else {
                right = 2;
                left = 1;
            }
        } else if(y2 < y1) {
            if(xResultOnLine > xResult1) {
                right = 1;
                left = 2;
            } else {
                right = 2;
                left = 1;
            }
        } else {
            if(x2 > x1) {
                if(yResult1 < y1) {
                    right = 1;
                    left = 2;
                } else {
                    right = 2;
                    left = 1;
                }
            } else {
                if(yResult1 > y1) {
                    right = 1;
                    left = 2;
                } else {
                    right = 2;
                    left = 1;
                }
            }
        }

        //extract the searched point of intersection
        QString result;
        switch(side) {
            case 'l':
                if(left == 1) {
                    result = QString::number(xResult1, 'f', 10) + ";" + QString::number(yResult1, 'f', 10) + ";" + QString::number(zResult, 'f', 10);
                } else {
                    result = QString::number(xResult2, 'f', 10) + ";" + QString::number(yResult2, 'f', 10) + ";" + QString::number(zResult, 'f', 10);
                }
                break;
            case 'r':
                if(right == 1) {
                    result = QString::number(xResult1, 'f', 10) + ";" + QString::number(yResult1, 'f', 10) + ";" + QString::number(zResult, 'f', 10);
                } else {
                    result = QString::number(xResult2, 'f', 10) + ";" + QString::number(yResult2, 'f', 10) + ";" + QString::number(zResult, 'f', 10);
                }
                break;
            default:
                break;
        }
        return result;

    } else {
        te->insertPlainText("Discrimant < 0 at point (" + p1 + ")\n");
        QTextCursor c = te->textCursor();
        c.movePosition(QTextCursor::End);
        te->setTextCursor(c);
        return "";
    }
}
*/

/*!
 * \brief Zeb2PointCloud::get3dPointWithMeasuredHeight
 * This functions add 2 additional heights on the z-coordinate of a 3D-point.
 * \param p1 QString containing the coordinates of point 1 (coords separeted by semicolon)
 * \param transverseValue the height from the transverse profil
 * \param offset the offset between HMP and transverse profil
 * \return a new 3D-point as QString, the values will be separeted by semicolon (x;y;z)
 */
QString Zeb2PointCloud::get3dPointWithMeasuredHeight(QString p1, QString transverseValue, double offset) {
    //extract the z-coordinate from string
    QString x1 = p1.split(";").at(0);
    QString y1 = p1.split(";").at(1);
    double z1 = p1.split(";").at(2).toDouble();

    //add the measured values to the height
    double z2 = z1 + transverseValue.toDouble() - offset;

    //create the new coordinate-string
    QString result = x1 + ";" + y1 + ";" + QString::number(z2, 'f', 10);
    return result;
}

/*!
 * \brief Zeb2PointCloud::synchroniseLfdmValues
 * This function synchronises two lists of coordinates.
 * The result will be two indices, one for each given list.
 * The two indices contains the index of each list, where the coordinates have to lowest distance.
 * \param listCoords1 list of QStrings containing coordinates (coords separeted by semicolon)
 * \param listCoords2 list of QStrings containing coordinates (coords separeted by semicolon)
 * \param startIndex1 integer where the synchronised starting index of list 1 will be stored
 * \param startIndex2 integer where the synchronised starting index of list 2 will be stored
 */
void Zeb2PointCloud::synchroniseLfdmValues(QList<QString> listCoords1,
                                           QList<QString> listCoords2,
                                           int &startIndex1, int &startIndex2) {
    //check first, if listCoords1 starts in front of listCoords2
    double diff = this->get2dDistance(listCoords1.value(0), listCoords2.value(0));
    bool distanceIncreasing = false;

    for(int i = 1; i < listCoords1.size(); i++) {
        double diffTemp = this->get2dDistance(listCoords1.value(i), listCoords2.value(0));
        if(diff > diffTemp) {
            diff = diffTemp;
        } else {
            if (i == 1) {
               distanceIncreasing = true;
            } else {
                startIndex1 = i;
                startIndex2 = 0;
            }
            break;
        }
    }

    //check, if map2 starts in front on map1
    if(distanceIncreasing) {
        diff = this->get2dDistance(listCoords1.value(0), listCoords2.value(0));
        for(int i = 1; i < listCoords2.size(); i++) {
            double diffTemp = this->get2dDistance(listCoords2.value(i), listCoords1.value(0));
            if(diff > diffTemp) {
                diff = diffTemp;
            } else {
                startIndex2 = i;
                startIndex1 = 0;
                break;
            }
        }
    }
}
