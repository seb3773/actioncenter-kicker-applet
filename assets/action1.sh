#!/bin/bash
night=("1:0.9:0.90" "1:0.9:0.85" "1:0.85:0.8" "1:0.80:0.75" "1:0.80:0.7" "1:0.75:0.65" "1:0.75:0.6" "1:0.75:0.55" "1:0.75:0.5" "1:0.75:0.4");nightb=("0.9" "0.9" "0.9" "0.8" "0.8" "0.8" "0.8" "0.7" "0.7" "0.7");day=("1:0.75:0.5" "1:0.75:0.55" "1:0.75:0.6" "1:0.75:0.65" "1:0.8:0.7" "1:0.8:0.75" "1:0.85:0.8" "1:0.9:0.85" "1:0.9:0.9" "1:1:1");dayb=("0.7" "0.7" "0.8" "0.8" "0.8" "0.8" "0.9" "0.9" "0.9" "1")
getbr(){ local v=$(xrandr --verbose | grep Brightness | cut -d ' ' -f 2 | head -n 1);echo "$v";}
apply(){ local mgam=("${!1}");local mbr=("${!2}");local condp=("${!3}")
for ((i=0;i<${#mgam[@]};i++));do cmd=""
for d in "${condp[@]}";do cmd+=" --output $d --gamma ${mgam[$i]} --brightness ${mbr[$i]}";done;xrandr $cmd;done;}
vbr=$(getbr);if [ "$1" == "check" ];then if [ "$vbr" == "1.0" ];then echo 1;exit
elif [ "$vbr" == "0.70" ];then echo 0;exit;fi;else condpl=($(xrandr | grep -E ' connected( primary)? [0-9]+x[0-9]+' | awk '{print $1}'))
if [ "$vbr" == "1.0" ];then apply night[@] nightb[@] condpl[@];else apply day[@] dayb[@] condpl[@];fi;fi
