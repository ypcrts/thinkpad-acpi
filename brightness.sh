#!/bin/sh
case $1 in
  up)
    DISPLAY=:0 /usr/bin/xbacklight -inc 20% -time 500
    ;;
  down)
    DISPLAY=:0 xbacklight -dec 20% -time 500 
    ;;
esac

DISPLAY=:0 notify-send --urgency=low --expire-time=500 "Backlight: $(DISPLAY=:0 xbacklight -get | cut -d . -f 1)%" 
