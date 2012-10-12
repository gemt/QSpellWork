# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

# This is a reminder that you are using a generated .pro file.
# Remove it when you are finished editing this file.
message("You are running qmake on a generated .pro file. This may not work!")

QT += webkit core gui network xml sql
TEMPLATE = app
TARGET = QSW
DESTDIR = ../Release
QT += core gui
CONFIG += release
INCLUDEPATH += ./GeneratedFiles \
    ./GeneratedFiles/Release \
    ./Includes \
    .
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/release
OBJECTS_DIR += release
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles

OTHER_FILES += \
    Icon.rc

HEADERS += \
    Alphanum.h \
    SWAboutForm.h \
    SWUpdateForm.h \
    SWMainForm.h \
    SWSearch.h \
    SWObject.h \
    SWEvent.h \
    SWDefines.h \
    DBC/DBCStructure.h \
    DBC/DBCStores.h \
    DBC/DBCStore.h \
    DBC/DBCfmt.h \
    DBC/DBCFileLoader.h \
    Includes/Define.h \
    Includes/CompilerDefs.h \
    Includes/ByteConverter.h

SOURCES += \
    Main.cpp \
    Alphanum.cpp \
    SWAboutForm.cpp \
    SWSearch.cpp \
    SWObject.cpp \
    SWMainForm.cpp \
    SWDefines.cpp \
    SWUpdateForm.cpp \
    DBC/DBCStores.cpp \
    DBC/DBCFileLoader.cpp

FORMS += \
    SWMainUI.ui \
    SWAboutUI.ui \
    SWUpdateUI.ui

RESOURCES += \
    SpellWork.qrc








