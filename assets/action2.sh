#!/bin/bash
radio="$(LC_MESSAGES=C nmcli radio all | awk 'FNR == 2 {print $2}')"
if [ "$1" == "check" ];then
if [ "$radio" == "enabled" ];then echo 1;else echo 0;fi; exit
else if [ "$radio" == "enabled" ];then nmcli radio all off;else nmcli radio all on;fi;fi