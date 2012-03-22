#############################################################################
#  Copyright (C) 2012 DAMHET Antoine                                        #
#                                                                           #
#  This program is free software; you can redistribute it and/or modify     #
#  it under the terms of the GNU General Public License as published by     #
#  the Free Software Foundation; either version 2 of the License, or        #
#  (at your option) any later version.                                      #
#                                                                           #
#  This program is distributed in the hope that it will be useful,          #
#  but WITHOUT ANY WARRANTY; without even the implied warranty of           #
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the             #
#  GNU General Public License for more details.                             #
#                                                                           #
#  You should have received a copy of the GNU General Public License along  #
#  with this program; if not, write to the Free Software Foundation, Inc.,  #
#  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.              #
#############################################################################

HEADERS += \
    mainwindow.h \
    core.h \
    debug.h \
    joystick.h \
    network.h

SOURCES += \
    mainwindow.cpp \
    main.cpp \
    core.cpp \
    debug.cpp \
    joystick.cpp \
    network.cpp

FORMS += \
    mainwindow.ui \
    debug.ui

RESOURCES += \
    ressources.qrc

win32{
RC_FILE += ressources.rc

    CONFIG(release, debug|release){
    LIBS += C:/SFML/lib/libsfml-window.a
}
    CONFIG(debug, debug|release){
    LIBS += C:/SFML/lib/libsfml-window-d.a
}
INCLUDEPATH += \
    C:/SFML/include
}

unix{
    CONFIG(release, debug|release){
    LIBS += -L/SFML/lib -lsfml-window
}
    CONFIG(debug, debug|release){
    LIBS += -L/SFML/lib -lsfml-window-d
}
INCLUDEPATH += \
    /SFML/include
}
