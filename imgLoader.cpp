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

cv::Scalar imgLoader::pixelVal(std::string filename)
{
   cv::Mat img = cv::imread(filename);
   cv::Scalar RGBpix;
   std::cout << img.rows;
   std::cin.get();
   for (int i = 0; i < img.rows; i++)
   {
      for (int j = 0; j < img.cols; j++)
      {
	 RGBpix = img.at<cv::Scalar>(i,j);
	 // TEST
	 std::cout << "ASSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS";
	 std::cout << std::endl;
	 std::cout << img.at<cv::Scalar>(i,0)[0] << "-" << img.at<cv::Scalar>(i,0)[1] << "-" << img.at<cv::Scalar>(i,0)[2] << std::endl;
      }
   }
   return RGBpix;
}

std::string imgLoader::hashImage(std::string filename)
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
	 
	 totalRed = totalRed + (int)img.at<cv::Scalar>(i, j)[2];
	 totalGreen = totalGreen + (int)img.at<cv::Scalar>(i, j)[1];
	 totalBlue = totalBlue + (int)img.at<cv::Scalar>(i, j)[0];
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
	 totalRed = totalRed + (int)img.at<cv::Scalar>(i, j)[2];
	 totalGreen = totalGreen + (int)img.at<cv::Scalar>(i, j)[1];
	 totalBlue = totalBlue + (int)img.at<cv::Scalar>(i, j)[0];
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
	 totalRed = totalRed + (int)img.at<cv::Scalar>(i, j)[2];
	 totalGreen = totalGreen + (int)img.at<cv::Scalar>(i, j)[1];
	 totalBlue = totalBlue + (int)img.at<cv::Scalar>(i, j)[0];
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
   cv::moveWindow(imageloc, 100, 100);
   cv::imshow(imageloc, image);
   if (cv::waitKey(30) == -1)
   {
      cv::destroyWindow(imageloc);
   }
   
}






 
