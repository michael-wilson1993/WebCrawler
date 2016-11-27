#include "imgLoader.h"
using namespace cv;


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


   //int cn = img.channels();
   //Scalar_<uint8_t> bgrPixel;

  
   for (int i = 0; i < img.rows; i++)
   {
      for (int j = 0; j < img.cols; j++)
      {
         //std::cout<<"Value: "<< static_cast<int>(img.at<uchar>(i,j))[0] << std::endl;
         std::cout<<"Value: (" << i << "," << j << ") (" << 
            (int)img.at<Vec3b>(i,j)[0] << "," <<
            (int)img.at<Vec3b>(i,j)[2] << "," <<
            (int)img.at<Vec3b>(i,j)[3] << ")\n" ;
    }
 }
 return RGBpix;
}

std::string getMeanValue(Mat img, int si, int sj, int i, int j, int RGB)
{
   int size = (i - si)*(j - sj); // gets the amount of pixels we are getting the mean for.
   long int totalPixelValue = 0;
   for (int x = si; x < i; x++ )
      for(int y = sj; y < j; y++)
         totalPixelValue += (int)img.at<Vec3b>(i,j)[RGB]; // adds to the total pixel value
   return std::to_string(totalPixelValue/size); //returns the mean
         

}

std::string imgLoader::hashImage(std::string filename, int hashingSize)
{ 

   cv::Mat img = cv::imread(filename);
   std::string retVal = "";

   int divx = img.rows/hashingSize;
   int divy = img.cols/hashingSize;

   for(int x = 0; x < hashingSize; x++)
      for(int y = 0; y < hashingSize; y++)
      {
         std::cout << "( " << x*divx << " , " << (x*divx)+divx << " )" << std::endl;
         std::cout << "( " << y*divy << " , " << (y*divy)+divy << " )" << std::endl;
         if (retVal == "")
         {
            for(int RGB = 0; RGB < 3; RGB++)
               if(RGB == 0)
                  retVal += getMeanValue(img, x*divx, y*divy, (x*divx)+divx,  (y*divy)+divy, RGB);
               else
               {
                  retVal += "-";
                  retVal += getMeanValue(img, x*divx, y*divy, (x*divx)+divx,  (y*divy)+divy, RGB);
               }
         }
         else
         {
             for(int RGB = 0; RGB < 3; RGB++)
             {
            retVal += "-";
            retVal += getMeanValue(img, x*divx, y*divy, (x*divx)+divx,  (y*divy)+divy, RGB);
         }
         }
      }
      return retVal;
}


void imgLoader::displayImage(std::string imageloc)
{
   imgLoader img;
   cv::Mat image;
   std::string windowName = "image viewer";
   image = img.loadImage(imageloc);
   cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
   cv::moveWindow(windowName, 2000, 100);
   cv::imshow(windowName, image);
   if (cv::waitKey(30) == -1)
   {
      cv::destroyWindow(windowName);
   }
   
}







//    // string storing hash
//    std::string hashed;
//    int totalRed;
//    int totalGreen;
//    int totalBlue;
//    int val = 3;

//    cv::Mat img = cv::imread(filename);
//    // For section 1 to 2
//    for(int i = 0; i < img.rows / val; i++)
//    {
//       for (int j = 0; j < img.cols / val; j++)
//       {

//        totalRed = totalRed + (int)img.at<cv::Scalar>(i, j)[2];
//        totalGreen = totalGreen + (int)img.at<cv::Scalar>(i, j)[1];
//        totalBlue = totalBlue + (int)img.at<cv::Scalar>(i, j)[0];
//     }
//  }

//  // push averages to string
//  hashed += totalRed/(img.rows / val) + 48;
//  hashed += '-';
//  hashed += totalGreen/(img.rows / val) + 48;
//  hashed += '-';
//  hashed += totalBlue/(img.rows / val) + 48;
//  hashed += '-';

//    // reset values
//  totalRed = 0;
//  totalGreen = 0;
//  totalBlue = 0;

//  for(int i = (img.rows / val); i > (img.rows / val) && i < ((img.rows / val) * 2); i++)
//  {
//    for (int j = (img.cols / val); j > (img.cols / val) && j < ((img.cols / val) * 2); i++)
//    {
//     totalRed = totalRed + (int)img.at<cv::Scalar>(i, j)[2];
//     totalGreen = totalGreen + (int)img.at<cv::Scalar>(i, j)[1];
//     totalBlue = totalBlue + (int)img.at<cv::Scalar>(i, j)[0];
//  }
// }

//    // push averages to string
// hashed += totalRed/(img.rows / val) + 48;
// hashed += '-';
// hashed += totalGreen/(img.rows / val) + 48;
// hashed += '-';
// hashed += totalBlue/(img.rows / val) + 48;
// hashed += '-';

//    // reset values
// totalRed = 0;
// totalGreen = 0;
// totalBlue = 0;

// for(int i = ((img.rows / val) * 2); i > ((img.rows / val) * 2) && i < img.rows; i++)
// {
//    for (int j = ((img.cols / val) * 2); j >  ((img.cols / val) * 2) && j < img.cols; j++)
//    {
//     totalRed = totalRed + (int)img.at<cv::Scalar>(i, j)[2];
//     totalGreen = totalGreen + (int)img.at<cv::Scalar>(i, j)[1];
//     totalBlue = totalBlue + (int)img.at<cv::Scalar>(i, j)[0];
//  }
// }

//  // push averages to string
// hashed += totalRed/(img.rows / val) + 48;
// hashed += '-';
// hashed += totalGreen/(img.rows / val) + 48;
// hashed += '-';
// hashed += totalBlue/(img.rows / val) + 48;
// hashed += '-';

//    // reset values
// totalRed = 0;
// totalGreen = 0;
// totalBlue = 0;

// std::cout << hashed;
// return hashed;