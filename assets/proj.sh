#!/bin/bash
if [ "$1" == "txt" ];then
echo "Projeter
Ecran du PC uniquement
Dupliquer
Etendre
Deuxieme ecran uniquement"
exit
fi

if [ "$1" == "pconly" ];then
xrandr --output eDP-1 --auto --primary --output HDMI-1 --off
fi

if [ "$1" == "duplicate" ];then
xrandr --output eDP-1 --auto --primary --output HDMI-1 --auto --same-as eDP-1
#toggle (to do)
#xrandr --output eDP-1 --auto --primary --output HDMI-1 --auto --same-as eDP-1
fi

if [ "$1" == "expand" ];then
xrandr --output eDP-1 --auto --primary --output HDMI-1 --auto --left-of eDP-1
fi

if [ "$1" == "2ndonly" ];then
xrandr --output eDP-1 --off --output HDMI-1 --auto
fi