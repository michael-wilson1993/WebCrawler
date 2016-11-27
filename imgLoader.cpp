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
   if (img.rows <= i)
      i--;
   if (img.cols <= j)
      j--;


   int size = (i - si)*(j - sj); // gets the amount of pixels we are getting the mean for.
   long int totalPixelValue = 0;
   for (int x = si; x < i; x++ )
      for(int y = sj; y < j; y++)
         totalPixelValue += (int)img.at<Vec3b>(i,j)[RGB]; // adds to the total pixel value

   if(totalPixelValue/size < 10)
      return "00" + std::to_string(totalPixelValue/size); 
   if(totalPixelValue/size < 100)
      return "0" + std::to_string(totalPixelValue/size);
   return std::to_string(totalPixelValue/size); //returns the mean
         

}

std::string imgLoader::hashImage(std::string filename, int hashingSize)
{ 

   cv::Mat img = cv::imread(filename);
   std::string retVal = "";
   if(img.rows <= hashingSize || img.cols <= hashingSize)
      return "img/error-Image.png";

   int divx = (img.rows/hashingSize);
   int divy = (img.cols/hashingSize);

   for(int x = 0; x < hashingSize; x++)
      for(int y = 0; y < hashingSize; y++)
      {
         //std::cout << "( " << x*divx << " , " << (x*divx)+divx << " ) - ";
         //std::cout << "( " << y*divy << " , " << (y*divy)+divy << " )" << std::endl;
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
            retVal += getMeanValue(img, x*divx+1, y*divy+1, (x*divx)+divx,  (y*divy)+divy, RGB);
         }
         }
      }
      return retVal;// + std::to_string(img.rows) + "-" +std::to_string(img.cols);
}


void imgLoader::displayImage(std::string imageloc, std::string imageloc2)
{
   // imgLoader img;
   // imgLoader img2;
   
   // cv::Mat image;
   // cv::Mat image2;
   
   // std::string windowName = "image viewer alpha";
   // //std::string windowName2 = "image viewer beta";
   
   // image = img.loadImage(imageloc);
   // //image2 = img2.loadImage(imageloc2);
   // cv::startWindowThread();
   
   // cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
   // //cv::namedWindow(windowName2, cv::WINDOW_AUTOSIZE);
   
   
   // cv::moveWindow(windowName, 50, 100);
   // //cv::moveWindow(windowName2, image.cols+55, 100);
   
   
   // cv::imshow(windowName, image);
   // //cv::imshow(windowName, image2);
   
   // // if (cv::waitKey(30) == -1)
   // // {
   // //    cv::destroyWindow(windowName);
   // // }
   cv::startWindowThread();
IplImage* img1 = cvLoadImage( imageloc.c_str() );
IplImage* img2 = cvLoadImage( imageloc2.c_str() );

int dstWidth=img1->width+img2->width;
int dstHeight=std::max(img1->height, img2->height);

IplImage* dst=cvCreateImage(cvSize(dstWidth,dstHeight),IPL_DEPTH_8U,3); 

cvSetImageROI(dst, cvRect(0, 0,img1->width,img1->height) );
cvCopy(img1,dst,NULL);
cvResetImageROI(dst);

cvSetImageROI(dst, cvRect(img1->width , 0,img2->width,img2->height) );
cvCopy(img2,dst,NULL);
cvResetImageROI(dst);


cvNamedWindow( "display", CV_WINDOW_AUTOSIZE );
cvShowImage( "display", dst );
//cvWaitKey(0);
}
   

void imgLoader::displayImage(std::string imageloc)
{
   imgLoader img;
   std::string display = "display";
   cv::Mat image;
   cv::startWindowThread();
   std::string windowName = "image viewer alpha"; 
   image = img.loadImage(imageloc);
   cv::namedWindow(display, cv::WINDOW_AUTOSIZE);
   cv::imshow(display, image);  

   
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
