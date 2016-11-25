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

cv::Vec3b imgLoader::pixelVal(std::string filename)
{
   cv::Mat img = cv::imread(filename);
   cv::Vec3b RGBpix;
   for (int i = 0; i < img.rows; i++)
   {
      for (int j = 0; j < img.cols; j++)
      {
	 RGBpix = (int)img.at<cv::Vec3b>(i,j);
      }
   }  
   return RGBpix;
}

std::string imgLoader::hashImage(std::string filename, cv::Vec3b RGBval)
{
   /*
   // string storing hash
   std::string hashed;
   
   // split factor
   int split = 3;

   cv::Mat img = cv::imread(filename);
   // For section 1 to 2
   for(int i = 0; i < img.rows / 3; i++)
   {
      for (int j = 0; j < img.columns / 3; j++)
      {
	 hashed.append(
      }
   }

   for(int i = (img.rows / 3); i > (img.rows / 3) && i < ((img.rows / 3) * 2); i++)
   {
      for (int j = 0; img.columns / 3; j++)
      {
	 
      }
   }

   for(int i = ((img.rows / 3) * 2); i >  ((img.rows / 3) * 2) && i < img.rows; i++)
   {
      for (int j = 0; img.columns / 3; j++)
      {
	 
      }
      }
   */
}


void imgLoader::displayImage(std::string imageloc)
{
   imgLoader img;
   cv::Mat image;
   image = img.loadImage(imageloc);
   cv::namedWindow(imageloc, cv::WINDOW_AUTOSIZE);
   cv::imshow(imageloc, image);
   cv::waitKey(0);
   cv::destroyWindow(imageloc);
}






 
