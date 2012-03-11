#!/bin/bash
# Script d'installation et de mise à jour de la SFML 2.0 et des dépendances necessaires pour compiler le projet Sphero
# https://github.com/xdbob/Sphero

clean()
{
	cd /
	rm -rf /SFML
}

clear
if [ "$(id -u)" != "0" ]; then
	echo "Vous devez lancer le script en tant que root (sudo)"
	exit 0
fi
echo "Installation des dépendances + Qt4"
read -p "Pressez la touche [Entrée] ([Ctrl + C] Pour arrêter) pour continuer ..." readEnterKey
apt-get install -y make cmake git g++ build-essential libgl1-mesa-dev libglew1.5-dev libxrandr-dev libsndfile1-dev libopenal-dev libpng12-dev libfreetype6-dev libjpeg62-dev doxygen libqt4-dev
if (( $? == 0 )); then
	echo "Succès"
else
	echo "Erreur lors de l'installation des dépendances"
	echo "Il se peut qu'il y ait un bug avec le sudo ./script.sh, essayez avec la commande \"sudo bash script.sh\""
	exit 50
fi
echo "Test de l'existence de /SFML => si oui, destruction"
read -p "Pressez la touche [Entrée] ([Ctrl + C] Pour arrêter) pour continuer ..." readEnterKey
if [ -d /SFML ]; then
	rm -rf /SFML
	if (( $? == 0 )); then
		echo "Suppression de /SFML => succès"
	else
		exit 125
	fi
fi
echo "Création et Déplacement dans /SFML"
read -p "Pressez la touche [Entrée] ([Ctrl + C] Pour arrêter) pour continuer ..." readEnterKey
mkdir /SFML
if (( $? == 0 )); then
	echo "Succès"
else
	echo "Impossible de créer le dossier /SFML"
	exit 150
fi
chmod 777 /SFML
if (( $? != 0 )); then
	exit 175
fi
cd /SFML
echo "Téléchargement des sources de la SFML 2.0"
read -p "Pressez la touche [Entrée] ([Ctrl + C] Pour arrêter) pour continuer ..." readEnterKey
git clone https://github.com/LaurentGomila/SFML.git .
if (( $? == 0 )); then
	echo "Succès"
else
	echo "Impossible de télécharger les sources de la SFML"
	exit 200
fi
echo "Building de la SFML en Release Dynamique"
cmake -G "Unix Makefiles" -D CMAKE_BUILD_TYPE=Release -D BUILD_SHARED_LIBS=TRUE .
if (( $? != 0)); then
	clean
	exit 300
fi
make
if (( $? != 0)); then
	clean
	exit 300
fi
echo "Installation"
make install
if (( $? != 0)); then
	clean
	exit 300
fi
echo "Building de la SFML en Debug Dynamique"
cmake -G "Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug -D BUILD_SHARED_LIBS=TRUE .
if (( $? != 0)); then
	clean
	exit 300
fi
make
if (( $? != 0)); then
	clean
	exit 300
fi
make install
if (( $? != 0)); then
	clean
	exit 300
fi
echo "Building de la SFML en Release Statique"
cmake -G "Unix Makefiles" -D CMAKE_BUILD_TYPE=Release -D BUILD_SHARED_LIBS=FALSE .
if (( $? != 0)); then
	clean
	exit 300
fi
make
if (( $? != 0)); then
	clean
	exit 300
fi
make install
if (( $? != 0)); then
	clean
	exit 300
fi
echo "Building de la SFML en Debug Statique"
cmake -G "Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug -D BUILD_SHARED_LIBS=FALSE .
if (( $? != 0)); then
	clean
	exit 300
fi
make
if (( $? != 0)); then
	clean
	exit 300
fi
make install
if (( $? != 0)); then
	clean
	exit 300
fi
echo "L'installation est un succès"
exit 0