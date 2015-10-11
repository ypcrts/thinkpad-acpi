#!/bin/sh
case $1 in
  up)
    DISPLAY=:0 /usr/bin/xbacklight -inc 10% -time 300
    ;;
  down)
    DISPLAY=:0 xbacklight -dec 10% -time 300 
    ;;
esac
sleep 300ms
sudo -u gxg DISPLAY=:0 notify-send --urgency=low --expire-time=500 "Backlight: $(DISPLAY=:0 xbacklight -get | cut -d . -f 1)%" 
