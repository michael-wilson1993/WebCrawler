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

class imgLoader
{
public:
   imgLoader();
   cv::Mat loadImage(std::string imageloc);

   
  private:
   
};
