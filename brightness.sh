#!/bin/sh
if [ -z "$1" ]; then
  return 1;
fi
TIME=300
case $1 in
  up)
    INC="10"
    ;;
  down)
    INC="-10"
    ;;
  *)
    INC="${1}"
    if [ "$INC" -lt 5 ] && [ "$INC" -gt -5 ]; then
      TIME=10
    elif [ "$INC" -lt 10 ] && [ "$INC" -gt -10 ]; then
      TIME=100
    fi
    ;;
esac
DISPLAY=:0 /usr/bin/xbacklight -inc ${INC}% -time ${TIME} 
sudo -u gxg DISPLAY=:0 notify-send --urgency=low --expire-time=500 "Backlight: $(DISPLAY=:0 xbacklight -get | cut -d . -f 1)%"
return 0
