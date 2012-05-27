Liste des commandes consoles
============================


##Commandes de base
### quit/exit :
Permet de quitter le programme.
### clean X :
Les commandes sont répétées ou non dans la console.
### echo X :
Affiche X dans la console.

##Commandes de debug
### debug init :
Initialise le module de débug.
### debug :
Affiche la fenêtre de débug.
### debug -i :
Initialise et affiche le module de débug.

##Commandes de connection
### port list (-v) :
Liste tous les ports série du PC l'option -v permet d'afficher toutes les caractéristiques disponibles sur les ports.
### port set X :
Le programme se connecte au port X.
### blink X :
Permet de tester la PWM sur l'arduino Mega ou simplement de tester la connection (bluetooth), 0 <= X < 255 [Si X n'est pas précisé, X = 0].

##Commandes du JoyStick
###joy list :
Affiche le statut de tous les joysticks gérés par le système.
###joy set X :
Affecte le programme au joystick d'ID X
###joy start :
Lance la capture du joystick
###joy stop :
Arrête la capture du joystick