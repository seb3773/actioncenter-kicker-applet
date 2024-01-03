#!/bin/bash
updates=0
if [ $updates -eq 0 ]; then
echo "Votre systeme est a jour."
else
echo "Des mises a jours sont disponibles."
echo " "
echo "Vous pouvez les installer en cliquant sur"
echo "l'icone du gestionnaire de mises a jour"
echo "dans la zone de notifications de la barre des taches"
fi