#-------------------------------------------------
#
# Project created by QtCreator 2016-08-22T17:38:24
#
#    qZeb3D - calculating 3D-point-clouds from Georawfiles/Georohdaten of german ZEB
#    Copyright (C) 2016 Christoph Jung
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#-------------------------------------------------

QT       += core gui
QT       += xml
QT       += datavisualization

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qZeb3D
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ZebData/Rawdata/track.cpp \
    ZebData/Rawdata/camera.cpp \
    ZebData/Rawdata/longitudinal.cpp \
    ZebData/Rawdata/transverse.cpp \
    ZebData/Rawdata/damage.cpp \
    ZebData/zebfiles.cpp \
    ZebData/zebparser.cpp \
    controller.cpp \
    Utilities/settings.cpp \
    PointCloud/zeb2pointcloud.cpp \
    PointCloud/pointcloud.cpp

HEADERS  += mainwindow.h \
    ZebData/Rawdata/track.h \
    ZebData/Rawdata/camera.h \
    ZebData/Rawdata/longitudinal.h \
    ZebData/Rawdata/transverse.h \
    ZebData/Rawdata/damage.h \
    ZebData/zebfiles.h \
    ZebData/zebparser.h \
    controller.h \
    Utilities/settings.h \
    PointCloud/zeb2pointcloud.h \
    PointCloud/pointcloud.h

FORMS    += mainwindow.ui

DISTFILES += Settings/mainsettings.ini

RESOURCES += \
    resources.qrc
