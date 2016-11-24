#pragma once

#include <string>
#include <vector>
#include "curler/include/curl/multi.h"
#include "curler/include/curl/curl.h"
#include <iostream>
#include <set>
#include <fstream>
#include <cstring>
#include <unordered_map>

#include <opencv2/opencv.hpp>

class imageClass
{
public:
   imageClass();
   cv::Mat loadImage(std::string imageloc);
   void addHashElement(size_t value, cv::Mat image);
   size_t hashImage(cv::Mat image);
   std::unordered_map<size_t,cv::Mat> key, image;
   
  private:
   
};
