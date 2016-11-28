

OBJS = main.o WebScraper.o imgLoader.o MainMenu.o imageBoard.o

SRCS = main.cpp

CC = g++11
CFLAGS = -g -std=c++11 -lcurl
CINCLUDE = -I/home/cheng/opencv-64/include
CLINKER = -L/home/cheng/opencv-64/lib -lopencv_core -lopencv_imgproc -lopencv_contrib -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_legacy -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_ocl -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_video -lopencv_videostab

webCrawl: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(CINCLUDE) $(CLINKER) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $(CINCLUDE) $(CLINKER) -c $<

clean:
	rm -f *.o *~ *% *# .#*
	rm logFiles/VisitedLinks
	rm logFiles/savedImages
	rm logFiles/lookUpTable.txt
	rm logFiles/timeLog.txt
	rm img/*

clean-all:
	rm -f *.o *~ *% *# .#*
	rm ./webCrawl
	rm img/*

#!/bin/bash

#LD_LIBRARY_PATH=/home/cheng/opencv-64/lib webCrawl