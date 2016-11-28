#include "imgLoader.h"
using namespace cv;


imgLoader::imgLoader()
{}

cv::Mat imgLoader::loadImage(std::string imageloc)
{
   cv::Mat image;
   // reads an image from a given location
   image = cv::imread(imageloc.c_str(), 1);
   // throws error if the image is empty or doesnt load properly
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

   // pushes back the values of each pixel for BGR values onto the vector
   for (int i = 0; i < img.rows; i++)
   {
      for (int j = 0; j < img.cols; j++)
      {
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

   // adds numbers if the data is single digit to make keys align
   if(totalPixelValue/size < 10)
      return "00" + std::to_string(totalPixelValue/size); 
   if(totalPixelValue/size < 100)
      return "0" + std::to_string(totalPixelValue/size);
   return std::to_string(totalPixelValue/size); //returns the mean         
}

std::string imgLoader::hashImage(std::string filename, int hashingSize)
{
   // reads an image frm a file source given
   cv::Mat img = cv::imread(filename);

// makes sure an image is large enough to cut
   std::string retVal = "";
   if(img.rows <= hashingSize || img.cols <= hashingSize)
      return "";

   // decides number of divisions in each direction
   int divx = (img.rows/hashingSize);
   int divy = (img.cols/hashingSize);

   // gets the specific section of the image we want to read values from
   for(int x = 0; x < hashingSize; x++)
      for(int y = 0; y < hashingSize; y++)
      {
         if(x%3 == 0)
         {
            retVal += "-";
            retVal += getMeanValue(img, x*divx, y*divy, (x*divx)+divx,  (y*divy)+divy, 0);
         }
            if(x%3 == 1)
            {
            retVal += "-";
            retVal += getMeanValue(img, x*divx, y*divy, (x*divx)+divx,  (y*divy)+divy, 1);
            }
               else
               {
            retVal += "-";
            retVal += getMeanValue(img, x*divx, y*divy, (x*divx)+divx,  (y*divy)+divy, 2);
               }

      }
      return retVal;// + std::to_string(img.rows) + "-" +std::to_string(img.cols);
}


void imgLoader::displayImage(std::string imageloc, std::string imageloc2)
{
   cv::startWindowThread();
   // loads two images 
   IplImage* img1 = cvLoadImage( imageloc.c_str() );
   IplImage* img2 = cvLoadImage( imageloc2.c_str() );

   // window width in case of duplicates
   int dstWidth=img1->width+img2->width + 1;
   if(dstWidth > 2000)
      return;
   // window height in case of duplicates
   int dstHeight=std::max(img1->height, img2->height);

   IplImage* dst=cvCreateImage(cvSize(dstWidth,dstHeight),IPL_DEPTH_8U,3); 

   // resets and updates images when there is changes
   cvSetImageROI(dst, cvRect(0, 0,img1->width,img1->height) );
   cvCopy(img1,dst,NULL);
   cvResetImageROI(dst);
   cvSetImageROI(dst, cvRect(img1->width , 0,img2->width,img2->height) );
   cvCopy(img2,dst,NULL);
   cvResetImageROI(dst);


   cvNamedWindow( "display", CV_WINDOW_AUTOSIZE );
   cvShowImage( "display", dst );
}
   

void imgLoader::displayImage(std::string imageloc)
{ 
   cv::startWindowThread();
   // creates single image section
   IplImage* img1 = cvLoadImage( imageloc.c_str() );

   // sets window width and height using image size
   int dstWidth=img1->width+1;
   int dstHeight=img1->height;

   IplImage* dst=cvCreateImage(cvSize(dstWidth,dstHeight),IPL_DEPTH_8U,3); 

   cvSetImageROI(dst, cvRect(0, 0,img1->width,img1->height) );
   cvCopy(img1,dst,NULL);
   cvResetImageROI(dst);

   cvNamedWindow( "display", CV_WINDOW_AUTOSIZE );
   cvShowImage( "display", dst );  
}
