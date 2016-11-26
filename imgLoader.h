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
   //constructor
   imgLoader();
   
   // loading image
   cv::Mat loadImage(std::string imageloc);

   // displaying image
   void displayImage(std::string imageloc);
   
   // finding pixel values
   cv::Scalar pixelVal(std::string filename);
   // hashing function
   std::string hashImage(std::string filename);

   
  private:
   
};
