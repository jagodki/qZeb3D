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

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    graph(new Q3DScatter()){
    //load settings
    if(!this->controller.loadSettings()) {
        QMessageBox::information(this, "", "cannot find settings");
    }

    //setup all windows/dialogs
    ui->setupUi(this);

    //adjust the labelling of all buttons
    this->ui->pushButton_import->setText(this->controller.getMessage("import"));
    this->ui->pushButton_import->setToolTip(this->controller.getMessage("import"));
    this->ui->actionImport->setText(this->controller.getMessage("import"));
    this->ui->actionImport->setToolTip(this->controller.getMessage("import"));
    this->ui->pushButton_export->setText(this->controller.getMessage("export"));
    this->ui->pushButton_export->setToolTip(this->controller.getMessage("export"));
    this->ui->actionExport->setText(this->controller.getMessage("export"));
    this->ui->actionExport->setToolTip(this->controller.getMessage("export"));
    this->ui->actionInfo->setToolTip(this->controller.getMessage("information"));
    this->ui->menuLanguage->setTitle(this->controller.getMessage("lang"));
    this->ui->menuFile->setTitle(this->controller.getMessage("file"));

    this->initViewer();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_import_clicked() {
    //open FileDialog
    QString filename = QFileDialog::getOpenFileName(
                this,
                this->controller.getMessage("openfile"),
                this->controller.getSetting("importpath"),
                this->controller.getMessage("allfiles") + " (*.*);;" + controller.getMessage("zebfiles") + " (*.xml)");

    if(filename.isEmpty()) {
        QMessageBox::information(this, this->controller.getMessage("information"), this->controller.getMessage("nofileselected"));
    } else {
        //store the selected path in settings
        this->controller.setSetting("importpath", QFileInfo(filename).dir().absolutePath());

        int result = this->controller.importSingleTrack(filename, this->ui->textEdit);
        switch (result) {
            case -1:
                QMessageBox::information(this, this->controller.getMessage("information"), controller.getMessage("cannotfindtp3"));
                break;
            case -2:
                QMessageBox::warning(this, this->controller.getMessage("problem"), controller.getMessage("cannotfind1a1b"));
                break;
            case -3:
                QMessageBox::warning(this, this->controller.getMessage("problem"), controller.getMessage("cannotimporttp1a"));
                break;
            case -4:
                QMessageBox::warning(this, this->controller.getMessage("problem"), controller.getMessage("cannotimporttp1b"));
                break;
            case -5:
                QMessageBox::information(this, this->controller.getMessage("information"), controller.getMessage("cannotimporttp3"));
                break;
            default:
                break;
        }

        //add the imported track to the gui/tree widget, if import was successfull
        if(result == 0 || result == -1 || result == -5) {
            //create root element
            QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
            item->setText(0, this->controller.getDataName(filename, "zeb"));
            //ui->treeWidget->addTopLevelItem(item);

            //create element for TP1a
            QTreeWidgetItem *item1a = new QTreeWidgetItem();
            item1a->setText(0, "TP1a");
            item->addChild(item1a);

            //create element for TP1b
            QTreeWidgetItem *item1b = new QTreeWidgetItem();
            item1b->setText(0, "TP1b");
            item->addChild(item1b);

            //create element for TP3
            if(result == 0) {
                QTreeWidgetItem *item3 = new QTreeWidgetItem();
                item3->setText(0, "TP3");
                item->addChild(item3);
            }

            //create a pointcloud from the given zeb-track
            controller.convertZebToPointCloud(controller.getDataName(filename, "zeb"), ui->progressBar, 5, this->ui->textEdit);

            //display the pointcloud
            this->displayZebTrack(this->controller.getDataName(filename, "zeb"));
        } else {
            this->ui->textEdit->insertPlainText(
                        QDateTime::currentDateTime().toString() +
                        " - " + this->controller.getMessage("notabletocalcualtepointcloud") + "\n");
        }
    }
}

void MainWindow::displayZebTrack(QString trackNumber) {
    //init data-objects
    this->graphProxy = new QScatterDataProxy();
    this->graphSeries = new QScatter3DSeries(this->graphProxy);
    this->graphSeries->setItemLabelFormat(QStringLiteral("@xTitle: @xLabel @yTitle: @yLabel @zTitle: @zLabel"));
    this->graphSeries->setMeshSmooth(true);
    this->graph->addSeries(graphSeries);

    //populate the data-array
    QScatterDataArray *dataArray = new QScatterDataArray;
    this->controller.loadPointCloudDataArray(trackNumber, dataArray);

    //set data-array into proxy
    this->graphProxy->resetArray(dataArray);
    this->graph->show();
}

void MainWindow::initViewer() {
    this->container = QWidget::createWindowContainer(graph);
    this->ui->verticalLayout->addWidget(this->container);

    if (!graph->hasContext()) {
        QMessageBox::warning(this, this->controller.getMessage("information"), this->controller.getMessage("opengl"));
    }

    this->graph->activeTheme()->setType(Q3DTheme::Theme(0));
    QFont font = this->graph->activeTheme()->font();
    font.setPointSize(40.0f);
    this->graph->activeTheme()->setFont(font);
    this->graph->setShadowQuality(QAbstract3DGraph::ShadowQualitySoftLow);
    this->graph->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetFront);

    // Configure the axes according to the data
    this->graph->axisX()->setTitle(QStringLiteral("Latitude"));
    this->graph->axisY()->setTitle(QStringLiteral("Height"));
    this->graph->axisZ()->setTitle(QStringLiteral("Longitude"));
    this->graph->axisX()->setAutoAdjustRange(true);
    this->graph->axisY()->setAutoAdjustRange(true);
    this->graph->axisZ()->setAutoAdjustRange(true);
}

