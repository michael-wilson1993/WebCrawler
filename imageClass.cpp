#include "imageClass.h"

imageClass::imageClass()
{
   std::unordered_map<long,cv::Mat> key, image;
}

void imageClass::addHashElement(size_t value, cv::Mat image)
{
   std::pair<size_t, cv::Mat> newElement (value, image);
   key.insert(newElement);
}

cv::Mat imageClass::loadImage(std::string imageloc)
{
   cv::Mat image;
   image = cv::imread(imageloc, CV_LOAD_IMAGE_COLOR);
   if(! image.data)
   {
      std::cout << "Image Load Failed!" << std::endl;
   }
   return image;
}

size_t imageClass::hashImage(cv::Mat image)
{
   size_t thehash = 0; //image.cv::SparseMat::hash(1);
   return thehash;
}



 
