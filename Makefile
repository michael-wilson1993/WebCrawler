OBJS = main.o WebScraper.o imageScraper.o

SRCS = main.cpp 

CC = g++11
CFLAGS = -Wall -g -std=c++11 -lcurl


webCrawl: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ 

%.o: %.cc
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o *~ *% *# .#*

clean-all:
	rm -f *.o *~ *% *# .#*
	rm ./webCrawl