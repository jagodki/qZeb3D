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

#include "settings.h"

Settings::Settings(QObject *parent) : QObject(parent) {

}

/*!
 * \brief Settings::loadSettings
 * Loads a setting file, extracts the information of the application language and loads the translation file.
 * If no language-key will be found in the settingsfile, than the english translation will be loaded.
 * \param log
 * \return true if all was correct, otherwise false
 */
bool Settings::loadSettings() {
    //store pah to settings file with QT-separators
    this->settingsPath = QDir::fromNativeSeparators(QApplication::applicationDirPath()) + "/Settings/mainsettings.ini";
    this->settingsPath = QDir::toNativeSeparators(this->settingsPath);

    //hard coded Unix-path for testing
    //this->settingsPath = "/Users/Christoph/GitHub/qzeb3d/Settings/mainsettings.ini";

    if(!QFile(this->settingsPath).exists()) {
        this->loadLanguage("://Translations/translation_en.ini");
        return false;
    } else {
        //load settings file
        QSettings settings(this->settingsPath, QSettings::IniFormat);

        //parse language
        this->language = settings.value("language").toString();
        if(this->language == "en" || this->language == "") {
            settings.setValue("language", "en");
            this->loadLanguage("://Translations/translation_en.ini");
        } else if(this->language == "pl") {
            this->loadLanguage(":/Translations/translation_pl.ini");
        } else if(this->language == "fr") {
            this->loadLanguage(":/Translations/translation_fr.ini");
        } else if(this->language == "de") {
            this->loadLanguage(":/Translations/translation_de.ini");
        }
        return true;
    }
}

/*!
 * \brief Settings::loadLanguage
 * Loads a language file and parses the content of the file in the message-object (key-value-pairing)
 * \param path the absolute path as QString to the translation file
 */
void Settings::loadLanguage(QString path) {
    QFile langFile(path);
    langFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream langTextStream(&langFile);
    while(!langTextStream.atEnd()) {
        QString currentLine = langTextStream.readLine();
        this->keys.append(currentLine.split("=")[0]);
        this->values.append(currentLine.split("=")[1]);
    }
}

void Settings::setMessage(QString key, QString value) {
    this->messages.insert(key, value);
}

QString Settings::getMessage(QString key) {
    QString result = "";
    int maxSize = this->keys.size();
    for(int i = 0; i < maxSize; i++) {
        if(this->keys.at(i) == key) {
            result = this->values.at(i);
            break;
        }
    }
    return result;
}

/*!
 * \brief Settings::getSetting
 * Returns the value of a property in the settings file.
 * \param key the identificator of the property
 * \return the value as QString corresponding to the given key
 */
QString Settings::getSetting(QString key) {
    QSettings settings(this->settingsPath, QSettings::IniFormat);
    return settings.value(key).toString();
}

/*!
 * \brief Settings::setSetting
 * Stores a property in the settings file.
 * \param key identificator as QString of the property
 * \param value as QString of the property
 */
void Settings::setSetting(QString key, QString value) {
    QSettings settings(this->settingsPath, QSettings::IniFormat);
    settings.setValue(key, value);
}
