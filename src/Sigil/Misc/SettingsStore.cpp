/************************************************************************
**
**  Copyright (C) 2011  John Schember <john@nachtimwald.com>
**
**  This file is part of Sigil.
**
**  Sigil is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  Sigil is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with Sigil.  If not, see <http://www.gnu.org/licenses/>.
**
*************************************************************************/

#include <QtCore/QLocale>
#include <QtCore/QCoreApplication>
#include <QtGui/QDesktopServices>

#include "Misc/SettingsStore.h"
#include "sigil_constants.h"

static QString SETTINGS_GROUP = "user_preferences";
static QString KEY_DEFAULT_METADATA_LANGUAGE = SETTINGS_GROUP + "/" + "default_metadata_lang";
static QString KEY_UI_LANGUAGE = SETTINGS_GROUP + "/" + "ui_language";
static QString KEY_ZOOM_IMAGE = SETTINGS_GROUP + "/" + "zoom_image";
static QString KEY_ZOOM_TEXT = SETTINGS_GROUP + "/" + "zoom_text";
static QString KEY_ZOOM_WEB = SETTINGS_GROUP + "/" + "zoom_web";
static QString KEY_RENAME_TEMPLATE = SETTINGS_GROUP + "/" + "rename_template";
static QString KEY_DICTIONARY_NAME = SETTINGS_GROUP + "/" + "dictionary_name";
static QString KEY_SPELL_CHECK = SETTINGS_GROUP + "/" + "spell_check";
static QString KEY_USER_DICTIONARY_NAME = SETTINGS_GROUP + "/" + "user_dictionary_name";
static QString KEY_CLEAN_LEVEL = SETTINGS_GROUP + "/" + "clean_level";

SettingsStore::SettingsStore()
    : QSettings(QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName())
{
}

QString SettingsStore::uiLanguage()
{
    clearSettingsGroup();
    return value(KEY_UI_LANGUAGE, QLocale::system().name()).toString();
}

QString SettingsStore::defaultMetadataLang()
{
    clearSettingsGroup();
    return value(KEY_DEFAULT_METADATA_LANGUAGE, "en").toString();
}

float SettingsStore::zoomImage()
{
    clearSettingsGroup();
    return value(KEY_ZOOM_IMAGE, ZOOM_NORMAL).toFloat();;
}

float SettingsStore::zoomText()
{
    clearSettingsGroup();
    return value(KEY_ZOOM_TEXT, ZOOM_NORMAL).toFloat();
}

float SettingsStore::zoomWeb()
{
    clearSettingsGroup();
    return value(KEY_ZOOM_WEB, ZOOM_NORMAL).toFloat();
}

QString SettingsStore::dictionary()
{
    clearSettingsGroup();
    return value(KEY_DICTIONARY_NAME, "en_US").toString();
}

bool SettingsStore::spellCheck()
{
    clearSettingsGroup();
    return static_cast<bool>(value(KEY_SPELL_CHECK, true).toBool());
}

QString SettingsStore::userDictionaryName()
{
    clearSettingsGroup();
    return value(KEY_USER_DICTIONARY_NAME, "default").toString();
}

QString SettingsStore::renameTemplate()
{
    clearSettingsGroup();
    return value(KEY_RENAME_TEMPLATE, "Section001").toString();
}

SettingsStore::CleanLevel SettingsStore::cleanLevel()
{
    clearSettingsGroup();

    int level = value(KEY_CLEAN_LEVEL, SettingsStore::CleanLevel_Off).toInt();
    switch (level) {
        case SettingsStore::CleanLevel_Off:
        case SettingsStore::CleanLevel_PrettyPrint:
        case SettingsStore::CleanLevel_Tidy:
            return static_cast<SettingsStore::CleanLevel>(level);
            break;
        default:
            return SettingsStore::CleanLevel_Off;
    }
}

void SettingsStore::setDefaultMetadataLang(const QString &lang)
{
    clearSettingsGroup();
    setValue(KEY_DEFAULT_METADATA_LANGUAGE, lang);
}

void SettingsStore::setUILanguage(const QString &language_code)
{
    clearSettingsGroup();
    setValue(KEY_UI_LANGUAGE, language_code);
}

void SettingsStore::setZoomImage(float zoom)
{
    clearSettingsGroup();
    setValue(KEY_ZOOM_IMAGE, zoom);
}

void SettingsStore::setZoomText(float zoom)
{
    clearSettingsGroup();
    setValue(KEY_ZOOM_TEXT, zoom);
}

void SettingsStore::setZoomWeb(float zoom)
{
    clearSettingsGroup();
    setValue(KEY_ZOOM_WEB, zoom);
}

void SettingsStore::setDictionary(const QString &name)
{
    clearSettingsGroup();
    setValue(KEY_DICTIONARY_NAME, name);
}

void SettingsStore::setSpellCheck(bool enabled)
{
    clearSettingsGroup();
    setValue(KEY_SPELL_CHECK, enabled);
}

void SettingsStore::setUserDictionaryName(const QString &name)
{
    clearSettingsGroup();
    setValue(KEY_USER_DICTIONARY_NAME, name);
}

void SettingsStore::setRenameTemplate(const QString &name)
{
    clearSettingsGroup();
    setValue(KEY_RENAME_TEMPLATE, name);
}

void SettingsStore::setCleanLevel(SettingsStore::CleanLevel level)
{
    clearSettingsGroup();
    setValue(KEY_CLEAN_LEVEL, level);
}

void SettingsStore::clearSettingsGroup()
{
    while (!group().isEmpty()) {
        endGroup();
    }
}

QString SettingsStore::defaultDictionaryDirectory()
{
    return QDesktopServices::storageLocation(QDesktopServices::DataLocation) + "/dictionaries";
}
