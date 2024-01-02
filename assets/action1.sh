#!/bin/bash
nightmode() {
xrandr --output "$1" --gamma 1.0:0.9:0.90 --brightness 0.9
xrandr --output "$1" --gamma 1.0:0.9:0.85 --brightness 0.9
xrandr --output "$1" --gamma 1.0:0.85:0.80 --brightness 0.9
xrandr --output "$1" --gamma 1.0:0.80:0.75 --brightness 0.8
xrandr --output "$1" --gamma 1.0:0.80:0.70 --brightness 0.8
xrandr --output "$1" --gamma 1.0:0.75:0.65 --brightness 0.8
xrandr --output "$1" --gamma 1.0:0.75:0.60 --brightness 0.8
xrandr --output "$1" --gamma 1.0:0.75:0.55 --brightness 0.7
xrandr --output "$1" --gamma 1.0:0.75:0.50 --brightness 0.7
xrandr --output "$1" --gamma 1.0:0.75:0.40 --brightness 0.7
}
daymode () {
xrandr --output "$1" --gamma 1.0:0.75:0.50 --brightness 0.7
xrandr --output "$1" --gamma 1.0:0.75:0.55 --brightness 0.7
xrandr --output "$1" --gamma 1.0:0.75:0.60 --brightness 0.8
xrandr --output "$1" --gamma 1.0:0.75:0.65 --brightness 0.8
xrandr --output "$1" --gamma 1.0:0.80:0.70 --brightness 0.8
xrandr --output "$1" --gamma 1.0:0.80:0.75 --brightness 0.8
xrandr --output "$1" --gamma 1.0:0.85:0.80 --brightness 0.9
xrandr --output "$1" --gamma 1.0:0.9:0.85 --brightness 0.9
xrandr --output "$1" --gamma 1.0:0.9:0.90 --brightness 0.9
xrandr --output "$1" --gamma 1:1:1 --brightness 1
}
brightness_value=$(xrandr --verbose | grep Brightness | cut -d ' ' -f 2)
if [ "$1" == "check" ]; then
if [ "$brightness_value" == "1.0" ]; then echo 1;exit
elif [ "$brightness_value" == "0.70" ]; then echo 0;exit
fi
else
connected_display_list=$(xrandr | grep ' connected' | awk '{print $1}')
if [ "$brightness_value" == "1.0" ]; then
for disp in $connected_display_list; do
nightmode "$disp"
done
else
for disp in $connected_display_list; do
daymode "$disp"
done
fi
fi





