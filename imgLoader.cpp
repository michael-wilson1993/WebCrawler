#include "imgLoader.h"

imgLoader::imgLoader()
{}

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
	 RGBpix = img.at<cv::Vec3b>(i,j);
	 // TEST
	 // std::cout << img.at<cv::Vec3b>(i,0)[0] << "-" << img.at<cv::Vec3b>(i,0)[1] << "-" << img.at<cv::Vec3b>(i,0)[2] << std::endl;
      }
   }
   return RGBpix;
}

std::string imgLoader::hashImage(std::string filename, cv::Vec3b RGBval)
{ 
   // string storing hash
   std::string hashed;
   int totalRed;
   int totalGreen;
   int totalBlue;

   cv::Mat img = cv::imread(filename);
   // For section 1 to 2
   for(int i = 0; i < img.rows / 3; i++)
   {
      for (int j = 0; j < img.cols / 3; j++)
      {
	 
	 totalRed = totalRed + (int)img.at<cv::Vec3b>(i, j)[0];
	 std::cout << totalRed;
	 totalGreen = totalGreen + (int)img.at<cv::Vec3b>(i, j)[1];
	 std::cout << totalGreen;
	 totalBlue = totalBlue + (int)img.at<cv::Vec3b>(i, j)[2];
	  std::cout << totalBlue;
      }
   }

 // push averages to string
   hashed += totalRed/(img.rows / 3) + 48;
   hashed += '-';
   hashed += totalGreen/(img.rows / 3) + 48;
   hashed += '-';
   hashed += totalBlue/(img.rows / 3) + 48;
   hashed += '-';

   // reset values
   totalRed = 0;
   totalGreen = 0;
   totalBlue = 0;

   for(int i = (img.rows / 3); i > (img.rows / 3) && i < ((img.rows / 3) * 2); i++)
   {
      for (int j = (img.cols / 3); j > (img.cols / 3) && j < ((img.cols / 3) * 2); i++)
      {
	 totalRed = totalRed + (int)img.at<cv::Vec3b>(i, j)[0];
	 totalGreen = totalGreen + (int)img.at<cv::Vec3b>(i, j)[1];
	 totalBlue = totalBlue + (int)img.at<cv::Vec3b>(i, j)[2];
      }
   }

   // push averages to string
   hashed += totalRed/(img.rows / 3) + 48;
   hashed += '-';
   hashed += totalGreen/(img.rows / 3) + 48;
   hashed += '-';
   hashed += totalBlue/(img.rows / 3) + 48;
   hashed += '-';

   // reset values
   totalRed = 0;
   totalGreen = 0;
   totalBlue = 0;

   for(int i = ((img.rows / 3) * 2); i > ((img.rows / 3) * 2) && i < img.rows; i++)
   {
      for (int j = ((img.cols / 3) * 2); j >  ((img.cols / 3) * 2) && j < img.cols; j++)
      {
	 totalRed = totalRed + (int)img.at<cv::Vec3b>(i, j)[0];
	 totalGreen = totalGreen + (int)img.at<cv::Vec3b>(i, j)[1];
	 totalBlue = totalBlue + (int)img.at<cv::Vec3b>(i, j)[2];
      }
   }

 // push averages to string
   hashed += totalRed/(img.rows / 3) + 48;
   hashed += '-';
   hashed += totalGreen/(img.rows / 3) + 48;
   hashed += '-';
   hashed += totalBlue/(img.rows / 3) + 48;
   hashed += '-';

   // reset values
   totalRed = 0;
   totalGreen = 0;
   totalBlue = 0;

   std::cout << hashed;
   return hashed;
   
}


void imgLoader::displayImage(std::string imageloc)
{
   imgLoader img;
   cv::Mat image;
   image = img.loadImage(imageloc);
   cv::namedWindow(imageloc, cv::WINDOW_AUTOSIZE);
   cv::imshow(imageloc, image);
   cv::waitKey(0);
   // cv::destroyWindow(imageloc);
}






 
