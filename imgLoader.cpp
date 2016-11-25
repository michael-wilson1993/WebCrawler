#include "imgLoader.h"

imgLoader::imgLoader()
{

}



cv::Mat imgLoader::loadImage(std::string imageloc)
{
   cv::Mat image;
   image = cv::imread(imageloc.c_str(), 1);
   if(! image.data)
   {
      std::cout << "Image Load Failed!" << std::endl;
   }
   return image;
}





 
