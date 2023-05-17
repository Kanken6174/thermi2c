# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = thermi2c

CONFIG += sailfishapp

SOURCES += src/thermi2c.cpp \
    src/MLX90640_API.cpp \
    src/MLX90640_I2C_Driver.cpp \
    src/conv.cpp \
    src/i2cdriversingleton.cpp \
    src/i2cif.cpp

DISTFILES += qml/thermi2c.qml \
    qml/cover/CoverPage.qml \
    qml/pages/FirstPage.qml \
    qml/pages/SecondPage.qml \
    rpm/thermi2c.changes.in \
    rpm/thermi2c.changes.run.in \
    rpm/thermi2c.spec \
    translations/*.ts \
    thermi2c.desktop

SAILFISHAPP_ICONS = 86x86 108x108 128x128 172x172

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n

# German translation is enabled as an example. If you aren't
# planning to localize your app, remember to comment out the
# following TRANSLATIONS line. And also do not forget to
# modify the localized app name in the the .desktop file.
TRANSLATIONS += translations/thermi2c-de.ts

HEADERS += \
    src/MLX90640_API.h \
    src/MLX90640_I2C_Driver.h \
    src/conv.h \
    src/i2cdriversingleton.h \
    src/i2cif.h
