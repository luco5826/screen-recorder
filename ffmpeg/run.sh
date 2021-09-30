#!/bin/bash
g++ \
  -g \
  $(pkg-config --cflags libavcodec libavformat libavutil libswscale libavdevice libswresample  libswscale) \
  -pthread \
  ScreenRecorder.cpp \
  main.cpp \
  $(pkg-config --libs libavcodec libavformat libswscale libavdevice libavutil libswresample  libswscale) \
  -o out
if [[ $? == 0 ]]; then
  ./out 
fi
