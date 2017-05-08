/*
     .-')       .-') _   ('-. .-. .-')           _ .-') _
   .(  OO)     (  OO) )_(  OO)\  ( OO )         ( (  OO) )
  (_)---\_)  ,(_)----.(,------.;-----.\  .-----. \     .'_
  '  .-.  '  |       | |  .---'| .-.  | /  -.   \,`'--..._)
 ,|  | |  |  '--.   /  |  |    | '-' /_)'-' _'  ||  |  \  '
(_|  | |  |  (_/   /  (|  '--. | .-. `.    |_  < |  |   ' |
  |  | |  |   /   /___ |  .--' | |  \  |.-.  |  ||  |   / :
  '  '-'  '-.|        ||  `---.| '--'  /\ `-'   /|  '--'  /
   `-----'--'`--------'`------'`------'  `----'' `-------'

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
#include <QApplication>
#include <QtDataVisualization>
#include <Q3DSurface>

using namespace QtDataVisualization;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
