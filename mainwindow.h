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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QHash>
#include <QMessageBox>
#include <QString>
#include <QSettings>
#include <QTextStream>
#include <QTreeWidgetItem>
#include <QtDataVisualization>
#include <QtDataVisualization/Q3DScatter>
#include <QFont>
#include <QtDataVisualization/QScatterDataProxy>
#include <QtDataVisualization/QHeightMapSurfaceDataProxy>
#include <QtDataVisualization/QScatter3DSeries>
#include <QWidget>
#include <QFileDialog>
#include <QFileInfo>
#include "controller.h"
#include "ZebData/zebfiles.h"
#include "ZebData/zebparser.h"
#include "ZebData/Rawdata/track.h"

using namespace QtDataVisualization;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QString mainSettingsPath;
    Controller controller;
    Q3DScatter *graph;
    QScatterDataProxy *graphProxy;
    QScatter3DSeries *graphSeries;
    QWidget *container;
    QDialog *info;

    void displayZebTrack(QString trackNumber);
    void initViewer();

private slots:
    void on_pushButton_import_clicked();

    void on_pushButton_export_clicked();

    void on_actionImport_triggered();

    void on_actionExport_triggered();

    void on_actionEnglish_triggered();

    void on_actionFrench_triggered();

    void on_actionGerman_triggered();

    void on_actionPolish_triggered();

    void on_actionInfo_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