void MainWindow::on_pushButton_export_clicked() {
    QString filename = QFileDialog::getSaveFileName(
                this,
                this->controller.getMessage("exportfile"),
                this->controller.getSetting("exportpath"),
                this->controller.getMessage("allfiles") + " (*.*);;" +
                this->controller.getMessage("zebfiles") + " (*.xml)");

    if(filename.isEmpty()) {
        QMessageBox::information(this, this->controller.getMessage("information"), this->controller.getMessage("notrackselected"));
    } else {
        //store the selected path in settings
        this->controller.setSetting("exportpath", QFileInfo(filename).dir().absolutePath());

        //start export
        this->controller.exportPointCloud(filename, this->ui->treeWidget->selectedItems().at(0)->text(0), this->ui->progressBar, this->ui->textEdit);
    }
}

void MainWindow::on_actionImport_triggered() {
    this->on_pushButton_import_clicked();
}

void MainWindow::on_actionExport_triggered() {
    this->on_pushButton_export_clicked();
}

void MainWindow::on_actionEnglish_triggered() {
    this->controller.setSetting("language", "en");
    QMessageBox::information(this, this->controller.getMessage("information"), "please restart the software to change the language");
}

void MainWindow::on_actionFrench_triggered() {
    this->controller.setSetting("language", "fr");
    QMessageBox::information(this, this->controller.getMessage("information"), "veuillez redémarrer le logiciel pour changer la langue");
}

void MainWindow::on_actionGerman_triggered() {
    this->controller.setSetting("language", "de");
    QMessageBox::information(this, this->controller.getMessage("information"), "bitte das Programm neustarten, um die Sprache zu wechseln");
}

void MainWindow::on_actionPolish_triggered() {
    this->controller.setSetting("language", "pl");
    QMessageBox::information(this, this->controller.getMessage("information"), "proszę zrestartuj oprogramowanie, aby zmienić język");
}

void MainWindow::on_actionInfo_triggered() {
    QMessageBox::about(this, "",
                         this->controller.getSetting("appname") + "\n" +
                         "Version: " + this->controller.getSetting("appversion") + "\n" +
                         "written by: " + this->controller.getSetting("appauthor") + "\n" +
                         "GitHub: " + this->controller.getSetting("appgithub"));
}
