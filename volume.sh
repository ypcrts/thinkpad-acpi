#!/bin/sh
case $1 in
  up)
#  pactl set-sink-volume @DEFAULT_SINK@ +10%

    ;;
  down)
  #pactl set-sink-volume @DEFAULT_SINK@ -10%
    ;;
  mute)
  #pactl set-sink-mute @DEFAULT_SINK@ toggle
  amixer -D pulse set Master 1+ toggle
    ;;
  mutemic)
  #pactl set-source-mute alsa_input.pci-0000_00_1b.0.analog-stereo toggle
  exit 0
    ;;
esac

DISPLAY=:0 notify-send --urgency=low --expire-time=500 "Volume: $(echo `(pactl list sinks | grep "Volume: 0:")| awk '{print $3}'`)%" 
