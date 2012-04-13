Configuration requise
=====================

Windows
-------

cmake
make
MinGW

SFML 2.0 compilée avec les outils précénts et installée dans C:\SFML

QtSDK (+sources) > 4.7

Changez le fichier \QtSDK\Desktop\Qt\4.X.X\mingw\include\QtCore\private\qwineventnotifier_p.h:
// #include "../../../src/corelib/kernel/qwineventnotifier_p.h"
 #include "../../../../../../../QtSources/4.X.X/src/corelib/kernel/qwineventnotifier_p.h"

Linux
-----

apt-get et bash (installées par défaut sur ubuntu, debian etc.)
Lancer en root dependances.sh pour préparer l'environnement de compilation. (sudo bash dependances.sh)

MacOS (non testé)
-----------------

cmake
make
g++
SFML 2.0 (dans /SFML)
Qt

DLL à inclure avec l'exe (Windows)
==================================

Debug
-----
-libgcc_s_dw2-1.dll
-libstdc++-6.dll
-mingwm10.dll
-QtCored4.dll
-QtGuid4.dll
-sfml-system-d-2.dll
-sfml-window-d-2.dll

Release
-------
-libgcc_s_dw2-1.dll
-libstdc++-6.dll
-mingwm10.dll
-QtCore4.dll
-QtGui4.dll
-sfml-system-2.dll
-sfml-window-2.dll