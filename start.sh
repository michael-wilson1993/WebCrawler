#!/bin/bash

if [ ! -d "$img" ]; then
  mkdir -p img;
fi

LD_LIBRARY_PATH=/home/cheng/opencv-64/lib webCrawl
