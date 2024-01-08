#!/bin/bash
maj=$(xdotool search --onlyvisible "updatemgr.exu")
if [ -n "$maj" ]; then
echo "Mises a jour en cours..."
exit;fi
wid=$(xdotool search --onlyvisible "q4os-pkui")
if [ -n "$wid" ]; then
echo "Des mises a jours sont disponibles."
echo " "
echo "Vous pouvez les installer en cliquant sur"
echo "l'icone du gestionnaire de mises a jour"
echo "dans la zone de notifications de la barre des taches"
else
echo "Votre systeme est a jour."
fi
